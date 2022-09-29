//============================
//
// �v���C���[�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "input.h"
#include "camera.h"
#include "motion.h"
#include "manager.h"
#include "motion.h"
#include "object3d.h"
#include "particle_manager.h"
#include "utility.h"
#include "game.h"
#include "tutorial.h"

//------------------------------------
// static�ϐ�
//------------------------------------
const float CPlayer::ATTENUATION = 0.5f;	// 
const float CPlayer::SPEED = 1.0f;			// �ړ���
const float CPlayer::WIDTH = 10.0f;			// ���f���̔��a
const int CPlayer::MAX_PRAYER = 16;			// �ő吔
const int CPlayer::MAX_MOVE = 9;			// �A�j���[�V�����̍ő吔
const int CPlayer::INVINCIBLE = 30;		// ���G����
CPlayer::NOWMAGIC CPlayer::m_NowMagic = NOW_NON;		// ���G����
CPlayer::NOWMAGIC CPlayer::m_CastMagic = NOW_NON;		// ���G����


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CPlayer::CPlayer()
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CPlayer::~CPlayer()
{

}

//------------------------------------
// ������
//------------------------------------
HRESULT CPlayer::Init()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Init();
	CObject3d::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "Data/system/Gon/Fox.txt");
	m_motionTypeOld = m_motionType;
	D3DXVECTOR3	Size(2.0f, 2.0f, 2.0f);
	m_MoveSpeed = 7.0f;
	m_rot.y += (-D3DX_PI*0.5f);
	SetSize(Size);
	SetLife(CPlayer::MAXLIFE);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CPlayer::Uninit()
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CPlayer::Update()
{

	switch (*CManager::GetInstance()->GetMode())
	{
	case CManager::MODE_TITLE:
		TitleMove();	//�����Z�b�g
		break;
	case CManager::MODE_GAME:
		Move();	//�����Z�b�g	
		break;
	case CManager::MODE_RESULT:
		ResetMove();
		break;
	case CManager::MODE_RANKING:
		break;
	case CManager::MODE_TUTORIAL:
		TutorialMove();
		break;
	default:
		break;
	}

	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject3d::Update();
}

//------------------------------------
// �`��
//------------------------------------
void CPlayer::Draw()
{
	CObject3d::Draw();
}

//------------------------------------
// create
//------------------------------------
CPlayer *CPlayer::Create()
{
	CPlayer * pObject = nullptr;
	pObject = new CPlayer;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//------------------------------------
// Move
//------------------------------------
void CPlayer::Move()	//�����Z�b�g
{



	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;

	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{	
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{	
		m_move.y += m_MoveSpeed;
	}
	
	//�e�̃N���G�C�g
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
		
	}


 	else
	{
		m_Pow = 20;
	}

	if (m_pos.y <= -SCREEN_HEIGHT / 2 + 20.0f)
	{
		m_pos.y = (-SCREEN_HEIGHT / 2)+20.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2 - 100.0f)
	{
		m_pos.y = SCREEN_HEIGHT / 2 - 100.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2 + 100.0f)
	{
		m_pos.x = -SCREEN_WIDTH*0.5f + 100.0f;
	}
	if (m_pos.x >= SCREEN_WIDTH / 2 - 80.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f - 80.0f;
	}

	//	�K�E�Z
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//	particleManager�̎擾
		CParticleManager* particleManager = CGame::GetParticleManager();

		if (particleManager->GetEmitter().size() == 0)
		{
			
			D3DXVECTOR3 Pos = ScreenCastWorld(
				&m_pos,			// �X�N���[�����W
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));
			
			//CastMagic�̒��ɂ�������������
			m_CastMagic = m_NowMagic;
		
			switch (m_NowMagic)
			{	
			case CPlayer::NOW_FIRE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_FIRE);
				break;
			case CPlayer::NOW_ICE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_ICE);
				break;
			case CPlayer::NOW_STORM:

				particleManager->Create(Pos, 0, CParticleManager::NOW_STORM);
				break;
			case CPlayer::NOW_SUN:
				particleManager->Create(Pos, 0, CParticleManager::NOW_SUN);
				break;
			case CPlayer::NOW_NON:
				break;
			default:
				break;
			}

			
		}
	}

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

	//���K��
	if ( consumption > D3DX_PI)
	{
		 consumption += D3DX_PI * 2.0f;
	}
	if ( consumption < -D3DX_PI)
	{
		 consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

	 //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//------------------------------------
// SetMagic
//------------------------------------
void CPlayer::SetMagic(CPlayer::NOWMAGIC NextMagic)
{
	if (NOW_MAX >= NextMagic)
	{
 		m_NowMagic = NextMagic;
	}
	else
	{
		m_NowMagic = NOW_NON;
	}
}

//------------------------------------
// GetMagic 
//------------------------------------
CPlayer::NOWMAGIC * CPlayer::GetMagic()
{
	return &m_NowMagic;
}


//------------------------------------
// GetMagic 
//------------------------------------
CPlayer::NOWMAGIC * CPlayer::GetCastMagic()
{
	return &m_CastMagic;
}

//------------------------------------
// Title�̂Ƃ���Move
//------------------------------------
void CPlayer::TitleMove()
{

	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;
	
	m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	consumption = m_rotMove.x + -(D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	
	m_pos.y = 250.0f;

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

					//���K��
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

										  //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}



	if (m_pos.x <= -SCREEN_WIDTH*0.5f-100.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f;
	}
	
	
}

//------------------------------------
// Reset�̂Ƃ���Move
//------------------------------------
void CPlayer::ResetMove()
{

	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;



	m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	consumption = m_rotMove.x + -(D3DX_PI*0.5f) - m_rot.y + Camerarot->y;

	m_pos.y = 250.0f;

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

					//���K��
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

										  //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}



	if (m_pos.x <= -SCREEN_WIDTH*0.5f - 100.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f;
	}


}

//------------------------------------
// Move
//------------------------------------
void CPlayer::TutorialMove()	//�����Z�b�g
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	float consumption = 0.0f;

	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		consumption = m_rotMove.x + (D3DX_PI*0.5f) - m_rot.y + Camerarot->y;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED * m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{
		m_move.y -= m_MoveSpeed;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{
		m_move.y += m_MoveSpeed;
	}

	//�e�̃N���G�C�g
	if (CInputpInput->Press(CInput::KEY_SHOT))
	{
	
	}


	else
	{
		m_Pow = 20;
	}

	if (m_pos.y <= -SCREEN_HEIGHT / 2 + 20.0f)
	{
		m_pos.y = (-SCREEN_HEIGHT / 2) + 20.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT / 2 - 100.0f)
	{
		m_pos.y = SCREEN_HEIGHT / 2 - 100.0f;
	}
	if (m_pos.x <= -SCREEN_WIDTH / 2 + 100.0f)
	{
		m_pos.x = -SCREEN_WIDTH*0.5f + 100.0f;
	}
	if (m_pos.x >= SCREEN_WIDTH / 2 - 80.0f)
	{
		m_pos.x = SCREEN_WIDTH*0.5f - 80.0f;
	}

	//	�K�E�Z
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		//	particleManager�̎擾
		CParticleManager* particleManager = CTutorial::GetParticleManager();

		if (particleManager->GetEmitter().size() == 0)
		{

			D3DXVECTOR3 Pos = ScreenCastWorld(
				&m_pos,			// �X�N���[�����W
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));

			//CastMagic�̒��ɂ�������������
			m_CastMagic = m_NowMagic;

			switch (m_NowMagic)
			{
			case CPlayer::NOW_FIRE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_FIRE);
				break;
			case CPlayer::NOW_ICE:
				particleManager->Create(Pos, 0, CParticleManager::NOW_ICE);
				break;
			case CPlayer::NOW_STORM:

				particleManager->Create(Pos, 0, CParticleManager::NOW_STORM);
				break;
			case CPlayer::NOW_SUN:
				particleManager->Create(Pos, 0, CParticleManager::NOW_SUN);
				break;
			case CPlayer::NOW_NON:
				break;
			default:
				break;
			}

		}
	}

	m_move.x += (0.0f - m_move.x)*ATTENUATION;//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z)*ATTENUATION;
	m_move.y += (0.0f - m_move.y)*ATTENUATION;

	m_pos += m_move;//�ړ������Z

					//���K��
	if (consumption > D3DX_PI)
	{
		consumption += D3DX_PI * 2.0f;
	}
	if (consumption < -D3DX_PI)
	{
		consumption += -D3DX_PI * 2.0f;
	}

	//���Z�ݒ�i�����j
	m_rot.y += (consumption)* ATTENUATION;//�ړI�̒l-���݂̒l�j�������W��

										  //���K��
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}
	if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}


}