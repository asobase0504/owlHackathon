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

//=====================================
// �R���X�g���N�^
//=====================================
GameSystem::GameSystem()
{
	m_bSignal = false;
	m_bGameEnd = false;
	m_nCountUpToSignalMax = -1;
	m_fCountUpToSignal = -1.0;
	srand((unsigned)time(NULL)); // ���ݎ����̏��ŏ�����
}

//=====================================
// �f�X�g���N�^
//=====================================
GameSystem::~GameSystem()
{
}

//=====================================
// �X�V����
//=====================================
void GameSystem::Update()
{
	if (m_bGameEnd)
	{
		return;
	}

	float fCnt = (timeGetTime() - m_fCountUpToSignal) / 1000.0f;
	if (m_nCountUpToSignalMax < fCnt && !m_bSignal)
	{
		m_bSignal = true;

	}


}

//=====================================
// ���}�܂ł̎��ԃZ�b�g
//=====================================
void GameSystem::SetCountUpToSignal()
{
	m_bSignal = false;
	m_bGameEnd = false;
	m_fCountUpToSignal = timeGetTime();
	m_nCountUpToSignalMax = rand() % AMPLITUDE_UP_TO_SIGNAL + MINIMUM_TIME_UP_TO_SIGNAL;
}
