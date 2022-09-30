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
class CObject2d;
class CPause; 
class CGameSystem;
class CCurtain;

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
	static CPause * GetPause() { return m_Pause; };

	//static CObject2d* GetBg(int number) { return  Bg[number]; };

	void SetTime();
private:
	static CParticleManager* m_PaticleManager;	// パーティクルマネジャー
	static CObject2d* m_player[2];

	static CPause *m_Pause;
	CObject2d *Bg;
	CObject2d *Saboten[4];
	CObject2d *m_pGo;
	CObject2d *m_pReady;
	CGameSystem *m_pGameSystem;
	CCurtain *m_curtain;
	int m_GameCount;

	int m_tumbleweedPopCount;
	int m_birdPopCount;
	int m_nCnt;
	bool m_bCurtain;
	bool m_bCurtainIn;

	int m_1pTimeId;
	int m_2pTimeId;

	bool isText;
};
#endif