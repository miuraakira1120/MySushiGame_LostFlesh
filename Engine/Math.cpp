#include "Math.h"
#include "Direct3D.h"

namespace Math
{
	/// <summary>
	/// XMFloat3の足し算
	/// </summary>
	/// <param name="引数1 : 足される数"></param>
	/// <param name="引数2 : 足す数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/// <summary>
	/// XMFloat3の引き算
	/// </summary>
	/// <param name="引数1 : 引かれる数"></param>
	/// <param name="引数2 : 引く数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/// <summary>
	///  XMFloat3のxyzに同じ数かける
	/// </summary>
	/// <param name="a">XMFloat3のかけられる数</param>
	/// <param name="b">XMFloat3のxにかける数</param>
	/// <param name="c">XMFloat3のyにかける数</param>
	/// <param name="d">XMFloat3のzにかける数</param>
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
	/// XMFloat3の符号の反転
	/// </summary>
	/// <param name="引数1 : 反転する数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Reverse(XMFLOAT3 a)
	{
		return XMFLOAT3(-(a.x), -(a.y), -(a.z));
	}

	/// <summary>
	/// Transformをピクセルに変換
	/// </summary>
	/// <param name="transform"></param>
	/// <returns></returns>
	XMFLOAT3 TransformToPixel(const XMFLOAT3& transform)
	{
		//position_を0~1に変更
		XMFLOAT3 pos = { (transform.x + 1) / 2, (-transform.y + 1) / 2, transform.z };
		pos = { pos.x * Direct3D::screenWidth_, pos.y * Direct3D::screenHeight_, pos.z };

		return pos;
	}

	/// <summary>
	/// ピクセルをTransformに変換
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