#include <DirectXMath.h>

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

using std::vector;

//コンストラクタ
Syari::Syari(GameObject* parent)
    :GameObject(parent, "Syari"), hModel_(-1), mode(1)
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

    //transform_.position_.y = 100;

    Instantiate<Maguro>(this);

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    AddCollider(collision);

}

//更新
void Syari::Update()
{
    if (Input::IsKey(DIK_SPACE))
    {
        breakFlag = true;
    }
    XMFLOAT3 camPos1 = Camera::GetPosition();
    XMVECTOR vSyariCam = XMLoadFloat3(&camPos1) - XMLoadFloat3(&transform_.position_);
    XMFLOAT3 axisPos = { 0.5f, 0.5f, 1.0f };
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
    if (mode == 0)
    {
        transform_.MoveAxisRotate();
    }
    else
    {
        transform_.NomalAxisRotate();
    }
    
    transform_.SetAxisTrans(axisPos);
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    XMMATRIX m =
        XMMatrixTranslation(axisPos.x, axisPos.y, axisPos.z) *
        XMMatrixRotationZ(XMConvertToRadians((int)transform_.rotate_.z % 360)) *
        XMMatrixRotationY(XMConvertToRadians((int)transform_.rotate_.y % 360)) *
        XMMatrixRotationX(XMConvertToRadians((int)transform_.rotate_.x % 360)) *
        XMMatrixTranslation(-(axisPos.x), -(axisPos.y), -(axisPos.z));//軸でrotate_度回転させる行列
    XMFLOAT3 fRotate = { 0,0,0 };

    // ////////キー入力///////////////////////////////
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.z += 0.3f;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.z -= 0.3f;
    }
    if (Input::IsKey(DIK_W))
    {
        transform_.rotate_.x += 0.3f;
    }
    if (Input::IsKey(DIK_S))
    {
        transform_.rotate_.x -= 0.3f;
    }

    ////Aキーが押されていたら
    //if (Input::IsKey(DIK_A))
    //{
    //    fRotate.z += 1.0;
    //}
    ////Dキーが押されていたら
    //if (Input::IsKey(DIK_D))
    //{
    //    fRotate.z -= 1.0;
    //}
    ////Wキーが押されていたら
    //if (Input::IsKey(DIK_W))
    //{
    //    fRotate.x += 1.0;
    //}
    ////Sキーが押されていたら
    //if (Input::IsKey(DIK_S))
    //{
    //    fRotate.x -= 1.0;
    //}
    //if (Input::IsKey(DIK_SPACE))
    //{
    //    breakFlag = true;
    //}
    //D3DXQuaternionRotationMatrix();
    //DirectX::XMMatrixRotationQuaternion(); 
    //Quaternion _quaternion = Quaternion.Identity;
    //DirectX::XMMatrixTransformation(aaa, )
    /*XMVECTOR vRotate;
    vRotate = XMLoadFloat3(&fRotate);
    vRotate = DirectX::XMQuaternionRotationAxis(vRotate, XMConvertToRadians(90));
    XMMATRIX axisRotate = DirectX::XMMatrixRotationQuaternion(vRotate);*/
    /*XMVECTOR nomalRotate = XMVector3Normalize(vRotate) * ROTATE_SPEED;
    vRotate = XMVector3TransformCoord(nomalRotate, m);
    vRotate = XMVector3TransformCoord(vRotate, m);
    XMFLOAT3 ffRotate;
    XMStoreFloat3(&ffRotate, vRotate);
    transform_.rotate_ = Transform::Float3Add(transform_.rotate_, ffRotate);*/

    ////////////////////////////////////////////////////////

    RedBox* pRedBox = (RedBox*)FindObject("RedBox");    //RedBox生成（一番下の頂点に）
    BlueBox* pBlueBox = (BlueBox*)FindObject("BlueBox");//BlueBox生成（transform_.positionに）

    vector<XMVECTOR> v;
    for (int i = 0; i < vVertexPos.size(); i++)
    {
        v.push_back(XMVector3TransformCoord(vVertexPos[i], m ));
    }
    XMVECTOR vAxis = XMLoadFloat3(&axisPos);
    XMVECTOR vPos = XMLoadFloat3(&transform_.rotate_);
    XMVector3TransformCoord(vPos, XMMatrixRotationAxis(vAxis, XMConvertToRadians(90)));
    XMStoreFloat3(&transform_.rotate_, vPos);

    float lowest = 0;
    float highest = 0;
    for (int i = 1; i < v.size(); i++)
    {
        if ( XMVectorGetY(v[lowest]) > XMVectorGetY(v[i]))
        {
            lowest = i;
        }
        if (XMVectorGetY(v[highest]) < XMVectorGetY(v[i]))
        {
            highest = i;
        }
    }

    //一番低い角のposition
    XMFLOAT3 lowestPos = {
        XMVectorGetX(v[lowest]) + transform_.position_.x,
        XMVectorGetY(v[lowest]) + transform_.position_.y,
        XMVectorGetZ(v[lowest]) + transform_.position_.z
    };
    //一番高い角のposition
    XMFLOAT3 highestPos = {
        XMVectorGetX(v[highest]) + transform_.position_.x,
        XMVectorGetY(v[highest]) + transform_.position_.y,
        XMVectorGetZ(v[highest]) + transform_.position_.z
    };

    RayCastData lowestData;
    lowestData.start = lowestPos;   //レイの発射位置
    lowestData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &lowestData); //レイを発射

    float upPos = 0;
    //レイが当たったら
    if (lowestData.hit)
    {
        transform_.position_.y -= 0.1;
    }
    else
    {
        RayCastData posData;
        posData.start = transform_.position_;   //レイの発射位置
        posData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
        Model::RayCast(hGroundModel, &posData); //レイを発射
        float distance = abs(lowestPos.y) + abs(transform_.position_.y);//一番低い角と一番高い角の距離を求める
        upPos = distance - posData.dir.y ;
    }

    if (breakFlag)
    {
        int a = 0;
    }

    transform_.position_.y += upPos;
    pRedBox->SetPosition(highestPos);
    pBlueBox->SetPosition(transform_.position_);

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

XMFLOAT3 Syari::GetPosition()
{
    return transform_.position_;
}

XMFLOAT3 Syari::GetRotate()
{
    return transform_.rotate_;
}

//何かに当たった
void Syari::OnCollision(GameObject* pTarget)
{
   
}