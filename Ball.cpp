#include "Ball.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Camera.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1),fMove(), isPrevRayHit(true)
{
}

//デストラクタ
Ball::~Ball()
{
}

//初期化
void Ball::Initialize()
{
    hModel_ = Model::Load("Ball.fbx");
    assert(hModel_ >= 0);
}

//更新
void Ball::Update()
{
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    //一番下の位置からレイを飛ばす
    RayCastData nowLowPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowLowPosData.start = transform_.position_/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowLowPosData); //レイを発射

    transform_.position_ = Transform::Float3Add(transform_.position_, fMove);
    //もし下に地面があったら
    if (nowLowPosData.hit && nowLowPosData.dist - BALL_SIZE_Y > accel)
    {
        //接地フラグを偽にする
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
    else if(isPrevRayHit) //もし下に地面がなかったら
    {
        accel = 0.0f;
        transform_.position_.y -= nowLowPosData.dist - BALL_SIZE_Y;
        //接地フラグを真にする
        isGround = true;
    }

   isPrevRayHit = nowLowPosData.hit;

}

//描画
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ball::Release()
{
}

void Ball::SetMove(XMFLOAT3 move)
{
    fMove = move;
}

void Ball::SetPosition(XMFLOAT3 pos)
{
    transform_.position_ = pos;
}
