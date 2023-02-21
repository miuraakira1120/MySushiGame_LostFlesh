#include "Cannon.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Ball.h"

//コンストラクタ
Cannon::Cannon(GameObject* parent)
    :GameObject(parent, "Cannon"), hModel_(-1),timer(0)
{
}

//デストラクタ
Cannon::~Cannon()
{
}

//初期化
void Cannon::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Cannon_kari.fbx");
    assert(hModel_ >= 0);

    //Model::SetAnimFrame(hModel_, 1, 3000, 3.0f);

    transform_.rotate_.z = 50.0f;

    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得
    RayCastData data;
    data.start = transform_.position_;   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &data); //レイを発射

     //レイが当たったら
    if (data.hit)
    {
        //その分位置を下げる
        transform_.position_.y -= data.dist - CANNON_SIZE_Y;
    }
}

//更新
void Cannon::Update()
{
    /*XMFLOAT3 CannonFront = Model::GetBonePosition(hModel_, "Cannon_Front");
    XMFLOAT3 CannonBack = Model::GetBonePosition(hModel_, "Cannon_Back");*/
   
    if (timer >=60)
    {
        XMFLOAT3 CannonFront = Transform::Float3Add({ 1.5f,2,0 }, transform_.position_);
        XMFLOAT3 CannonBack = transform_.position_;
            XMVECTOR vCannonFront = XMLoadFloat3(&CannonFront);
            XMVECTOR vCannonBack = XMLoadFloat3(&CannonBack);

            XMFLOAT3 fBallMove;
            XMVECTOR vBallMove = vCannonFront - vCannonBack;
            vBallMove = XMVector3Normalize(vBallMove);
            vBallMove *= 0.5;
            XMStoreFloat3(&fBallMove, vBallMove);

            Ball* pBall = Instantiate<Ball>(this->GetParent());
            pBall->SetPosition(CannonBack);
            pBall->SetMove(fBallMove);

            timer = 0;
    }
    timer++;
   /* Syari* pSyari = (Syari*)FindObject("Syari");
    transform_.position_ = pSyari->GetPosition();*/
}

//描画
void Cannon::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Cannon::Release()
{
}