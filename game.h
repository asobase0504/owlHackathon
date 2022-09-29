//============================
//
// �Q�[����ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//���̃}�N������`����ĂȂ�������
#define _GAME_H_		//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"

class CMagicBox;
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

	static CMagicBox*GetMagicBox() { return m_MagicBox; };
	static CParticleManager* GetParticleManager() { return m_PaticleManager; }
	static CPlayer * GetPlayer() { return m_Player; };
	static CPause * GetPause() { return m_Pause; };
	
private:

	static CMagicBox* m_MagicBox;
	static CPlayer* m_Player;
	static CParticleManager* m_PaticleManager;	// �p�[�e�B�N���}�l�W���[
	static CPause *m_Pause;

	int m_GameCount;
	int m_SpeedUp;
};
#endif