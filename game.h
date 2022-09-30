//============================
//
// ゲーム画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//このマクロが定義されてなかったら
#define _GAME_H_		//2重インクルード防止のマクロ定義

#include "object.h"

class CParticleManager;
class CPlayer;
class CPause; 

class CGame :public CObject
{
public:
	CGame();
	~CGame();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CParticleManager* GetParticleManager() { return m_PaticleManager; }
	static CPlayer * GetPlayer() { return m_Player; };
	static CPause * GetPause() { return m_Pause; };

	static CBg* GetBg(int number) { return  Bg[number]; };
	static CScore*GetScore();

private:

	static CPlayer* m_Player;
	static CParticleManager* m_PaticleManager;	// パーティクルマネジャー
	static CPause *m_Pause;
	static CScore * pScore;
	static CBg * Bg[3];

	int m_GameCount;
	int m_SpeedUp;
};
#endif