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




CMagicBox* CGame::m_MagicBox = nullptr;
CParticleManager*CGame::m_PaticleManager = nullptr;
CPlayer*CGame::m_Player = nullptr;
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
	m_SpeedUp = 300;

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	m_PaticleManager = new CParticleManager;
	// �p�[�e�B�N��
	if (FAILED(m_PaticleManager->Init()))
	{
		return E_FAIL;
	}

	CObject::AllCreate();


	m_Player = CPlayer::Create();
	m_Player->SetUp(CObject::PLAYER);

	SetBossPop(false);
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_Pause = new CPause;
	m_Pause->Init();
	m_Pause->SetUp(CObject::PAUSE);

	
	
	return S_OK;
}

//========================
// �Q�[���̏I������
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
// �Q�[���̍X�V����
//========================
void CGame::Update(void)
{
	m_GameCount++;
	// �X�V����
	if (m_GameCount == m_SpeedUp&&!GetMaxBoss())
	{
		m_GameCount = 0;
		m_SpeedUp += 250;
	}

	CInput *CInputpInput = CInput::GetKey();

	
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//���[�h�̐ݒ�
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
	
		//CText::Create(CText::GON,120, 10, "�����n�����̂���...");
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
// �Q�[���̕`�揈��
//========================
void CGame::Draw(void)
{

}

