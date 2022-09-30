//============================
//
// ゲーム画面
// Author:hamada ryuuga
//
//============================

//------------------------
// インクルード
//------------------------
#include "game.h"
#include "input.h"
#include "manager.h"
#include "object.h"
#include "light.h"
#include "file.h"
#include "object2d.h"
#include "fade.h"

#include "multiply.h"
#include "particle_manager.h"
#include "ranking.h"

#include "score.h"
#include "sound.h"
#include "bg.h"

#include "pause.h"

#include "text.h"
#include "time_text.h"
#include "tumbleweed.h"
#include "bird.h"
#include "curtain.h"
#include <tchar.h> // _T

#include "game_system.h"

CParticleManager*CGame::m_PaticleManager = nullptr;
CObject2d* CGame::m_player[2];
CPause *CGame::m_Pause = nullptr;

//========================
// コンストラクター
//========================
//========================
CGame::CGame()
{
}
//========================
// デストラクト
//========================
CGame::~CGame()
{
}

//========================
// ゲームの初期化処理
//========================
HRESULT CGame::Init(void)
{
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_WIND);

	m_GameCount = 0;
	m_nCnt = 0;
	m_bCurtain = false;
	m_bCurtainIn = false;
	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	m_PaticleManager = new CParticleManager;
	// パーティクル
	if (FAILED(m_PaticleManager->Init()))
	{
		return E_FAIL;
	}

	SetBossPop(false);

	m_Pause = new CPause;
	m_Pause->Init();
	m_Pause->SetUp(CObject::PAUSE);

	// 背景の荒野
	Bg = CObject2d::Create();
	Bg->SetTexture(CTexture::TEXTURE_WILDERNESS);
	Bg->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));
	Bg->SetSize(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));

	// サボテン
	Saboten[0] = CObject2d::Create();
	Saboten[0]->SetTexture(CTexture::TEXTURE_SABOTEN);
	Saboten[0]->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f + 300.0f, CManager::SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f));
	Saboten[0]->SetSize(D3DXVECTOR3(20.0f, 60.0f, 0.0f));

	// サボテン
	Saboten[1] = CObject2d::Create();
	Saboten[1]->SetTexture(CTexture::TEXTURE_SABOTEN);
	Saboten[1]->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f - 300.0f, CManager::SCREEN_HEIGHT * 0.5f + 150.0f, 0.0f));
	Saboten[1]->SetSize(D3DXVECTOR3(20.0f, 60.0f, 0.0f));

	// 左の人
	m_player[0] = CObject2d::Create(1);
	m_player[0]->SetPos(D3DXVECTOR3(CManager::GetInstance()->Pos.x * 0.45f, 550.0f, 0.0f));
	m_player[0]->SetSize(D3DXVECTOR3(150.0f, 150.0f, 0.0f));
	m_player[0]->SetTexture(CTexture::TEXTURE_PLAYER1_1);

	// 右の人
	m_player[1] = CObject2d::Create(1);
	m_player[1]->SetPos(D3DXVECTOR3(CManager::GetInstance()->Pos.x * 1.55f, 550.0f, 0.0f));
	m_player[1]->SetSize(D3DXVECTOR3(150.0f, 150.0f, 0.0f));
	m_player[1]->SetTexture(CTexture::TEXTURE_PLAYER2_1);

	m_tumbleweedPopCount = rand() % 70;
	m_birdPopCount = rand() % 70;

	// GO
	m_pGo = CObject2d::Create(3);
	m_pGo->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.3f, 0.0f));
	m_pGo->SetSize(D3DXVECTOR3(200.0f, 200.0f, 0.0f));
	m_pGo->SetTexture(CTexture::TEXTURE_GO);
	m_pGo->TrueDraw();

	m_pReady = CObject2d::Create(3);
	m_pReady->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.3f, 0.0f));
	m_pReady->SetSize(D3DXVECTOR3(200.0f, 200.0f, 0.0f));
	m_pReady->SetTexture(CTexture::TEXTURE_READY);



	m_pGameSystem = new CGameSystem;
	m_pGameSystem->SetCountUpToSignal();

	isText = false;

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_READY);

	return S_OK;
}

//========================
// ゲームの終了処理
//========================
void CGame::Uninit(void)
{
	CManager::GetInstance()->GetText()->AllDelete();
	CManager::GetInstance()->GetSound()->Stop();

	if (m_PaticleManager != nullptr)
	{
		m_PaticleManager->Uninit();
		delete m_PaticleManager;
		m_PaticleManager = nullptr;

	}

	if (m_curtain != nullptr)
	{
		m_curtain->Uninit();
		m_curtain = nullptr;
	}

	if (m_Pause != nullptr)
	{
		m_Pause->Uninit();
		m_Pause = nullptr;
	}

	if (m_pGameSystem != nullptr)
	{
		delete m_pGameSystem;
		m_pGameSystem = nullptr;
	}
}

//========================
// ゲームの更新処理
//========================
void CGame::Update(void)
{
	if (m_nCnt < -900)
	{
		return;
	}
	m_GameCount++;

	CInput *CInputpInput = CInput::GetKey();

	m_PaticleManager->Update();

	m_tumbleweedPopCount--;
	if (m_tumbleweedPopCount <= 0)
	{
		m_tumbleweedPopCount = rand() % 150 + 50;
		CTumbleweed::Create();
	}

	m_birdPopCount--;
	if (m_birdPopCount <= 0)
	{
		m_birdPopCount = rand() % 150 + 50;
		CBird::Create();
	}

	m_pGameSystem->Update();

	if (m_pGameSystem->GetGameStatus() >= CGameSystem::STATUS_PL1_CHICKEN)
	{
		if (!m_bCurtain)
		{
			m_pReady->TrueDraw();
			m_nCnt = 120;
			m_curtain = CCurtain::Create();
			m_bCurtain = true;
			m_pGameSystem->SetGameEnd();
		}
	}


	if (m_pGameSystem->GetSignal())
	{
		if (!m_bCurtain)
		{
			m_pReady->TrueDraw();
			m_nCnt = 120;
			m_curtain = CCurtain::Create();
			m_bCurtain = true;
			m_pGo->FalseDraw();
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_FIRE);
		}
	}

	if (!m_pGameSystem->GetGameEnd())
	{
		return;
	}

	m_nCnt--;

	if (m_nCnt == 0)
	{
		m_bCurtainIn = m_curtain->GetInStop();
		m_curtain->SetOut();
	}

	if (!m_bCurtainIn)
	{
		return;
	}

	switch (m_pGameSystem->GetGameStatus())
	{
	case CGameSystem::STATUS_PL1_WINNING:
		m_player[0]->SetTexture(CTexture::TEXTURE_PLAYER1_2);
		m_player[1]->SetTexture(CTexture::TEXTURE_PLAYER2_3);
		break;
	case CGameSystem::STATUS_PL2_WINNING:
		m_player[0]->SetTexture(CTexture::TEXTURE_PLAYER1_3);
		m_player[1]->SetTexture(CTexture::TEXTURE_PLAYER2_2);
		break;
	case CGameSystem::STATUS_DRAW:
		m_player[0]->SetTexture(CTexture::TEXTURE_PLAYER1_3);
		m_player[1]->SetTexture(CTexture::TEXTURE_PLAYER2_3);
		break;
	case CGameSystem::STATUS_PL1_CHICKEN:
		m_player[0]->SetTexture(CTexture::TEXTURE_PLAYER_CIKIN);
		break;
	case CGameSystem::STATUS_PL2_CHICKEN:
		m_player[1]->SetTexture(CTexture::TEXTURE_PLAYER_CIKIN);
		break;
	case CGameSystem::STATUS_DOUBLE_CHICKEN:
		m_player[0]->SetTexture(CTexture::TEXTURE_PLAYER_CIKIN);
		m_player[1]->SetTexture(CTexture::TEXTURE_PLAYER_CIKIN);
		break;
	default:
		break;
	}

	if (m_nCnt == -300)
	{
		SetTime();
	}

	if (m_nCnt < -300)
	{
		m_pGo->TrueDraw();
	}

	if (m_nCnt < -700)
	{
		CInputpInput->ResetInputTime();
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RANKING);
	}
}

//========================
// ゲームの描画処理
//========================
void CGame::Draw(void)
{
}

void CGame::SetTime()
{
	if (!isText)
	{
		if (m_pGameSystem->GetGameStatus() >= CGameSystem::STATUS_PL1_CHICKEN)
		{
			return;
		}

		CManager::GetInstance()->GetText()->SetText((float)m_pGameSystem->GetPlayerTime(0), D3DXVECTOR3(CManager::GetInstance()->Pos.x * 0.15f, 350.0f, 0.0f));
		CManager::GetInstance()->GetText()->SetText((float)m_pGameSystem->GetPlayerTime(1), D3DXVECTOR3(CManager::GetInstance()->Pos.x * 1.25f, 350.0f, 0.0f));
		isText = true;
	}
}
