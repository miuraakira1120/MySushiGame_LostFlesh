#include <vector>
#include <DirectXMath.h>
#include <directxmath.h>

using namespace DirectX;

class OBB
{
	XMVECTOR Pos;				   // 位置
	XMVECTOR NormaDirect[3];	   // 方向ベクトル
	float fLength[3];              // 各軸方向の長さ

public:
	XMVECTOR GetDirect(int elem);   // 指定軸番号の方向ベクトルを取得
	float GetLen_W(int elem);       // 指定軸方向の長さを取得
	XMVECTOR GetPos_W();            // 位置を取得
};