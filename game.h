//============================
//
// �Q�[����ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//���̃}�N������`����ĂȂ�������
#define _GAME_H_		//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

class CParticleManager;
class CObject2d;
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
	static CPause * GetPause() { return m_Pause; };

	//static CObject2d* GetBg(int number) { return  Bg[number]; };

private:
	static CParticleManager* m_PaticleManager;	// �p�[�e�B�N���}�l�W���[
	static CObject2d* m_player[2];

	static CPause *m_Pause;
	CObject2d *Bg;
	CObject2d *Saboten[4];

	int m_GameCount;

	int m_tumbleweedPopCount;
};
#endif