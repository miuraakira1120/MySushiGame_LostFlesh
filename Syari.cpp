﻿#include <DirectXMath.h>

#include <vector>
#include "Syari.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "RedBox.h"
#include "BlueBox.h"
#include "Engine/Camera.h"
#include "Maguro.h"
#include <directxmath.h>
#include "Engine/BoxCollider.h"
#include "Goal.h"
#include "Controller.h"
#include "Time.h"
#include "Engine/SceneManager.h"


using std::vector;

//コンストラクタ
Syari::Syari(GameObject* parent)
    :GameObject(parent, "Syari"), hModel_(-1), mode(1), axisPos(0.5f, 0.5f, 1.0f),
    prevPos(0.0f, 0.0f, 0.0f), accel(0.0f), jumpSpeed(0), pGauge_(nullptr),isGround(false),prevBonePos(),countTime(0)
{
}

//デストラクタ
Syari::~Syari()
{
}

//初期化
void Syari::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("syari.fbx");
    //hModel_ = Model::Load("GodSyari.fbx");
    assert(hModel_ >= 0);

    //頂点の座標をvVertexPosに入れる
    vVertexPos.push_back(upRightFrontPos);
    vVertexPos.push_back(upRightBackPos);
    vVertexPos.push_back(upLeftFrontPos);
    vVertexPos.push_back(upLeftBackPos);
    vVertexPos.push_back(downRightFrontPos);
    vVertexPos.push_back(downRightBackPos);
    vVertexPos.push_back(downLeftFrontPos);
    vVertexPos.push_back(downLeftBackPos);

    //子オブジェクトの生成
    Instantiate<Maguro>(this);

    //当たり判定の生成
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 2));
    AddCollider(collision);

    transform_.position_.y = -40;

    pGauge_ = Instantiate<Gauge>(this);

    //ポリライン初期化
    pLine = new PoryLine;
    pLine->Load("tex.png");

    //Time::UnLock();
    //pGauge_->SetMaxHP(300 * 60);
}

//更新
void Syari::Update()
{
    countTime ++;
    //pGauge_->SetNowHP(Time::GetTimei());
    pGauge_->Damage(1);

    if (countTime > 250 * 60)
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }

    vMove = { 0,0,0,0 };

    MoveMouse();
    //キー入力をする
    KeyOperation();
    

    //各頂点の位置を調べる
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }


    //transform_.SetAxisTrans(axisPos);
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    Goal* pGoal = (Goal*)FindObject("Goal");        //ゴールオブジェクトを探す
    int hGoalModel = pGoal->GetModelHandle();       //モデル番号を取得

    //一番低いところと高いところを探す
    int lowest = 0;
    int highest = 0;
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[lowest].y > vertexBonePos[i].y)
        {
            lowest = i;
        }
        if (vertexBonePos[highest].y < vertexBonePos[i].y)
        {
            highest = i;
        }
    }

    //一番右と左を探す
    int rightest = 0;
    int leftest = 0;
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[leftest].x > vertexBonePos[i].x)
        {
            leftest = i;
        }
        if (vertexBonePos[rightest].x < vertexBonePos[i].x)
        {
            rightest = i;
        }
    }

    //一番奥と手前を探す
    int foremost = 0;//奥
    int innermost = 0;//手前
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[innermost].z > vertexBonePos[i].z)
        {
            innermost = i;
        }
        if (vertexBonePos[foremost].z < vertexBonePos[i].z)
        {
            foremost = i;
        }
    }
    ////////////////////レイを飛ばす/////////////////////
    
    RayCastData GoalData;                       //シャリの位置からレイを飛ばして、ゴールとぶつかるかを調べる
    GoalData.start = transform_.position_;      //レイの発射位置
    GoalData.dir = XMFLOAT3(0, -1, 0);          //レイの方向
    Model::RayCast(hGoalModel, &GoalData);      //レイを発射

    RayCastData prevPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    prevPosData.start = prevPos/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    prevPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &prevPosData); //レイを発射

    RayCastData prevLowPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    prevLowPosData.start = prevBonePos[lowest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    prevLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &prevLowPosData); //レイを発射

    RayCastData nowPosData[6];
    for (int i = 0; i < sizeof(direction) / sizeof(XMFLOAT3); i++)
    {
        nowPosData[i].start = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z);    //レイの発射位置
        nowPosData[i].dir = direction[i];        //レイの方向
        Model::RayCast(hGroundModel, &nowPosData[i]);  //レイを発射
    }

    //一番下の位置からレイを飛ばす
    RayCastData nowLowPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowLowPosData.start = vertexBonePos[lowest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowLowPosData); //レイを発射

    XMFLOAT3 fDir;
    XMStoreFloat3(&fDir, vMove);
    fDir = XMFLOAT3(fDir.x * 0, fDir.y, fDir.z * 0);
    //一番上の位置からレイを飛ばす
    RayCastData nowUpPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowUpPosData.start = Transform::Float3Add(vertexBonePos[highest],fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowUpPosData.dir = XMFLOAT3(0, 1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowUpPosData); //レイを発射

    //一番左の位置からレイを飛ばす
    RayCastData nowLeftPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowLeftPosData.start = Transform::Float3Add(vertexBonePos[leftest], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowLeftPosData.dir = XMFLOAT3(-1, 0, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowLeftPosData); //レイを発射

    //一番右の位置からレイを飛ばす
    RayCastData nowRightPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowRightPosData.start = Transform::Float3Add(vertexBonePos[rightest], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowRightPosData.dir = XMFLOAT3(1, 0, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowRightPosData); //レイを発射

    //一番奥の位置からレイを飛ばす
    RayCastData nowBackPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowBackPosData.start = Transform::Float3Add(vertexBonePos[foremost], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowBackPosData.dir = XMFLOAT3(0, 0, 1);       //レイの方向
    Model::RayCast(hGroundModel, &nowBackPosData); //レイを発射

    //一番手前の位置からレイを飛ばす
    RayCastData nowFrontPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowFrontPosData.start = Transform::Float3Add(vertexBonePos[innermost], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowFrontPosData.dir = XMFLOAT3(0, 0, -1);       //レイの方向
    Model::RayCast(hGroundModel, &nowFrontPosData); //レイを発射

    /////////全部の角から全方向にレイを飛ばす//////
    RayCastData shortDistance[SHORT_DISTANCE_MAX];
    for (int i = 0; i < SHORT_DISTANCE_MAX; i++)
    {
        shortDistance[i].dist = 99999;
    }
    
    //一番左の位置からレイを飛ばす
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        RayCastData nowLeftPosDataAll;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
        nowLeftPosDataAll.start = Transform::Float3Add(vertexBonePos[i], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
        nowLeftPosDataAll.dir = XMFLOAT3(-1, 0, 0);       //レイの方向
        Model::RayCast(hGroundModel, &nowLeftPosDataAll); //レイを発射
        if (nowLeftPosDataAll.dist < shortDistance[LEFTEST].dist)
        {
            shortDistance[LEFTEST] = nowLeftPosDataAll;
        }
    }

    //一番右の位置からレイを飛ばす
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        RayCastData nowRightPosDataAll;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
        nowRightPosDataAll.start = Transform::Float3Add(vertexBonePos[i], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
        nowRightPosDataAll.dir = XMFLOAT3(1, 0, 0);       //レイの方向
        Model::RayCast(hGroundModel, &nowRightPosDataAll); //レイを発射
        if (nowRightPosDataAll.dist < shortDistance[RIGHTEST].dist)
        {
            shortDistance[RIGHTEST] = nowRightPosDataAll;
        }
    }

    //一番奥の位置からレイを飛ばす
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        RayCastData nowBackPosDataAll;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
        nowBackPosDataAll.start = Transform::Float3Add(vertexBonePos[i], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
        nowBackPosDataAll.dir = XMFLOAT3(0, 0, 1);       //レイの方向
        Model::RayCast(hGroundModel, &nowBackPosDataAll); //レイを発射
        if (nowBackPosDataAll.dist < shortDistance[FOREMOST].dist)
        {
            shortDistance[FOREMOST] = nowBackPosDataAll;
        }
    }

    //一番手前の位置からレイを飛ばす
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        RayCastData nowFrontPosDataAll;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
        nowFrontPosDataAll.start = Transform::Float3Add(vertexBonePos[i], fDir)/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
        nowFrontPosDataAll.dir = XMFLOAT3(0, 0, -1);       //レイの方向
        Model::RayCast(hGroundModel, &nowFrontPosDataAll); //レイを発射
        if (nowFrontPosDataAll.dist < shortDistance[INNERMOST].dist)
        {
            shortDistance[INNERMOST] = nowFrontPosDataAll;
        }
    }

    /////////////////////////////////////////////////////

    
    //もし下に地面があったら
    if (nowLowPosData.hit && nowLowPosData.dist > accel)
    //if (nowPosData[BOTOM].hit && nowPosData[BOTOM].dist > accel)
    {           
        //接地フラグを真にする
        isGround = false;

        //重力
        if (SPEED_LIMIT >= accel)
        {
            accel += FALL_SPEED;
            transform_.position_.y -= accel;
        }
        else
        {
            transform_.position_.y -= SPEED_LIMIT;
        }
    }
    else //もし下に地面がなかったら
    {
        /*isGround = true;
        accel = 0.0f;
        transform_.position_.y -= nowLowPosData.dist;*/

        accel = 0.0f;
        XMFLOAT3 lowDistance = { abs(transform_.position_.x - vertexBonePos[lowest].x),  abs(transform_.position_.y - vertexBonePos[lowest].y),  abs(transform_.position_.z - vertexBonePos[lowest].z) };
        //XMFLOAT3 lowDistance = { abs(prevPos.x - pravBonePos[lowest].x),  abs(prevPos.y - pravBonePos[lowest].y),  abs(prevPos.z - pravBonePos[lowest].z) };
        transform_.position_.y -= nowPosData[BOTOM].dist - lowDistance.y;
        //transform_.position_.y -= prevPosData.dist - SYARI_SIZE_Y;
        //接地フラグを真にする
        isGround = true;
    }

    //右の当たり判定
    if (shortDistance[RIGHTEST].hit && shortDistance[RIGHTEST].dist <= fabs(XMVectorGetX(vMove)))
    {
        transform_.position_.x -= shortDistance[RIGHTEST].dist;
    }
    //左の当たり判定
    else if (shortDistance[LEFTEST].hit && shortDistance[LEFTEST].dist <= fabs(XMVectorGetX(vMove)))
    {
        transform_.position_.x += shortDistance[LEFTEST].dist;
    }
    else
    {
        XMVECTOR vPos;
        vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
        vPos += vMove;
        transform_.position_.x = XMVectorGetX(vPos);
        //XMFLOAT3 tmpPosition_;
        //XMStoreFloat3(&tmpPosition_, vPos);//現在地をtransform_.position_に送る
        //tmpPosition_ = { tmpPosition_.x, 0, 0 };
        //transform_.position_ = Transform::Float3Add(transform_.position_, tmpPosition_);
    }

    //奥の当たり判定
    if (shortDistance[FOREMOST].hit && shortDistance[FOREMOST].dist <= fabs(XMVectorGetZ(vMove)))
    {
        transform_.position_.z -= shortDistance[FOREMOST].dist;
    }
    //手前の当たり判定
    else if (shortDistance[INNERMOST].hit && shortDistance[INNERMOST].dist <= fabs(XMVectorGetZ(vMove)))
    {
        transform_.position_.z += shortDistance[INNERMOST].dist;
    }
    else
    {
        XMVECTOR vPos;
        vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
        vPos += vMove;
        //XMFLOAT3 tmpPosition_;
        transform_.position_.z = XMVectorGetZ(vPos);
        //XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る
        //tmpPosition_ = { 0, 0, tmpPosition_.z };
        //transform_.position_ = Transform::Float3Add(transform_.position_, vPos);
    }

    ////右の当たり判定
    //if (nowRightPosData.hit && nowRightPosData.dist <= fabs(XMVectorGetX(vMove)))
    //{
    //    transform_.position_.x -= nowRightPosData.dist;
    //}
    ////左の当たり判定
    //else if (nowLeftPosData.hit && nowLeftPosData.dist <= fabs(XMVectorGetX(vMove)))
    //{
    //    transform_.position_.x += nowLeftPosData.dist;
    //}
    //else
    //{
    //    XMVECTOR vPos;
    //    vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
    //    vPos += vMove;
    //    transform_.position_.x = XMVectorGetX(vPos);
    //    //XMFLOAT3 tmpPosition_;
    //    //XMStoreFloat3(&tmpPosition_, vPos);//現在地をtransform_.position_に送る
    //    //tmpPosition_ = { tmpPosition_.x, 0, 0 };
    //    //transform_.position_ = Transform::Float3Add(transform_.position_, tmpPosition_);
    //}

    ////奥の当たり判定
    //if (nowBackPosData.hit && nowBackPosData.dist <= fabs(XMVectorGetZ(vMove)))
    //{
    //    transform_.position_.z -= nowBackPosData.dist;
    //}
    ////手前の当たり判定
    //else if (nowFrontPosData.hit && nowFrontPosData.dist <= fabs(XMVectorGetZ(vMove)))
    //{
    //    transform_.position_.z += nowFrontPosData.dist;
    //}
    //else
    //{
    //    XMVECTOR vPos;
    //    vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
    //    vPos += vMove;
    //    //XMFLOAT3 tmpPosition_;
    //    transform_.position_.z = XMVectorGetZ(vPos);
    //    //XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る
    //    //tmpPosition_ = { 0, 0, tmpPosition_.z };
    //    //transform_.position_ = Transform::Float3Add(transform_.position_, vPos);
    //}

    //XMVECTOR vPos;
    //vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
    //vPos -= vMove;
    //XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る
    


    ////横の当たり判定
    //RayCastData vertexCollision[VERTEX_MAX];
    //for (int i = 0; i < VERTEX_MAX; i++)
    //{
    //    vertexCollision[i].start = transform_.position_;
    //    vertexCollision[i].dir = Transform::Float3Sub(transform_.position_, vertexBonePos[i]);
    //    Model::RayCast(hGroundModel, &vertexCollision[i]);  //レイを発射
    //}

    ////中心から角までの距離
    //float vertexDistance[VERTEX_MAX];
    ////中心から角までの距離を求める
    //for (int i = 0; i < VERTEX_MAX; i++)
    //{
    //    vertexDistance[i] = Transform::FloatDistance(transform_.position_, vertexBonePos[i]);
    //}
    ////distがvertexDistanceより短ければ当たっている
    //for (int i = 0; i < VERTEX_MAX; i++)
    //{
    //    if (vertexCollision[i].dist < vertexDistance[i] && vertexCollision[i].hit)
    //    {
    //            //x > 0 = 右向きのベクトルなら
    //            if (vertexCollision[i].dir.x > 0)
    //            {
    //                transform_.position_ = prevPos;
    //            }
    //            //x > 0 = 左向きのベクトルなら
    //            if (vertexCollision[i].dir.x < 0)
    //            {
    //                transform_.position_ = prevPos;
    //            }
    //            //x > 0 = 右向きのベクトルなら
    //            if (vertexCollision[i].dir.z > 0)
    //            {
    //                transform_.position_.z = prevPos.z;
    //            }
    //            //x > 0 = 右向きのベクトルなら
    //            if (vertexCollision[i].dir.z < 0)
    //            {
    //                transform_.position_.z = prevPos.z;
    //            }
    //    }
    //}
     
     
    //ゴールしたら
    if (GoalData.hit)
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GOAL);
    }

    RedBox* pRedBox = (RedBox*)FindObject("RedBox");    //RedBoxを探す（一番下の頂点に）
    BlueBox* pBlueBox = (BlueBox*)FindObject("BlueBox");//BlueBoxを探す（transform_.positionに）
    pRedBox->SetPosition(vertexBonePos[foremost]);
    pBlueBox->SetPosition(vertexBonePos[innermost]);

    //ポリラインに現在の位置を伝える
    pLine->AddPosition(transform_.position_);

    //動かす前の位置を保存しておく
    prevPos = transform_.position_;
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        prevBonePos[i] = vertexBonePos[i];
    }
}

//描画
void Syari::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //ポリラインを描画
    pLine->Draw();
}

//開放
void Syari::Release()
{
    pLine->Release();
}

//現在地のゲッター
XMFLOAT3 Syari::GetPosition()
{
    return transform_.position_;
}

//回転のゲッター
XMFLOAT3 Syari::GetRotate()
{
    return transform_.rotate_;
}

//キー操作
void Syari::KeyOperation()
{
#if _DEBUG
    if (Input::IsKeyDown(DIK_RETURN))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GOAL);
    }
#endif
    //ENTERキーを押したとき
    if (Input::IsKeyDown(DIK_RETURN))
    {
        switch (mode)
        {
        case 0:
            mode += 1;
            break;
        case 1:
            mode -= 1;
            break;
        default:
            break;
        }
    }
    ////////移動/////////////

    //左マウスキーを押したとき
    if (Input::IsMouseButton(0))
    {
    //    Controller* pController = (Controller*)FindObject("Controller");
    //    transform_.rotate_.y = pController->GetRotate().y;
    //    XMFLOAT3 move = { 0,0,0.3f };//プレイヤーの移動ベクトル
    //    XMVECTOR vMove = XMLoadFloat3(&move);//移動ベクトルの型をXMVECTORに変換
    //    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //    vMove -= XMVector3TransformCoord(vMove, mRotate);
    //    //移動
    //    XMVECTOR vPos;
    //    vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
    //    vPos += vMove;
    //    XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る

        Controller* pController = (Controller*)FindObject("Controller");
        transform_.rotate_.y = pController->GetRotate().y;
        XMFLOAT3 move = { 0,0,0.3f };//プレイヤーの移動ベクトル
        vMove = XMLoadFloat3(&move);//移動ベクトルの型をXMVECTORに変換
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        vMove = XMVector3TransformCoord(vMove, mRotate);
        vMove *= -1;
       
        XMStoreFloat3(&fMove, vMove);
        //XMVECTOR vPos;
        //vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
        //vPos -= vMove;
        //XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る
    }

    //左マウスキーを押したとき
    if (Input::IsMouseButton(1))
    {
        Controller* pController = (Controller*)FindObject("Controller");
        transform_.rotate_.y = pController->GetRotate().y;
        XMFLOAT3 move = { 0,0,0.3f };//プレイヤーの移動ベクトル
        vMove = XMLoadFloat3(&move);//移動ベクトルの型をXMVECTORに変換
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        vMove = XMVector3TransformCoord(vMove, mRotate);
        vMove *= 1;
        XMStoreFloat3(&fMove, vMove);
        //XMVECTOR vPos;
        //vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
        //vPos += vMove;
        //XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る
    }
    //Sキーを押したとき
    if (Input::IsKey(DIK_S))
    {
    }
    //ジャンプする
    if (Input::IsKey(DIK_SPACE))
    {
        Jump();
    }
}

bool Syari::isFly()
{
    return false;
}

void Syari::MoveMouse()
{
   XMFLOAT3 moveMouse = Input::GetMouseMove();
    transform_.rotate_.x += moveMouse.y * ROTATE_SPEED;
    transform_.rotate_.z += moveMouse.x * ROTATE_SPEED;
}

void Syari::Jump()
{
    if (isGround)
    {
        accel -= SPEED_OF_JUMP;
    }
}

