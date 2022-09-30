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
	nLife--;
	if (nLife <= 0)
	{
		Uninit();
	}
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
CBlackOut *CBlackOut::Create(bool isLeft)
{
	CBlackOut * pObject = new CBlackOut;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos;
		pObject->isLeft = isLeft;
		if (pObject->isLeft)
		{
			popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			popPos.x -= CManager::GetInstance()->Pos.x * 0.5f;
			pObject->SetMove(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));		// moveの設定
		}
		else
		{
			popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			popPos.x += CManager::GetInstance()->Pos.x * 0.5f;
			pObject->SetMove(D3DXVECTOR3(1.0f, 0.0f, 0.0f));		// moveの設定
		}

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// スクリーンサイズ

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);		// テクスチャ選択
		D3DXVECTOR3 size(CManager::Pos);
		size.x *= 0.5f;
		pObject->SetSize(size);	// サイズ設定
		pObject->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	// 色設定

		pObject->nLife = 650;
	}
	return pObject;
}


//------------------------------------
// 動き系統
//------------------------------------
void CBlackOut::move()
{
	//if (isLeft)
	//{
	//	m_rot.z -= 0.01f;
	//}

	////動き入れたいときはここに	SetMove()で変えれるよ
	//SetRot(m_rot);
	m_pos += m_move;
}