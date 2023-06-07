#include "PlayerBase.h"
#include "Controller.h"
#include "OBB.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"


//コンストラクタ
PlayerBase::PlayerBase(GameObject* parent, std::string name, std::string modelFilename)
    :GameObject(parent, name, modelFilename),hModel_(-1), isGround(false), gravity(0.0f), canMove(true), size(PLAYER_SIZE)
{
}

//描画
void PlayerBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//ジャンプ
void PlayerBase::Jump()
{
    //陸についていたら
    if (isGround)
    {
        gravity -= SPEED_OF_JUMP;
    }
}

//移動する関数
void PlayerBase::Move(bool isInverse)
{
    //カメラのコントローラーを探す
    Controller* pController = (Controller*)FindObject("Controller");

    //カメラの向きにこのオブジェクトを設定する
    transform_.rotate_.y = pController->GetRotate().y;

    //プレイヤーの移動ベクトル
    XMFLOAT3 move = { 0,0,SYARI_SPEED };

    //移動ベクトルの型をXMVECTORに変換
    XMVECTOR vMove;
    vMove = XMLoadFloat3(&move);

    //移動する向きに回転
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vMove = XMVector3TransformCoord(vMove, mRotate);

    //バックにするならmoveを逆にする
    if (!isInverse)
    {
        vMove *= -1;
    }

    //vMoveをXMFLOAT3に変換
    XMFLOAT3 fMove;
    XMStoreFloat3(&fMove, vMove);

    //シャリの現在地をXMVECTORに変換
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);

    //移動後の座標を計算
    vPos += vMove;

    //現在地をtransform_.position_に送る
    XMStoreFloat3(&transform_.position_, vPos);
}

//重力の処理
void PlayerBase::Gravity()
{
    //スピードの上限に達していなければ
    if (FALL_SPEED_LIMIT >= gravity)
    {
        gravity += FALL_SPEED;
        transform_.position_.y -= gravity;
    }
    else
    {
        transform_.position_.y -= FALL_SPEED_LIMIT;
    }
}

//衝突しているか調べる
bool PlayerBase::CheckIfCollided(int hStageModel, XMFLOAT3 vec, float& length)
{
    //シャリの現在地をXMVECTORに変換
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);

    //OBBに使用するベクトルの元を作成
    XMFLOAT3 fBoneDir[DIRECTION_ARRAY_SIZE] =
    {
        {size.x, 0, 0},
        {0, size.y, 0},
        {0, 0, size.z},
    };

    //OBBに使用するベクトルを作成
    //DIRECTIONの分ループする
    std::vector<XMVECTOR> dirVec;
    for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++)
    {
        //fBoneDirをXMVECTORに変換
        XMVECTOR vBoneDir = XMLoadFloat3(&fBoneDir[i]);

        //BoneDirを行列ｍで変形
        vBoneDir = XMVector3TransformCoord(vBoneDir, transform_.changeMatRotate_);	

        //vBoneDirにポジションを足す
        vBoneDir += vPos;

        //XMFLOATに直す
        XMStoreFloat3(&fBoneDir[i], vBoneDir);

        //リストに追加する
        dirVec.push_back(vBoneDir - vPos);
    }

    //OBBに使用するベクトルの長さを取得
    std::vector<float> fLength;
    for (int i = 0; i < fLength.size() - 1; i++)
    {
        //リストに追加する
        fLength.push_back(XMVectorGetX(XMVector3Length(dirVec[i])));
    }

    //プレイヤーのOBBを設定
    OBB prayerOBB;
    prayerOBB.SetOBBAll(vPos, dirVec, fLength);

    //床のOBB衝突判定
    RayCastData prayerOBBData;
    prayerOBBData.start = transform_.position_;   //レイの発射位置
    prayerOBBData.dir = vec;                      //レイの方向
    Model::RayCast(hStageModel, &prayerOBBData);  //レイを発射

    float len;
    //レイが当たっていて、衝突していたら
    if (prayerOBBData.hit && prayerOBB.OBBvsPlane(prayerOBB, prayerOBBData.pos, prayerOBBData.normal, &len))
    {
        length = len;
        return TRUE;
    }
    return FALSE;
}

//姿勢を地面の法線に添わせる
void PlayerBase::PostureGroundFollow(int hStageModel)
{
    if (isGround)
    {
        //rotate_を使わずに回転
        //回転計算を変える(これをしないと回転しない)
        transform_.SetRotateMode(TRANS_NONROTATE);

        //各軸に対するベクトルを求める
        XMMATRIX rotateX, rotateY, rotateZ;
        rotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
        rotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        rotateZ = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

        //回転行列を求める
        XMMATRIX m = rotateZ * rotateX * rotateY;

        //y軸のベクトルを取得
        XMFLOAT3 fUpVec = { 0, size.y, 0 };

        //XMFLOAT3に変換
        XMVECTOR vUpVec = XMLoadFloat3(&fUpVec);

        //vUpVecを行列ｍで変形
        vUpVec = XMVector3TransformCoord(vUpVec, m);

        //現在地をXMVECTOR型に変換する
        XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

        //fBoneDirVecにvUpVecの逆ベクトルを入れる
        XMFLOAT3 fBoneDirVec;
        XMStoreFloat3(&fBoneDirVec, -vUpVec);

        RayCastData GroundData;                               //シャリの位置からレイを飛ばして、ゴールとぶつかるかを調べる
        GroundData.start = transform_.position_;              //レイの発射位置
        GroundData.dir = fBoneDirVec;                         //レイの方向
        Model::RayCast(hStageModel, &GroundData);             //レイを発射

        XMVECTOR nor = XMVector3Normalize(GroundData.normal); //法線
        XMVECTOR up = XMVector3Normalize(vUpVec);             //上ベクトル

        //外積が0だとまずいので確認
        if (XMVectorGetX(nor) != XMVectorGetX(up) || XMVectorGetY(nor) != XMVectorGetY(up) || XMVectorGetZ(nor) != XMVectorGetZ(up))
        {
            //ベクトル間のラジアン角度求める
            float dot = XMVectorGetX(XMVector3Dot(XMVector3Normalize(nor), XMVector3Normalize(up)));

            //外積求める
            XMVECTOR cross = XMVector3Cross(nor, up);

            if (dot >= -1 && dot != 0 && dot <= 1)
            {
                XMMATRIX y;
                y = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
                //回転行列求める
                transform_.changeMatRotate_ = y * XMMatrixRotationAxis(cross, -acos(dot));
            }
        }
        else
        {
            XMMATRIX x, y, z;
            x = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
            y = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
            z = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
            XMMATRIX mat = z * x * y;
            transform_.changeMatRotate_ = mat;
        }
    }
}
