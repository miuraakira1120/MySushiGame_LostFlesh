#pragma once
#include "Direct3D.h"

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

/// <summary>
/// ���������߂�֐�
/// </summary>
/// <param name="����1 : �ʒu1"></param>
/// <param name="����2 : �ʒu2"></param>
/// <returns></returns>
XMFLOAT3 FindDistance(XMFLOAT3 a, XMFLOAT3 b)
{
	XMVECTOR aD = XMLoadFloat3(&a);
	XMVECTOR bD = XMLoadFloat3(&b);

	std::abs()
	return 
}