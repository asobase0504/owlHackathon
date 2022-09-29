//============================
//
// �w�i�ݒ�
// Author:hamada ryuuga
//
//============================

#include "3dpolygontemplate.h"
#include "hamada.h"
#include "manager.h"
#include "3dpolygon.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CTest3d::CTest3d(int list) :C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CTest3d::~CTest3d()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CTest3d::Init()
{

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CTest3d::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CTest3d::Update()
{
	
	//����
	CTest3d::move();
	
	C3dpolygon::Update();
	


}

//------------------------------------
// �`��
//------------------------------------
void CTest3d::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�y���ŉ�]���܂����Ȃ݂�m_rot�����ƃO���O�����܂�
	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);
	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CTest3d *CTest3d::Create()
{
	CTest3d * pObject = nullptr;
	pObject = new CTest3d(0);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_EXPLOSION);//�e�N�X�`���I��
		pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));//�T�C�Y�ݒ�
		pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 10200.0f));//���W�ݒ�
		pObject->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�F�ݒ�
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//move�̐ݒ�
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CTest3d::GetPos() const
{
	return &m_pos;
}

void CTest3d::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}



//------------------------------------
// �����n��
//------------------------------------
void CTest3d::move()
{
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����

	m_pos += m_Move;
}

