#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"


//コンストラクタ
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1),fallFlag(false),pravPos(0.0f,0.0f,0.0f)
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

    //transform_.position_.x = 3;
}

//更新
void Maguro::Update()
{
    Syari* pSyari = (Syari*)FindObject("Syari");    //Syariオブジェクトを探す
    int hSyariModel = pSyari->GetModelHandle();    //モデル番号を取得
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得
    
    ////スペースキーが押されていたら
    //if (Input::IsKey(DIK_A))
    //{
    //    //何らかの処理
    //    transform_.position_.x -= 0.2;
    //}
    //if (Input::IsKey(DIK_D))
    //{
    //    //何らかの処理
    //    transform_.position_.x += 0.2;
    //}

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
        //transform_.rotate_ = GetParent()->GetRotate();
        //なんかいろいろ処理する
        //transform_.rotate_.z -= 0.25;
        transform_.position_.y -= 0.01;

        //transform_.rotate_ = Transform::Float3Reverse((GetParent()->GetRotate()));
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


