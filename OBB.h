#include <vector>
#include <DirectXMath.h>
#include <directxmath.h>

using namespace DirectX;

class OBB
{
	XMVECTOR pos;				   // 位置
	XMVECTOR normalDirect[3];	   // 方向ベクトル
	float fLength[3];              // 各軸方向の長さ

public:
	void SetPos(XMVECTOR position);
	void SetNormalDirect(XMVECTOR direct1, XMVECTOR direct2, XMVECTOR direct3);
	void SetLength(float length1, float length2, float length3);
	/// <summary>
	/// OBBのセットを一気にやる関数
	/// </summary>
	/// <param name="position">OBB判定の位置</param>
	/// <param name="direct1">OBB判定の方向ベクトル</param>
	/// <param name="direct2">OBB判定の方向ベクトル</param>
	/// <param name="direct3">OBB判定の方向ベクトル</param>
	/// <param name="length1">OBB判定の方向の長さ</param>
	/// <param name="length2">OBB判定の方向の長さ</param>
	/// <param name="length3">OBB判定の方向の長さ</param>
	void SetOBBAll(XMVECTOR position, XMVECTOR direct1, XMVECTOR direct2, XMVECTOR direct3, float length1, float length2, float length3);

	XMVECTOR GetDirect(int elem);   // 指定軸番号の方向ベクトルを取得
	float GetLen_W(int elem);       // 指定軸方向の長さを取得
	XMVECTOR GetPos_W();            // 位置を取得
};