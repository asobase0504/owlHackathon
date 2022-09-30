//=============================================================================
//
// �J�����ݒ�
// Author:hamada ryuuga
//
//=============================================================================
#include "camera.h"
#include "input.h"

#include "manager.h"

//-----------------------------------------------------------------------------
//�R���X�g���N�g
//-----------------------------------------------------------------------------
CCamera::CCamera()
{
}

//-----------------------------------------------------------------------------
//�f�X�g���N�g
//-----------------------------------------------------------------------------
CCamera::~CCamera()
{
}

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
void CCamera::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//���_�@�����_�@������@�ݒ�
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_directionR = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	m_directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fDistance = sqrtf((m_posR.x - m_posV.x) *
		(m_posR.x - m_posV.x) +
		(m_posR.z - m_posV.z) *
		(m_posR.z - m_posV.z));

	m_fDistance = sqrtf((m_posR.y - m_posV.y)*
		(m_posR.y - m_posV.y) +
		(m_fDistance*m_fDistance));

	m_rot.x = atan2f((m_posR.z - m_posV.z),
		(m_posR.y - m_posV.y));
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void CCamera::Uninit(void)
{
}

//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void CCamera::Update(void)
{
	if (m_Type == 0)
	{
		m_posV.x += 1.1f;
		m_posR.x += 1.1f;
	}
}

//-----------------------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------------------
void CCamera::Set(int Type)
{
	m_Type = Type;
	LPDIRECT3DDEVICE9  pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	//�r���[�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_MtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_MtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�K�p
	pDevice->SetTransform(D3DTS_VIEW, &m_MtxView);

	//�v���W�F�N�V�����}�g���b�N�X��������
	D3DXMatrixIdentity(&m_MtxProje);

	//if (Type == 0)
	//{
	//	//�v���W�F�N�V�����}�g���b�N�X�쐬
	//	D3DXMatrixPerspectiveFovLH(&m_MtxProje,
	//		D3DXToRadian(90.0f),
	//		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
	//		10.0f,
	//		10000.0f);
	//}
	//else
	{
		// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
		D3DXMatrixOrthoLH(&m_MtxProje,					// �v���W�F�N�V�����}�g���b�N�X
			(float)SCREEN_WIDTH,								// ��
			(float)SCREEN_HEIGHT,								// ����
			-100.0f,											// �j�A
			2000.0f);											// �t�@�[
	}
	//�K�p
	pDevice->SetTransform(D3DTS_PROJECTION, &m_MtxProje);
}


//-----------------------------------------------------------------------------
//GetPos
//-----------------------------------------------------------------------------
D3DXVECTOR3 *CCamera::GetPos()
{
	return &m_posV;
}

//-----------------------------------------------------------------------------
//GetRot
//-----------------------------------------------------------------------------
D3DXVECTOR3 * CCamera::GetRot()
{
	return &m_rot;
}

//-----------------------------------------------------------------------------
// GetMtxProje
//-----------------------------------------------------------------------------
D3DXMATRIX  *CCamera::GetMtxProje()
{
	return &m_MtxProje;
}

//-----------------------------------------------------------------------------
// GetMtxView
//-----------------------------------------------------------------------------
D3DXMATRIX *CCamera::GetMtxView()
{
	return &m_MtxView;
}