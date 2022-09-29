//=============================================================================
//
// ����
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "bullet.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "crystal.h"
#include "player.h"
#include "hamada.h"
#include "enemy.h"
#include "hit.h"
#include "bg.h"
#include <assert.h>


int CBullet::m_AllMember;
LPDIRECT3DTEXTURE9	CBullet::m_pTexture;

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CBullet::CBullet()
{
	m_AllMember++;
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CBullet::Init()
{
	C3dpolygon::Init();

	C3dpolygon::SetTexture(CTexture::TEXTURE_BULLET);

	m_VecLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Length = 0.0f;
	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CBullet::Uninit()
{
	C3dpolygon::Uninit();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CBullet::Update()
{
	C3dpolygon::Update();

	Move();

	if (m_pos.y > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}
	if (m_pos.x > SCREEN_WIDTH/2)
	{
		Uninit();
		return;
	}
	CObject**pObject;
	pObject = GetObjectData(0);

	for (int nObject = 0; nObject < MAX_OBJECT; nObject++)
	{
		if (pObject[nObject] != nullptr)
		{
			EObjectType Type = pObject[nObject]->GetType();
			if (Type == CObject::ENEMY)
			{
				CObject3d* pObject3d = dynamic_cast<CObject3d*>(pObject[nObject]);  // �_�C�i�~�b�N�L���X�g
				assert(pObject3d != nullptr);
				//�T�C�Y
				const D3DXVECTOR3 *enemyPos = pObject3d->GetPos();
				const D3DXVECTOR3 *pEnemySize = pObject3d->GetSize();

				float enemySizeY = 30.0f;
				float enemySizeX = 15.0f;

				enemySizeY *= pEnemySize->y;
				enemySizeX *= pEnemySize->x;

				//�����蔻��
				if (((m_pos.y - m_Size.y) <= (enemyPos->y + enemySizeY)) &&
					((m_pos.y + m_Size.y) >= (enemyPos->y - enemySizeY)) &&
					((m_pos.x - m_Size.x) <= (enemyPos->x + enemySizeX)) &&
					((m_pos.x + m_Size.x) >= (enemyPos->x - enemySizeX)))
				{
					CHit::Create(*enemyPos, m_Type);
					switch (m_Type)
					{
					case CPlayer::NOW_FIRE:
						pObject3d->HitLife(5);
						break;
					case CPlayer::NOW_ICE:
						pObject3d->HitLife(2);
						break;
					case CPlayer::NOW_STORM:
						pObject3d->HitLife(3);
						break;
					case CPlayer::NOW_SUN:
						pObject3d->HitLife(3);
						break;
					case CPlayer::NOW_NON:
						pObject3d->HitLife(2);
						break;
					default:
						pObject3d->HitLife(2);
						break;
					}
					//D3DXVECTOR3 BGmove = CBg::GetKillMove();
					//BGmove.x += 0.001f;
					//CBg::SetKillMove(BGmove);
					// ���
					Uninit();
					return;
				}
			}
		}
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBullet::Draw()
{		//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

 	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=============================================================================
// create�֐�
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos ,D3DXVECTOR3 move, int magic)
{
	CBullet * pObject = nullptr;
	pObject = new CBullet;

	if (pObject != nullptr)
	{
		pObject->SetMove(move);
		pObject->SetPos(pos);
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

		pObject->SetType((int)magic);
		//�F�̐ݒ�
		switch (magic)
		{
		case CPlayer::NOW_FIRE:
			pObject->SetCollar(PositionVec4(1.0f, 0.0f, 0.0f, 0.8f));

			break;
		case CPlayer::NOW_ICE:
			pObject->SetCollar(PositionVec4(0.0f, 0.0f, 1.0f, 0.8f));
			break;
		case CPlayer::NOW_STORM:
			pObject->SetCollar(PositionVec4(0.0f, 1.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_SUN:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 0.0f, 0.8f));
			break;
		case CPlayer::NOW_NON:
			pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			break;
		default:
				pObject->SetCollar(PositionVec4(1.0f, 1.0f, 1.0f, 0.8f));
			break;
		}
	}
	return pObject;
}
//=============================================================================
// Setmove�֐�
//=============================================================================
void CBullet::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//=============================================================================
// Gettex�֐�
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::GetTex()
{
	return m_pTexture;
}

//=============================================================================
// �����n���֐�
//=============================================================================
void CBullet::Move()
{
	switch ((CPlayer::NOWMAGIC)m_Type)
	{
	case CPlayer::NOW_FIRE:
		m_pos += m_move;
		break;
	case CPlayer::NOW_ICE:
	{
		bool homing = false;

		CObject**pObject = nullptr;
		pObject = GetObjectData(0);
		for (int nObject = 0; nObject < MAX_OBJECT; nObject++)
		{
			if (pObject[nObject] != nullptr)
			{
				EObjectType Type = pObject[nObject]->GetType();
				if (Type == CObject::ENEMY)
				{
					CEnemy* Enemy = dynamic_cast<CEnemy*>(pObject[nObject]);  // �_�E���L���X�g

					D3DXVECTOR3 vecDiff = *Enemy->GetPos() - m_pos;
					float fLength = D3DXVec3Length(&vecDiff);
					m_pos = m_pos + ((vecDiff / fLength) * 10.0f);
					homing = true;
					break;
				}
			}
		}

		if (!homing)
		{
			m_pos += m_move;
		}
	}
	break;
	case CPlayer::NOW_STORM:
		m_pos += m_move;
		break;
	case CPlayer::NOW_SUN:
		m_pos += m_move;
		break;
	case CPlayer::NOW_NON:
		m_pos += m_move;
		break;
	default:	
		m_pos += m_move;
		break;
	}



}

void CBullet::SetType(int Type)
{
	m_Type = Type;
}