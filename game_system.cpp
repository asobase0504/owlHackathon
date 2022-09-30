//============================
//
// �Q�[���̃V�X�e��
// Author:koduna hurohito
//
//============================

//=====================================
// �C���N���[�h
//=====================================
#include "game_system.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "input.h"

//=====================================
// �R���X�g���N�^
//=====================================
CGameSystem::CGameSystem()
{
	m_bSignal = false;
	m_bGameEnd = false;
	m_nCountUpToSignalMax = -1;
	m_fCountUpToSignal = -1.0;
	m_nCnt = 0;
	m_GameStatu = STATUS_WAITING;
	srand((unsigned)time(NULL)); // ���ݎ����̏��ŏ�����
}

//=====================================
// �f�X�g���N�^
//=====================================
CGameSystem::~CGameSystem()
{
}

//=====================================
// �X�V����
//=====================================
void CGameSystem::Update()
{
	if (m_bGameEnd)
	{
		return;
	}
	CInput *pInput = CInput::GetKey();

	float fCnt = (timeGetTime() - m_fCountUpToSignal) / 1000.0f;
	if (m_nCountUpToSignalMax < fCnt && !m_bSignal)
	{
		m_bSignal = true;
		pInput->TimeUpToReactionKeyTimeStart();
	}

	m_fPlayerTime[0] = pInput->GetTimeUpToReactionKey(0);
	m_fPlayerTime[1] = pInput->GetTimeUpToReactionKey(1);

	SetStatus();

	if (m_bSignal)
	{
		m_nCnt++;
	}

	if (m_nCnt < 60)
	{
		return;
	}

	// ���ʂ̎���
	if (m_bSignal)
	{
		ResultIdentification();
	}
}

//=====================================
// ���}�܂ł̎��ԃZ�b�g
//=====================================
void CGameSystem::SetCountUpToSignal()
{
	m_bSignal = false;
	m_bGameEnd = false;
	m_fCountUpToSignal = timeGetTime();
	m_nCountUpToSignalMax = rand() % AMPLITUDE_UP_TO_SIGNAL + MINIMUM_TIME_UP_TO_SIGNAL;
}

//=====================================
// ���ʂ̎���
//=====================================
void CGameSystem::ResultIdentification()
{

	if (m_fPlayerTime[0] == 500.0f
		&& m_fPlayerTime[1] == 500.0f)
	{
		m_GameStatu = STATUS_DOUBLE_CHICKEN;
		m_bGameEnd = true;
		return;
	}
	else if (m_fPlayerTime[0] == 500.0f)
	{
		m_GameStatu = STATUS_PL1_CHICKEN;
		m_bGameEnd = true; 
		return;
	}
	else if (m_fPlayerTime[1] == 500.0f)
	{
		m_GameStatu = STATUS_PL2_CHICKEN;
		m_bGameEnd = true;
		return;
	}

	if (m_fPlayerTime[0] == m_fPlayerTime[1]
		&& 1000.0f > m_fPlayerTime[0])
	{
		m_GameStatu = STATUS_DRAW;
		m_bGameEnd = true;
		return;
	}
	else if (m_fPlayerTime[0] < m_fPlayerTime[1])
	{
		m_GameStatu = STATUS_PL1_WINNING;
		m_bGameEnd = true;
		return;
	}
	else if (m_fPlayerTime[1] < m_fPlayerTime[0])
	{
		m_GameStatu = STATUS_PL2_WINNING;
		m_bGameEnd = true;
		return;
	}
	

	if (m_fPlayerTime[0] >= 1000.0f
		&& m_fPlayerTime[1] >= 1000.0f)
	{
		m_GameStatu = STATUS_DOUBLE_CHICKEN;
		m_bGameEnd = true;
		return;
	}
	return;
}

void CGameSystem::SetStatus()
{
	if (m_fPlayerTime[0] == 500.0f
		&& m_fPlayerTime[1] == 500.0f)
	{
		m_GameStatu = STATUS_DOUBLE_CHICKEN;
		return;
	}
	else if (m_fPlayerTime[0] == 500.0f)
	{
		m_GameStatu = STATUS_PL1_CHICKEN;
		return;
	}
	else if (m_fPlayerTime[1] == 500.0f)
	{
		m_GameStatu = STATUS_PL2_CHICKEN;
		return;
	}
}
