//============================
//
// ２Dpolygon設定
// Author:Yuda Kaito
//
//============================

#include "blackout.h"
#include "utility.h"
#include "manager.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CBlackOut::CBlackOut() :CObject2d(3)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CBlackOut::~CBlackOut()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CBlackOut::Init()
{
	CObject2d::Init();

	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CBlackOut::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CBlackOut::Update()
{
	CObject2d::Update();
	//動き
	move();
}

//------------------------------------
// 描画
//------------------------------------
void CBlackOut::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBlackOut *CBlackOut::Create()
{
	CBlackOut * pObject = new CBlackOut;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// スクリーンサイズ
		
		pObject->Init();
		pObject->SetPos(popPos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);		// テクスチャ選択
		pObject->SetMove(D3DXVECTOR3(0.0f, 1.75f, 0.0f));		// moveの設定
		pObject->SetSize(CManager::Pos);	// サイズ設定
		pObject->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	// 色設定
	}
	return pObject;
}


//------------------------------------
// 動き系統
//------------------------------------
void CBlackOut::move()
{
	m_pos += m_move;
}