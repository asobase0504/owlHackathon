//============================
//
// ゲームのシステム
// Author:koduna hurohito
//
//============================
#ifndef _FILE_H_			// このマクロ定義がされてなかったら
#define _FILE_H_			// 二重インクルード防止のマクロ定義

//=====================================
// インクルード
//=====================================

//=====================================
// クラス宣言
//=====================================
class GameSystem
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
	static const int AMPLITUDE_UP_TO_SIGNAL = 20;
	static const int MINIMUM_TIME_UP_TO_SIGNAL = 5;

	GameSystem();
	~GameSystem();
	void Update();
	void SetCountUpToSignal();

private:
	bool m_bGameEnd;
	bool m_bSignal;
	int m_nCountUpToSignalMax;
	int m_fCountUpToSignal;
	float m_fPlayerTime[PLAYER_COUNT_MAX];
};
#endif
