#include "ModelBase.h"
#include "Engine/Model.h"

//�R���X�g���N�^
ModelBase::ModelBase(GameObject* parent, std::string filename)
    :GameObject(parent, "ModelBase"), hModel_(-1)
{
    SetPathName(filename); 
}

//�f�X�g���N�^
ModelBase::~ModelBase()
{
}

//������
void ModelBase::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load(pathName_);
    assert(hModel_ >= 0);
}

//�X�V
void ModelBase::Update()
{
}

//�`��
void ModelBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void ModelBase::Release()
{
}