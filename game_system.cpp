//============================
//
// ゲームのシステム
// Author:koduna hurohito
//
//============================

//=====================================
// インクルード
//=====================================
#include "game_system.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>

//=====================================
// コンストラクタ
//=====================================
GameSystem::GameSystem()
{
	m_bSignal = false;
	m_bGameEnd = false;
	m_nCountUpToSignalMax = -1;
	m_fCountUpToSignal = -1.0;
	srand((unsigned)time(NULL)); // 現在時刻の情報で初期化
}

//=====================================
// デストラクタ
//=====================================
GameSystem::~GameSystem()
{
}

//=====================================
// 更新処理
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
// 合図までの時間セット
//=====================================
void GameSystem::SetCountUpToSignal()
{
	m_bSignal = false;
	m_bGameEnd = false;
	m_fCountUpToSignal = timeGetTime();
	m_nCountUpToSignalMax = rand() % AMPLITUDE_UP_TO_SIGNAL + MINIMUM_TIME_UP_TO_SIGNAL;
}
