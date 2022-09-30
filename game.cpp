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
#include "player.h"
#include "file.h"

#include "fade.h"

#include "multiply.h"
#include "particle_manager.h"
#include "ranking.h"

#include "score.h"
#include "sound.h"
#include "bg.h"

#include "pause.h"

#include "text.h"

CParticleManager*CGame::m_PaticleManager = nullptr;
CPlayer*CGame::m_Player = nullptr;
CPause *CGame::m_Pause = nullptr;
CScore * CGame::pScore;
CBg * CGame::Bg[3];

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
	m_GameCount = 0;
	m_SpeedUp = 300;

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	m_PaticleManager = new CParticleManager;
	// パーティクル
	if (FAILED(m_PaticleManager->Init()))
	{
		return E_FAIL;
	}

	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);

	SetBossPop(false);
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_Pause = new CPause;
	m_Pause->Init();
	m_Pause->SetUp(CObject::PAUSE);

	Bg[0] = CBg::Create();
	Bg[0]->SetMove(D3DXVECTOR3(0.0001f, 0.0f, 0.0f));
	Bg[0]->SetTexture(CTexture::TEXTURE_STARRY);
	Bg[0]->SetBgType(CBg::MOVE);

	Bg[1] = CBg::Create();
	Bg[1]->SetMove(D3DXVECTOR3(0.001f, 0.0f, 0.0f));
	Bg[1]->SetTexture(CTexture::TEXTURE_TOWN);
	Bg[1]->SetBgType(CBg::MOVE);

	Bg[2] = CBg::Create();
	Bg[2]->SetTexture(CTexture::TEXTURE_MOON);
	Bg[2]->SetBgType(CBg::STOP);


	pScore = CScore::Create(D3DXVECTOR3(500.0f, 30.0f, 0.0f));
	pScore->Set(0);

	return S_OK;
}

//========================
// ゲームの終了処理
//========================
void CGame::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	CModelManager::ReleaseAll();
	CRanking::SetScore(CScore::GetScore());

	if (m_PaticleManager != nullptr)
	{
		m_PaticleManager->Uninit();
		delete m_PaticleManager;
		m_PaticleManager = nullptr;

	}

	

	if (m_Pause != nullptr)
	{
		m_Pause->Uninit();
		m_Pause = nullptr;
	}

}

//========================
// ゲームの更新処理
//========================
void CGame::Update(void)
{
	m_GameCount++;
	// 更新処理
	if (m_GameCount == m_SpeedUp&&!GetMaxBoss())
	{
		m_GameCount = 0;
		m_SpeedUp += 250;
	}

	CInput *CInputpInput = CInput::GetKey();

	
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
	
		//CText::Create(CText::GON,120, 10, "モンハンたのしい...");
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
		return;
	}
	if (GetMaxEnemy() <= 0)
	{
		if (GetMaxBoss())
		{
		}
		else
		{
			
		}
	}
	m_PaticleManager->Update();
}

//========================
// ゲームの描画処理
//========================
void CGame::Draw(void)
{

}

//=============================================================================
// スコアのデータを取得する関数
//=============================================================================
CScore*CGame::GetScore()
{
	return pScore;
}

