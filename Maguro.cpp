#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Time.h"

//コンストラクタ
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(),fallFlag(false),
    prevPos(0.0f,0.0f,0.0f), pSyari(nullptr),pStage(nullptr), hSyariModel(0), 
    hGroundModel(0)
{
    for (int i = 0; i < sizeof(hModel_) / sizeof(int); i++)
    {
        hModel_[i] = -1;
    }
}

//デストラクタ
Maguro::~Maguro()
{
}

//初期化
void Maguro::Initialize()
{
    //初期位置の設定
    transform_.position_.y = SYARI_SIZE_Y + MAGURO_SIZE_Y;

    //モデルデータのロード
    hModel_[0] = Model::Load("maguro.fbx");
    assert(hModel_[0] >= 0);

    //当たり判定の生成
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 0.5f, 3));
    AddCollider(collision);

    pParticle_ = Instantiate<Particle>(this);
}

//更新
void Maguro::Update()
{
    //オブジェクトを探して、ポインタに入れる
    FindAllObject();

    //各頂点の位置を調べる
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_[0], vertexName[i]);
    }

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

    RayCastData nowLowPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowLowPosData.start = vertexBonePos[lowest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowLowPosData); //レイを発射

    if (!nowLowPosData.hit)
    {
        //炎
        {
            EmitterData data;

            //炎
            data.textureFileName = "Cloud.png";
            data.position = XMFLOAT3(-4, 1.5, -4);
            data.positionErr = XMFLOAT3(0.1, 0, 0.1);
            data.delay = 5;
            data.number = 1;
            data.lifeTime = 60;
            data.gravity = -0.002f;
            data.dir = XMFLOAT3(0, 0, 0);
            data.dirErr = XMFLOAT3(0, 0, 0);
            data.speed = 0.01f;
            data.speedErr = 0.0;
            data.size = XMFLOAT2(1.5, 1.5);
            data.sizeErr = XMFLOAT2(0.4, 0.4);
            data.scale = XMFLOAT2(1.01, 1.01);
            data.color = XMFLOAT4(0.5, 1, 0, 1);
            data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
            pParticle_->Start(data);
            transform_.position_ = prevPos;
        }
    }

    //シャリの物理演算
    PhysicalOperation();
    
    prevPos = transform_.position_;//自分の今の場所を1f前の場所変数に入れる
}

//描画
void Maguro::Draw()
{
    Model::SetTransform(hModel_[0], transform_);
    Model::Draw(hModel_[0]);
}

//開放
void Maguro::Release()
{
}

//何かに当たった
void Maguro::OnCollision(GameObject* pTarget)
{ 
}

//オブジェクトを探して、ポインタに入れる
void Maguro::FindAllObject()
{
    pSyari = (Syari*)FindObject("Syari");    //Syariオブジェクトを探す
    hSyariModel = pSyari->GetModelHandle();  //モデル番号を取得

    pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    hGroundModel = pStage->GetModelHandle(); //モデル番号を取得
}

//レイを飛ばす
RayCastData Maguro::DoRay(XMFLOAT3 start, XMFLOAT3 dir, int hModel)
{
    RayCastData rayData;
    rayData.start = start;
    rayData.dir = dir;
    Model::RayCast(hModel, &rayData);
    return rayData;
}

void Maguro::PhysicalOperation()
{
    RayCastData syariData = DoRay(GetParentPos(), XMFLOAT3(0, -1, 0), hSyariModel);
    //マグロがシャリの上に乗っていたら
    //if (!syariData.hit)
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

    if (abs(transform_.position_.x) > SYARI_SIZE_X || abs(transform_.position_.z) > SYARI_SIZE_Z)
    {
        //落下してくれ
        transform_.position_.y -= 0.1;
    }
        //下にシャリがなかったら
}




