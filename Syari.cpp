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


using std::vector;

//コンストラクタ
Syari::Syari(GameObject* parent)
    :GameObject(parent, "Syari"), hModel_(-1), mode(1), axisPos(0.5f, 0.5f, 1.0f),
    prevPos(0.0f, 0.0f, 0.0f), accel(0.0f), jumpSpeed(0), pGauge_(nullptr),isGround(false),pravBonePos()
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

    //transform_.position_.y = -40;

    pGauge_ = Instantiate<Gauge>(this);

    //ポリライン初期化
    pLine = new PoryLine;
    pLine->Load("tex.png");
}

//更新
void Syari::Update()
{
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
    prevLowPosData.start = pravBonePos[lowest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    prevLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &prevLowPosData); //レイを発射

    RayCastData nowLowPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowLowPosData.start = vertexBonePos[lowest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowLowPosData); //レイを発射

    RayCastData nowPosData[6];
    for (int i = 0; i < sizeof(direction) / sizeof(XMFLOAT3); i++)
    {
        nowPosData[i].start = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z);    //レイの発射位置
        nowPosData[i].dir = direction[i];        //レイの方向
        Model::RayCast(hGroundModel, &nowPosData[i]);  //レイを発射
    }

    RayCastData vertexCollision[VERTEX_MAX];
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexCollision[i].start = transform_.position_;
        vertexCollision[i].dir = Transform::Float3Sub(vertexBonePos[i], transform_.position_);
        Model::RayCast(hGroundModel, &vertexCollision[i]);  //レイを発射
    }

    //横の当たり判定
    RayCastData vertexCollision[VERTEX_MAX];
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexCollision[i].start = transform_.position_;
        vertexCollision[i].dir = Transform::Float3Sub(vertexBonePos[i], transform_.position_);
        Model::RayCast(hGroundModel, &vertexCollision[i]);  //レイを発射
    }



    /////////////////////////////////////////////////////

    //中心から角までの距離
    float vertexDistance[VERTEX_MAX];
    //中心から角までの距離を求める
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexDistance[i] = Transform::FloatDistance(transform_.position_, vertexBonePos[i]);
    }
    //distがvertexDistanceより短ければ当たっている
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        if (vertexCollision[i].dist < vertexDistance[i])
        {
            if (i != lowest)
            {
                int b = 0;
            }
        }
    }

    //もし下に地面があったら
    if (nowLowPosData.hit && nowLowPosData.dist > accel)
    //if (nowPosData[BOTOM].hit && nowPosData[BOTOM].dist > accel)
    {           
        //接地フラグを真にする
        isGround = false;

        //重力
        if (SPEED_LIMIT >= accel)
        {
            Time::UnLock();
            accel += FALL_SPEED;
            transform_.position_.y -= accel;
        }
        else
        {
            Time::Lock();
            transform_.position_.y -= SPEED_LIMIT;
        }
    }
    else //もし下に地面がなかったら
    {
        accel = 0.0f;

        Time::Lock();
        XMFLOAT3 lowDistance2 = { abs(transform_.position_.x - vertexBonePos[lowest].x),  abs(transform_.position_.y - vertexBonePos[lowest].y),  abs(transform_.position_.z - vertexBonePos[lowest].z) };
        XMFLOAT3 lowDistance = { abs(prevPos.x - pravBonePos[lowest].x),  abs(prevPos.y - pravBonePos[lowest].y),  abs(prevPos.z - pravBonePos[lowest].z) };
        transform_.position_.y -= nowPosData[BOTOM].dist - lowDistance2.y;
        //transform_.position_.y -= prevPosData.dist - SYARI_SIZE_Y;
        
        //接地フラグを真にする
        isGround = true;
    }

    //ゴールしたら
    if (GoalData.hit)
    {
        transform_.position_.y = 10000;
    }

    RedBox* pRedBox = (RedBox*)FindObject("RedBox");    //RedBoxを探す（一番下の頂点に）
    BlueBox* pBlueBox = (BlueBox*)FindObject("BlueBox");//BlueBoxを探す（transform_.positionに）
    pRedBox->SetPosition(vertexBonePos[highest]);
    pBlueBox->SetPosition(vertexBonePos[lowest]);

    //ポリラインに現在の位置を伝える
    pLine->AddPosition(transform_.position_);

    //動かす前の位置を保存しておく
    prevPos = transform_.position_;
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        pravBonePos[i] = vertexBonePos[i];
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
    //SPACEキーを押したとき
    if (Input::IsKey(DIK_SPACE))
    {
        breakFlag = true;
    }
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
    //Aキーを押したとき
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.z += 0.3f;
    }
    //Dキーを押したとき
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.z -= 0.3f;
    }
    //Wキーを押したとき
    if (Input::IsKey(DIK_W))
    {
        //シャリの向き
        //syariDir.z += 90;
        //transform_.position_.z += SYARI_SPEED;
       //transform_.rotate_.x += 0.3f;
        Controller* pController = (Controller*)FindObject("Controller");
        transform_.rotate_.y = pController->GetRotate().y;
        XMFLOAT3 move = { 0,0,0.1f };//プレイヤーの移動ベクトル
        XMVECTOR vMove = XMLoadFloat3(&move);//移動ベクトルの型をXMVECTORに変換
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        vMove = XMVector3TransformCoord(vMove, mRotate);
        XMVECTOR vPos;
        vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
        vPos -= vMove * 3;
        XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る
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

void Syari::Jump()
{
    if (isGround)
    {
        accel -= SPEED_OF_JUMP;
    }
}

