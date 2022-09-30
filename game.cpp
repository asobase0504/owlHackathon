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

#include "tumbleweed.h"
#include "bird.h"
#include "blackout.h"
#include "blackin.h"

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
	m_GameCount = 0;

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	m_PaticleManager = new CParticleManager;
	// パーティクル
	if (FAILED(m_PaticleManager->Init()))
	{
		return E_FAIL;
	}

	SetBossPop(false);
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

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

	// 右の人
	m_Block[0] = CBlackIn::Create(true);
	m_Block[1] = CBlackIn::Create(false);
	//CBlackOut::Create(true);
	//CBlackOut::Create(false);

	m_tumbleweedPopCount = rand() % 70;
	m_birdPopCount = rand() % 70;

	return S_OK;
}

//========================
// ゲームの終了処理
//========================
void CGame::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
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

	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(DIK_F1))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(DIK_F2))
	{
		CText::Create(CText::GON, 120, 10, "モンハンたのしい...");
		return;
	}

	m_PaticleManager->Update();

	m_tumbleweedPopCount--;
	if (m_tumbleweedPopCount <= 0)
	{
		m_tumbleweedPopCount = rand() % 150;
		CTumbleweed::Create();
	}

	m_birdPopCount--;
	if (m_birdPopCount <= 0)
	{
		m_birdPopCount = rand() % 150;
		CBird::Create();
	}
}

//========================
// ゲームの描画処理
//========================
void CGame::Draw(void)
{

}
