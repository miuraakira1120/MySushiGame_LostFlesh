#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	/// <summary>
	/// XMFloat3の足し算
	/// </summary>
	/// <param name="引数1 : 足される数"></param>
	/// <param name="引数2 : 足す数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b);

	/// <summary>
	/// XMFloat3の引き算
	/// </summary>
	/// <param name="引数1 : 引かれる数"></param>
	/// <param name="引数2 : 引く数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b);

	/// <summary>
	///  XMFloat3のxyzに同じ数かける
	/// </summary>
	/// <param name="a">XMFloat3のかけられる数</param>
	/// <param name="b">XMFloat3のxにかける数</param>
	/// <param name="c">XMFloat3のyにかける数</param>
	/// <param name="d">XMFloat3のzにかける数</param>
	/// <returns></returns>
	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b, float c, float d);

	XMFLOAT3 Float3Mul(XMFLOAT3 a, float b);

	/// <summary>
	/// XMFloat3の符号の反転
	/// </summary>
	/// <param name="引数1 : 反転する数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	XMFLOAT3 Float3Reverse(XMFLOAT3 a);

	/// <summary>
	/// Transformをピクセルに変換
	/// </summary>
	/// <param name="transform"></param>
	/// <returns></returns>
	XMFLOAT3 TransformToPixel(const XMFLOAT3& transform);

	/// <summary>
	/// ピクセルをTransformに変換
	/// </summary>
	/// <param name="pixel"></param>
	/// <returns></returns>
	XMFLOAT3 PixelToTransform(const XMFLOAT3& pixel);

};


