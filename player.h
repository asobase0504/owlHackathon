//============================
//
// �v���C���[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"
#include "renderer.h"
#include "object3d.h"

class  CMotion;
class CMagicBox;
class CPlayer : public CObject3d
{
public:

	enum NOWMAGIC
	{
		NOW_FIRE = 2,		// ��
		NOW_ICE,			// �X
		NOW_STORM,			// ��
		NOW_SUN,			// ��
		NOW_NON,
		NOW_MAX
	};

	//model�f�[�^�̍\����//
	struct MODELDATAPLAYER
	{
		int key;		// ���ԊǗ�
		int nowKey;		// ���̃L�[
		int loop;		// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1 : ���[�v����]
		int num_key;  	// �L�[��
		/*MyKeySet KeySet[MAX_KEY];*/
	};

public:
	static const int MAXLIFE = 300;
	static const float ATTENUATION;		// �����W��
	static const float SPEED;			// �X�s�[�h
	static const float WIDTH;			// ���f���̔��a
	static const int MAX_PRAYER;		// �ő吔
	static const int MAX_MOVE;			// �A�j���[�V�����̍ő吔
	static const int INVINCIBLE;		// ���G����
	static const int MAX_MODELPARTS = 9;
	
public:
	CPlayer();
	~CPlayer();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CPlayer *Create();
	static NOWMAGIC *GetMagic();
	static void SetMagic(CPlayer::NOWMAGIC NextMagic);
	static CPlayer::NOWMAGIC * GetCastMagic();

private:
	
	void Move();		// �ړ�
	void TitleMove();
	void ResetMove();
	void TutorialMove();	//�����Z�b�g
	int m_Pow;
	float m_MoveSpeed;
	static NOWMAGIC m_NowMagic;			//���݂̖��@
	static NOWMAGIC m_CastMagic;		//���������@
private:
};
#endif
