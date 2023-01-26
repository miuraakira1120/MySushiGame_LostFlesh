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

#include <map>

using std::vector;

//コンストラクタ
Syari::Syari(GameObject* parent)
    :GameObject(parent, "Syari"), hModel_(-1), mode(1), axisPos(0.5f, 0.5f, 1.0f),
    prevPos(0.0f, 0.0f, 0.0f), accel(0.0f), jumpSpeed(0), pGauge_(nullptr),isGround(false)
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
    /*vertexBonePos[0] = Model::GetBonePosition(hModel_, "joint1");
    vertexBonePos[1] = Model::GetBonePosition(hModel_, "joint2");*/

    //transform_.SetAxisTrans(axisPos);
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    Goal* pGoal = (Goal*)FindObject("Goal");        //ゴールオブジェクトを探す
    int hGoalModel = pGoal->GetModelHandle();       //モデル番号を取得

    XMMATRIX m =
        XMMatrixTranslation(axisPos.x, axisPos.y, axisPos.z) *
        XMMatrixRotationZ(XMConvertToRadians((int)transform_.rotate_.z % 360)) *
        XMMatrixRotationY(XMConvertToRadians((int)transform_.rotate_.y % 360)) *
        XMMatrixRotationX(XMConvertToRadians((int)transform_.rotate_.x % 360)) *
        XMMatrixTranslation(-(axisPos.x), -(axisPos.y), -(axisPos.z));//軸でrotate_度回転させる行列
    //XMFLOAT3 fRotate = { 0,0,0 };
    //vector<XMVECTOR> v;
    //for (int i = 0; i < vVertexPos.size(); i++)
    //{
    //    v.push_back(XMVector3TransformCoord(vVertexPos[i], m ));
    //}
    //XMVECTOR vAxis = XMLoadFloat3(&axisPos);
    //XMVECTOR vPos = XMLoadFloat3(&transform_.rotate_);
    //XMVector3TransformCoord(vPos, XMMatrixRotationAxis(vAxis, XMConvertToRadians(90)));
    //XMStoreFloat3(&transform_.rotate_, vPos);
    //float lowest = 0;
    //float highest = 0;
    //for (int i = 1; i < v.size(); i++)
    //{
    //    if ( XMVectorGetY(v[lowest]) > XMVectorGetY(v[i]))
    //    {
    //        lowest = i;
    //    }
    //    if (XMVectorGetY(v[highest]) < XMVectorGetY(v[i]))
    //    {
    //        highest = i;
    //    }
    //}
    ////一番低い角のposition
    //XMFLOAT3 lowestPos = {
    //    XMVectorGetX(v[lowest]) + transform_.position_.x,
    //    XMVectorGetY(v[lowest]) + transform_.position_.y,
    //    XMVectorGetZ(v[lowest]) + transform_.position_.z
    //};
    ////一番高い角のposition
    //XMFLOAT3 highestPos = {
    //    XMVectorGetX(v[highest]) + transform_.position_.x,
    //    XMVectorGetY(v[highest]) + transform_.position_.y,
    //    XMVectorGetZ(v[highest]) + transform_.position_.z
    //};
    //RayCastData lowestData;                     //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    //lowestData.start = lowestPos;               //レイの発射位置
    //lowestData.dir = XMFLOAT3(0, -1, 0);        //レイの方向
    //Model::RayCast(hGroundModel, &lowestData);  //レイを発射
    ////レイが当たったら
    //if (lowestData.hit)
    //{
    //}
    //else
    //{
    //    //RayCastData posData;
    //    //posData.start = transform_.position_;   //レイの発射位置
    //    //posData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    //    //Model::RayCast(hGroundModel, &posData); //レイを発射
    //    //float distance = abs(lowestPos.y) + abs(transform_.position_.y);//一番低い角と一番高い角の距離を求める
    //}
    //RedBox* pRedBox = (RedBox*)FindObject("RedBox");    //RedBoxを探す（一番下の頂点に）
    //BlueBox* pBlueBox = (BlueBox*)FindObject("BlueBox");//BlueBoxを探す（transform_.positionに）
    //pRedBox->SetPosition(highestPos);
    //pBlueBox->SetPosition(transform_.position_);

    ////////////////////レイを飛ばす/////////////////////
    
    RayCastData GoalData;                       //シャリの位置からレイを飛ばして、ゴールとぶつかるかを調べる
    GoalData.start = transform_.position_;      //レイの発射位置
    GoalData.dir = XMFLOAT3(0, -1, 0);          //レイの方向
    Model::RayCast(hGoalModel, &GoalData);      //レイを発射

    RayCastData prevPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    prevPosData.start = prevPos/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    prevPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &prevPosData); //レイを発射

    RayCastData nowPosData[6];
    for (int i = 0; i < sizeof(direction) / sizeof(XMFLOAT3); i++)
    {
        //一番低い角からレイを飛ばして、床とぶつかるかを調べる
        nowPosData[i].start = XMFLOAT3(transform_.position_.x, transform_.position_.y + directionDistance[i], transform_.position_.z);    //レイの発射位置
        nowPosData[i].dir = direction[i];        //レイの方向
        Model::RayCast(hGroundModel, &nowPosData[i]);  //レイを発射
    }
    // ///////////////////////////////////////////////////

    for (int i = LEFT; i < DIRECTION_MAX; i++)
    {
        if (nowPosData[i].hit && nowPosData[i].dist >= FALL_SPEED)
        {

        }
    }

    //もし下に地面があったら
    if (nowPosData[BOTOM].hit && nowPosData[BOTOM].dist > accel)
    {           
        //接地フラグを真にする
        isGround = false;
        ////重力
        //if (FALL_SPEED - accel <= SPEED_LIMIT)
        //{
        //    Time::UnLock();

        //    accel += ACCELERATION;
        //    transform_.position_.y -= FALL_SPEED * (accel);
        //}
        //else
        //{
        //    transform_.position_.y -= FALL_SPEED;
        //}

        ////重力
        //if (SPEED_LIMIT >= accel)
        //{
        //    Time::UnLock();
        //    accel += FALL_SPEED;
        //    transform_.position_.y -= accel;
        //}
        //else
        //{
        //    Time::Lock();
        //    transform_.position_.y -= SPEED_LIMIT;
        //}
    }
    else //もし下に地面がなかったら
    {
        //accel = 0.0f;

        //Time::Lock();
        //transform_.position_.y -= prevPosData.dist - SYARI_SIZE_Y;
        //
        ////接地フラグを真にする
        //isGround = true;
    }

    //ゴールしたら
    if (GoalData.hit)
    {
        transform_.position_.y = 10000;
    }
    
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR axisVec = { 0.1, 0, 0, 0};
    XMMATRIX mmm = XMMatrixRotationAxis(axisVec, XMConvertToRadians(10));
    mmm * 0.1;
    mmm = XMMatrixRotationX(XMConvertToRadians(1));   //X軸で45°回転させる行列
    //transform_.rotate_.x += 1;
    vPos = XMVector3TransformCoord(vPos, mmm);	//ベクトルｖを行列ｍで変形
    XMStoreFloat3(&transform_.position_, vPos);

    //動かす前の位置を保存しておく
    prevPos = transform_.position_;
}

//描画
void Syari::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Syari::Release()
{
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

