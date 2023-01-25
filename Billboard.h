#pragma once
#include "Engine/Direct3D.h"
#include "Engine/Texture.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;

//コンスタントバッファー
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMFLOAT4	color;
};

//頂点情報
struct VERTEX
{
	XMFLOAT3 position;
	XMFLOAT3 uv;
};


//常にカメラの方を向く四角形ポリゴン
class BillBoard
{
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;	//画像

public:
	BillBoard();
	~BillBoard();

	//ロード
	//引数：fileName	画像ファイル名
	//戻値：成功/失敗
	HRESULT Load(std::string fileName);

	//描画
	//引数：matrix	変換行列（ワールド行列）
	//引数：color	色
	void Draw(XMMATRIX matWorld, XMFLOAT4 color);

	//解放
	void Release();
};