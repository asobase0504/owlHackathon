//============================
//
// �Q�[�����
// Author:hamada ryuuga
//
//============================

//------------------------
// �C���N���[�h
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

CParticleManager*CGame::m_PaticleManager = nullptr;
CObject2d* CGame::m_player[2];
CPause *CGame::m_Pause = nullptr;

//========================
// �R���X�g���N�^�[
//========================
//========================
CGame::CGame()
{
}
//========================
// �f�X�g���N�g
//========================
CGame::~CGame()
{
}

//========================
// �Q�[���̏���������
//========================
HRESULT CGame::Init(void)
{
	m_GameCount = 0;

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	m_PaticleManager = new CParticleManager;
	// �p�[�e�B�N��
	if (FAILED(m_PaticleManager->Init()))
	{
		return E_FAIL;
	}

	SetBossPop(false);
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_Pause = new CPause;
	m_Pause->Init();
	m_Pause->SetUp(CObject::PAUSE);

	// �w�i�̍r��
	Bg = CObject2d::Create();
	Bg->SetTexture(CTexture::TEXTURE_WILDERNESS);
	Bg->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));
	Bg->SetSize(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));

	// �T�{�e��
	Saboten[0] = CObject2d::Create();
	Saboten[0]->SetTexture(CTexture::TEXTURE_SABOTEN);
	Saboten[0]->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f + 300.0f, CManager::SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f));
	Saboten[0]->SetSize(D3DXVECTOR3(20.0f, 60.0f, 0.0f));

	// �T�{�e��
	Saboten[1] = CObject2d::Create();
	Saboten[1]->SetTexture(CTexture::TEXTURE_SABOTEN);
	Saboten[1]->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f - 300.0f, CManager::SCREEN_HEIGHT * 0.5f + 150.0f, 0.0f));
	Saboten[1]->SetSize(D3DXVECTOR3(20.0f, 60.0f, 0.0f));

	// ���̐l
	m_player[0] = CObject2d::Create(3);
	m_player[0]->SetPos(D3DXVECTOR3(CManager::GetInstance()->Pos.x * 0.45f, 550.0f, 0.0f));
	m_player[0]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_player[0]->SetTexture(CTexture::TEXTURE_PLAYER1_1);

	// �E�̐l
	m_player[1] = CObject2d::Create(3);
	m_player[1]->SetPos(D3DXVECTOR3(CManager::GetInstance()->Pos.x * 1.55f, 550.0f, 0.0f));
	m_player[1]->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_player[1]->SetTexture(CTexture::TEXTURE_PLAYER2_1);

	m_tumbleweedPopCount = rand() % 70;
	m_birdPopCount = rand() % 70;

	return S_OK;
}

//========================
// �Q�[���̏I������
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
// �Q�[���̍X�V����
//========================
void CGame::Update(void)
{
	m_GameCount++;

	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		CText::Create(CText::GON,120, 10, "�����n�����̂���...");
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
// �Q�[���̕`�揈��
//========================
void CGame::Draw(void)
{

}
