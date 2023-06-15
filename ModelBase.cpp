#include "ModelBase.h"
#include "Engine/Model.h"

//コンストラクタ
ModelBase::ModelBase(GameObject* parent, std::string filename)
    :GameObject(parent, "ModelBase"), hModel_(-1)
{
    SetPathName(filename); 
}

//デストラクタ
ModelBase::~ModelBase()
{
}

//初期化
void ModelBase::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(pathName_);
    assert(hModel_ >= 0);
}

//更新
void ModelBase::Update()
{
}

//描画
void ModelBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void ModelBase::Release()
{
}