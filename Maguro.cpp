#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"



//コンストラクタ
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1),fallFlag(false),
    pravPos(0.0f,0.0f,0.0f), pSyari(nullptr),pStage(nullptr), hSyariModel(0), 
    hGroundModel(0)
{
}

//デストラクタ
Maguro::~Maguro()
{
}

//初期化
void Maguro::Initialize()
{
    transform_.position_.y = SYARI_SIZE_Y + MAGURO_SIZE_Y;

    //モデルデータのロード
    hModel_ = Model::Load("maguro.fbx");
    assert(hModel_ >= 0);

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    AddCollider(collision);
}

//更新
void Maguro::Update()
{
    pSyari = (Syari*)FindObject("Syari");    //Syariオブジェクトを探す
    hSyariModel = pSyari->GetModelHandle();     //モデル番号を取得
    pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    RayCastData stageRay;
    stageRay.start = GetParentPos();         //レイの発射位置
    //data.start.y = 0;
    stageRay.dir = XMFLOAT3(0, -1, 0);       //レイの方向

    RayCastData syariRay;
    syariRay.start = GetParentPos();         //レイの発射位置
    //data1.start.y = 0;
    syariRay.dir = XMFLOAT3(0, -1, 0);       //レイの方向

    Model::RayCast(hGroundModel, &stageRay); //レイを発射
    Model::RayCast(hSyariModel, &syariRay);  //レイを発射

    //下にシャリがなかったら
    if (!syariRay.hit)
    {
        fallFlag = true;
        transform_.position_.y -= 0.01;
        transform_.ChangeParentRotate(1);
    }
    
    //マグロがシャリの上に乗っていたら
    if (!fallFlag)
    {
        if ((int)pSyari->GetRotate().z % ROTATE_MAX > FALL_ANGLE)
        {
            transform_.position_.x -= FALL_SPEED * ((int)pSyari->GetRotate().z % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().z % ROTATE_MAX < -FALL_ANGLE)
        {
            transform_.position_.x -= FALL_SPEED * ((int)pSyari->GetRotate().z % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().x % ROTATE_MAX > FALL_ANGLE)
        {
            transform_.position_.z += FALL_SPEED * ((int)pSyari->GetRotate().x % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().x % ROTATE_MAX < -FALL_ANGLE)
        {
            transform_.position_.z += FALL_SPEED * ((int)pSyari->GetRotate().x % ROTATE_MAX);
        }
    }
    pravPos = transform_.position_;//自分の今の場所を1f前の場所変数に入れる
}

//描画
void Maguro::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Maguro::Release()
{
}

//何かに当たった
void Maguro::OnCollision(GameObject* pTarget)
{ 
}



