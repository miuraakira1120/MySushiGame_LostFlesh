#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	/// <summary>
	/// XMFloat3�̑����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b);

	/// <summary>
	/// XMFloat3�̈����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b);

	/// <summary>
	///  XMFloat3��xyz�ɓ�����������
	/// </summary>
	/// <param name="a">XMFloat3�̂������鐔</param>
	/// <param name="b">XMFloat3��x�ɂ����鐔</param>
	/// <param name="c">XMFloat3��y�ɂ����鐔</param>
	/// <param name="d">XMFloat3��z�ɂ����鐔</param>
	/// <returns></returns>
	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b, float c, float d);

	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b);

	/// <summary>
	/// XMFloat3�̕����̔��]
	/// </summary>
	/// <param name="����1 : ���]���鐔"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Reverse(XMFLOAT3 a);

	/// <summary>
	/// Transform���s�N�Z���ɕϊ�
	/// </summary>
	/// <param name="transform"></param>
	/// <returns></returns>
	XMFLOAT3 TransformToPixel(const XMFLOAT3& transform);

	/// <summary>
	/// �s�N�Z����Transform�ɕϊ�
	/// </summary>
	/// <param name="pixel"></param>
	/// <returns></returns>
	XMFLOAT3 PixelToTransform(const XMFLOAT3& pixel);
};

