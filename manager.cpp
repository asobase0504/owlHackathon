//=============================================================================
//
// マネージャー
// Author : 浜田琉雅
//
//=============================================================================

#include "manager.h"
#include "main.h"

#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "ranking.h"
#include "fade.h"
#include "sound.h"

#include "texture.h"

#include "ranking.h"
#include "tutorial.h"

#include "time_text.h"

//-----------------------------------------------------------------------------
// 静的メンバー変数の初期化
//-----------------------------------------------------------------------------
CManager * CManager::m_manager = nullptr;
float CManager::m_fTime = 0.0f;
const D3DXVECTOR3 CManager::Pos = D3DXVECTOR3(1280.0f * 0.5f, 720.0f * 0.5f, 0.0f);

//=============================================================================
// シングルトンでのインスタンスの取得
//=============================================================================
CManager * CManager::GetInstance()
{
	if (m_manager == nullptr)
	{
		m_manager = new CManager;
	}
	return m_manager;
}

//=============================================================================
// コンストラクト関数
//=============================================================================
CManager::CManager() :
	m_pTexture(nullptr),
	m_cRenderer(nullptr),
	m_Fade(nullptr),
	m_Game(nullptr),
	m_Sound(nullptr),
	m_text(nullptr)
{
}

//=============================================================================
// デストラクト関数
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CManager::Init(HWND hWnd, bool /*bWindow*/, HINSTANCE hInstance)
{
	m_cRenderer = new CRenderer;

	m_Input = CInput::Create();

	// 初期化処理
	if (FAILED(m_cRenderer->Init(hWnd, false)))	//画面サイズ
	{//初期化処理が失敗した場合
		return -1;
	}
	//入力処理の初期化処理
	if (FAILED(m_Input->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_Sound = nullptr;
	m_Sound = new CSound;

	//入力処理の初期化処理
	if (FAILED(m_Sound->Init(hWnd)))
	{
		return E_FAIL;
	}

	m_pTexture = nullptr;
	m_pTexture = new CTexture;
	
	m_mode = CManager::MODE_TITLE;	//現在のモード

	//モードの設定
	SetMode(m_mode);

	m_Fade = CFade::Create();

	m_text = new CTImeText;
	m_text->Init();
	
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CManager::Uninit()
{
	CObject::AllUninit();

	if (m_pTexture != nullptr)
	{// 終了処理
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_cRenderer != nullptr)
	{// 終了処理

		m_cRenderer->Uninit();
		delete m_cRenderer;
		m_cRenderer = nullptr;
	}
	if (m_Sound != nullptr)
	{// 終了処理

		m_Sound->Uninit();
		delete m_Sound;
		m_Sound = nullptr;
	}

	if (m_text != nullptr)
	{// 終了処理

		m_text->Uninit();
		delete m_text;
		m_text = nullptr;
	}

	//入力処理の終了処理
	m_Input->Uninit();

}

//=============================================================================
// 更新
//=============================================================================
void CManager::Update()
{
	//入力処理の更新処理
	m_Input->Update();
	m_cRenderer->Update();
}

//=============================================================================
// 描画
//=============================================================================
void CManager::Draw()
{
	// 描画処理	
	m_cRenderer->Draw();
}

//=============================================================================
// GetRenderer
//=============================================================================
CRenderer *CManager::GetRenderer()
{
	return m_cRenderer;
}


//=============================================================================
// GetTexture
//=============================================================================
CTexture *CManager::GetTexture()
{
	return m_pTexture;
}

//=============================================================================
// GetFade
//=============================================================================
CFade * CManager::GetFade()
{
	return m_Fade;
}

//=============================================================================
// GetMode
//=============================================================================
CManager::MODE * CManager::GetMode()
{
	return &m_mode;
}

CTImeText * CManager::GetText()
{
	return m_text;
}

//=============================================================================
// GetSound
//=============================================================================
CSound * CManager::GetSound()
{
	return m_Sound;
}

//========================
// モードの設定
//========================
void CManager::SetMode(MODE mode)
{
	m_mode = mode;
	if (m_Game != nullptr)
	{
		m_Game->Uninit();
		m_Game->Release();
	}

	// ポリゴンの終了処理
	CObject::ModeNotUninit();
	
	switch (mode)
	{
	case CManager::MODE_TITLE:
		m_Game = new CTitle;
		break;
	case CManager::MODE_GAME:
		m_Game = new CGame;
		break;
	case CManager::MODE_RANKING:
		m_Game = new CRanking;
		break;
	case CManager::MODE_TUTORIAL:
		m_Game = new CTutorial;
		break;
	default:
		break;
	}

	// 初期化処理
	if (FAILED(m_Game->Init()))	//画面サイズ
	{//初期化処理が失敗した場合
		return ;
	}
	m_Game->SetUp(CObject::MODE);
}



