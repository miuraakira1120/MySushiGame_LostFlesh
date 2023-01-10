#pragma once
#include <DirectXMath.h>

using namespace DirectX;

enum TransMode
{
	TRANS_NORMAL_MODE,			//基本的な座標
	TRANS_AXIS_MODE,			//軸を移動して回転するか
	TRANS_CHANGEPARENT_MODE,	//親を変えて移動
	TRANS_MAX,
};

//-----------------------------------------------------------
//位置、向き、拡大率などを管理するクラス
//-----------------------------------------------------------
class Transform
{
private:
	unsigned int transMode;			//軸を移動して回転するか
	
public:
	XMMATRIX matTranslate_;		//移動行列
	XMMATRIX matRotate_;		//回転行列	
	XMMATRIX matScale_;			//拡大行列
	XMFLOAT3 position_;			//位置
	XMFLOAT3 rotate_;			//向き
	XMFLOAT3 scale_;			//拡大率
	Transform * pParent_;		//親オブジェクトの情報
	XMFLOAT3 axisMatrix_;		//このマトリクスを軸に回転する
	Transform* transParentTmp;	//親をさかのぼるために使うポインタ変数
	unsigned int parentNum;		//親をどれくらいさかのぼるか
	unsigned int NumberOfLoops;	//何回ループしたか
	unsigned int pravTransMode;	//1フレーム前のTransMode



	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	//引数：なし
	//戻値：なし
	void Calclation();

	//ワールド行列を取得
	//引数：なし
	//戻値：その時点でのワールド行列
	XMMATRIX GetWorldMatrix();

	/// <summary>
	/// XMFloat3の足し算
	/// </summary>
	/// <param name="引数1 : 足される数"></param>
	/// <param name="引数2 : 足す数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
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
	static XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/// <summary>
	/// XMFloat3の符号の反転
	/// </summary>
	/// <param name="引数1 : 反転する数"></param>
	/// <param name="戻値  : XMFLOAT3"></param>
	/// <returns></returns>
	static XMFLOAT3 Float3Reverse(XMFLOAT3 a)
	{
		return XMFLOAT3(-(a.x), -(a.y), -(a.z));
	}

	void NomalAxisRotate();	//軸を移動しないで回転する
	void MoveAxisRotate();  //軸を移動して回転する

	/// <summary>
	/// 回転の親を変える
	/// </summary>
	/// <param name="引数1 parentNum : 何番目の親で回転するか"></param>
	void ChangeParentRotate(int parentNum_);

	void SetAxisTrans(XMFLOAT3 mat);//この軸で回る

	/// <summary>
	/// 距離を求める関数
	/// </summary>
	/// <param name="引数1 : 位置1"></param>
	/// <param name="引数2 : 位置2"></param>
	/// <returns></returns>
	float FindDistance(XMFLOAT3 a, XMFLOAT3 b)
	{
		XMVECTOR aD = XMLoadFloat3(&a);
		XMVECTOR bD = XMLoadFloat3(&b);

		XMVECTOR vResult = aD - bD;

		//return sqrt()

	}
};

