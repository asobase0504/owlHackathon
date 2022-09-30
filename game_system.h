//============================
//
// ゲームのシステム
// Author:koduna hurohito
//
//============================
#ifndef _GAME_SYATEM_H_			// このマクロ定義がされてなかったら
#define _GAME_SYATEM_H_			// 二重インクルード防止のマクロ定義

//=====================================
// インクルード
//=====================================

//=====================================
// クラス宣言
//=====================================
class CGameSystem
{
public:
	enum GameStatus
	{
		STATUS_WAITING = 0,
		STATUS_PL1_WINNING,
		STATUS_PL2_WINNING,
		STATUS_DRAW,
		STATUS_PL1_CHICKEN,
		STATUS_PL2_CHICKEN,
		STATUS_MAX
	};
	static const int PLAYER_COUNT_MAX = 2;
	static const int AMPLITUDE_UP_TO_SIGNAL = 10;
	static const int MINIMUM_TIME_UP_TO_SIGNAL = 5;

	CGameSystem();
	~CGameSystem();
	void Update();
	void SetCountUpToSignal();
	void ResultIdentification();
	GameStatus GetGameStatus() { return m_GameStatu; }
	bool GetSignal() { return m_bSignal; }

private:
	bool m_bGameEnd;
	bool m_bSignal;
	int m_nCountUpToSignalMax;
	int m_fCountUpToSignal;
	float m_fPlayerTime[PLAYER_COUNT_MAX];
	GameStatus m_GameStatu;
};
#endif
