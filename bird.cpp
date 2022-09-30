//============================
//
// 鳥の動き
// Author: Yuda Kaito
//
//============================

#include "bird.h"
#include "utility.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CBird::CBird() :CObject2d(0)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CBird::~CBird()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CBird::Init()
{
	CObject2d::Init();

	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CBird::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CBird::Update()
{
	CObject2d::Update();
	//動き
	move();
}

//------------------------------------
// 描画
//------------------------------------
void CBird::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBird *CBird::Create()
{
	int isLeft = rand() % 2;

	D3DXVECTOR3 pos(isLeft == 0 ? 800.0f : -800.0f, FloatRandam(180.0f, 280.0f), 0.0f);
	D3DXVECTOR3 move(FloatRandam(4.0f, 7.0f), 0.0f, 0.0f);

	if (isLeft == 0)
	{
		move *= -1;
	}

	CBird * pObject = new CBird;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos = pos;

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// スクリーンサイズ

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->nLife = 700;
		pObject->SetTexture(CTexture::TEXTURE_BIRD);		// テクスチャ選択
		pObject->SetMove(move);		// moveの設定
		pObject->SetSize(D3DXVECTOR3(25.0f, 25.0f, 0.0f));	// サイズ設定
		pObject->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// 色設定
	}
	return pObject;
}


//------------------------------------
// 動き系統
//------------------------------------
void CBird::move()
{
	m_pos += m_move;
}