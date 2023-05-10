#include "PlayScene.h"
#include "Syari.h"
#include "Maguro.h"
#include "Stage.h"
#include "Controller.h"
#include "RedBox.h"
#include "BlueBox.h"
#include "Goal.h"
#include "Engine/Camera.h"
#include "Cannon.h"
#include "SalmonRoe.h"
#include "Engine/Image.h"


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pos(0), hPict_(-1)
{
	//D3D11_BUFFER_DESC cb;
	//cb.ByteWidth = sizeof(ConstantBuffer);
	//cb.Usage = D3D11_USAGE_DYNAMIC;
	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cb.MiscFlags = 0;
	//cb.StructureByteStride = 0;

	//// 定数バッファの作成
	//Direct3D::pDevice_->CreateBuffer(&cb, NULL, &pConstantBuffer_);
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Syari>(this);
	Instantiate<Controller>(this);
	Instantiate<Stage>(this);
	Instantiate<RedBox>(this);
	Instantiate<BlueBox>(this);

	////画像データのロード
	//hPict_ = Image::Load("sky.png");
	//assert(hPict_ >= 0);
}

//更新
void PlayScene::Update()
{
	pos += UVSCROLL_SPEED;
}

//描画
void PlayScene::Draw()
{
	//Direct3D::pContext_->VSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());
	//Direct3D::pContext_->PSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());

	//// パラメータの受け渡し
	//D3D11_MAPPED_SUBRESOURCE pdata;

	////空の行列
	////uvを移動させる量
	//ConstantBuffer cb = { XMMatrixIdentity(),pos};

	//Direct3D::pContext_->Map(pConstantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	//memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		                    // リソースへ値を送る
	//Direct3D::pContext_->Unmap(pConstantBuffer_.Get(), 0);									    // GPUからのリソースアクセスを再開

	////描画
	//Image::SetTransform(hPict_, transform_);
	//Image::Draw(hPict_, Direct3D::SHADER_UVSCROLL);
}

//開放
void PlayScene::Release()
{
}
