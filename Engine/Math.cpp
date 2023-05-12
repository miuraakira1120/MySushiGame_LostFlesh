#include "Math.h"
#include "Direct3D.h"

namespace Math
{
	/// <summary>
	/// XMFloat3�̑����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/// <summary>
	/// XMFloat3�̈����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/// <summary>
	///  XMFloat3��xyz�ɓ�����������
	/// </summary>
	/// <param name="a">XMFloat3�̂������鐔</param>
	/// <param name="b">XMFloat3��x�ɂ����鐔</param>
	/// <param name="c">XMFloat3��y�ɂ����鐔</param>
	/// <param name="d">XMFloat3��z�ɂ����鐔</param>
	/// <returns></returns>
	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b, float c, float d)
	{
		return XMFLOAT3(a.x * b, a.y * c, a.z * d);
	}

	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b)
	{
		return XMFLOAT3(a.x * b, a.y * b, a.z * b);
	}

	/// <summary>
	/// XMFloat3�̕����̔��]
	/// </summary>
	/// <param name="����1 : ���]���鐔"></param>
	/// <param name="�ߒl  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Reverse(XMFLOAT3 a)
	{
		return XMFLOAT3(-(a.x), -(a.y), -(a.z));
	}

	/// <summary>
	/// Transform���s�N�Z���ɕϊ�
	/// </summary>
	/// <param name="transform"></param>
	/// <returns></returns>
	XMFLOAT3 TransformToPixel(const XMFLOAT3& transform)
	{
		//position_��0~1�ɕύX
		XMFLOAT3 pos = { (transform.x + 1) / 2, (-transform.y + 1) / 2, transform.z };
		pos = { pos.x * Direct3D::screenWidth_, pos.y * Direct3D::screenHeight_, pos.z };

		return pos;
	}

	/// <summary>
	/// �s�N�Z����Transform�ɕϊ�
	/// </summary>
	/// <param name="pixel"></param>
	/// <returns></returns>
	XMFLOAT3 PixelToTransform(const XMFLOAT3& pixel)
	{
		XMFLOAT3 pos = { pixel.x / Direct3D::screenWidth_, pixel.y / Direct3D::screenHeight_, pixel.z };
		pos = { pos.x * 2 - 1, -pos.y * 2 + 1, pos.z };

		return pos;
	}
}