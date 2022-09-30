//============================
//
// ２Dpolygon設定
// Author:hamada ryuuga
//
//============================

#include "tumbleweed.h"
#include "utility.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CTumbleweed::CTumbleweed() :CObject2d(0)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CTumbleweed::~CTumbleweed()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CTumbleweed::Init()
{
	CObject2d::Init();

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	nLife = 0;
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CTumbleweed::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CTumbleweed::Update()
{
	nLife--;
	move();
	CObject2d::Update();

	if (nLife <= 0)
	{
		Uninit();
	}
}

//------------------------------------
// 描画
//------------------------------------
void CTumbleweed::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CTumbleweed *CTumbleweed::Create()
{
	int isLeft = rand() % 2;

	D3DXVECTOR3 pos(isLeft == 0 ? 800.0f : -800.0f, FloatRandam(-120.0f, -150.0f), 0.0f);
	D3DXVECTOR3 move(FloatRandam(2.0f, 5.0f), 0.0f, 0.0f);

	if (isLeft == 0)
	{
		move *= -1;
	}

	CTumbleweed * pObject = new CTumbleweed;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos = pos;

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// スクリーンサイズ

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->nLife = 700;
		pObject->SetTexture(CTexture::TEXTURE_TUMBLEWEED);		// テクスチャ選択
		pObject->SetMove(move);		// moveの設定
		pObject->SetSize(D3DXVECTOR3(25.0f, 25.0f, 0.0f));	// サイズ設定
		pObject->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// 色設定
	}
	return pObject;
}

//------------------------------------
// 動き系統
//------------------------------------
void CTumbleweed::move()
{
	m_rot.z+=0.1f;
	//動き入れたいときはここに	SetMove()で変えれるよ
	SetRot(m_rot);
	m_pos += m_move;
}