#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "ButtonManager.h"
#include "Engine/GameObject.h"

//前方宣言
namespace ShaderManager
{
    enum ShaderType : int;
}

//ボタンを管理するクラス
class Button : public GameObject
{
private:

    //ボタンのコンスタントバッファー
    struct ConstantBuffer
    {
        XMMATRIX	dummy_;		// 空
        int		    value_;		// ボタンの状態
    };

private:

    int hPict_;								//画像番号
    int value_;							    //状態
    bool select_;							//選ばれているか
    bool operationRight_;				    //操作権利

    ShaderManager::ShaderType shaderType_;	//シェーダーの種類

    Microsoft::WRL::ComPtr<ID3D11Buffer>pConstantBuffer_;	//コンスタントバッファ

protected:

    float move_;

private:
    /// <summary>
    /// 選ばれていない
    /// </summary>
    void UnSelect();

    /// <summary>
    /// 選ばれている
    /// </summary>
    void Select();

protected:
    /// <summary>
    /// 押された時の処理
    /// </summary>
    virtual void Event();

   

    /// <summary>
    ///  Update関数の前に呼ばれる関数
    /// </summary>
    virtual void PreUpdate() ;

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="parent">親オブジェクト</param>
    /// <param name="name">オブジェクトの名前</param>
    Button(GameObject* parent, const std::string& name);

    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

    /// <summary>
    /// 解放
    /// </summary>
    void Release() override;
    /// <summary>
    /// 画像の設定
    /// </summary>
    /// <param name="name">画像の名前</param>
    void SetImage(const std::string& name);

    /// <summary>
    /// マウスによるボタン操作の権限剝奪
    /// </summary>
    void NoRight();

    /// <summary>
    /// マウスによるボタン操作の権限付与
    /// </summary>
    void Right();

    

    /// <summary>
    /// value_のゲッター
    /// </summary>
    /// <returns>//変数value_</returns>
    bool GetValue();

};

