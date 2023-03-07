#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Time.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1),fallFlag(false),
    prevPos(0.0f,0.0f,0.0f), pSyari(nullptr),pStage(nullptr), hSyariModel(-1), 
    hGroundModel(-1),vertexBonePos(),pParticle_(nullptr)
{
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
    hModel_ = Model::Load("Maguro.fbx");
    assert(hModel_ >= 0);

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
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
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
    nowLowPosData.start = { vertexBonePos[lowest].x,vertexBonePos[lowest].y + 3,vertexBonePos[lowest].z };  /*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowLowPosData); //レイを発射

    RayCastData nowHightPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowHightPosData.start = vertexBonePos[highest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowHightPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowHightPosData); //レイを発射

    if (nowLowPosData.pos.y >= vertexBonePos[lowest].y)
    {
       SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
       pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }

    //シャリの物理演算
    PhysicalOperation();
    
    prevPos = transform_.position_;//自分の今の場所を1f前の場所変数に入れる
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

    XMFLOAT3 syariUpDistanceDifference = pSyari->GetUpDistanceDifference();
    //マグロがシャリの上に乗っていたら
    //if (!syariData.hit)
    {
        //右と手前のほう高ければ＋
        //左の奥ほう高ければ－
        if (syariUpDistanceDifference.z > FALL_ANGLE || syariUpDistanceDifference.z < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.z > FALL_ANGLE && FALL_ANGLE > 0)
            {
                transform_.position_.x += FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
            else
            {
                transform_.position_.x -= FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
        }
        if (syariUpDistanceDifference.x > FALL_ANGLE || syariUpDistanceDifference.x < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.x > FALL_ANGLE && FALL_ANGLE > 0)
            {
                transform_.position_.z -= FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
            else
            {
                transform_.position_.z += FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
        }
    }

    if (abs(transform_.position_.x) > SYARI_SIZE_X || abs(transform_.position_.z) > SYARI_SIZE_Z)
    {

        //落下してくれ
        transform_.position_.y -= 0.1f;
    }
        //下にシャリがなかったら
}




