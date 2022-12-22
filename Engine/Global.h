#pragma once
#include "Direct3D.h"

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

/// <summary>
/// 距離を求める関数
/// </summary>
/// <param name="引数1 : 位置1"></param>
/// <param name="引数2 : 位置2"></param>
/// <returns></returns>
XMFLOAT3 FindDistance(XMFLOAT3 a, XMFLOAT3 b)
{
	XMVECTOR aD = XMLoadFloat3(&a);
	XMVECTOR bD = XMLoadFloat3(&b);

	std::abs()
	return 
}