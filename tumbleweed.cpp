//============================
//
// �QDpolygon�ݒ�
// Author:hamada ryuuga
//
//============================

#include "tumbleweed.h"
#include "utility.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CTumbleweed::CTumbleweed() :CObject2d(0)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CTumbleweed::~CTumbleweed()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CTumbleweed::Init()
{
	CObject2d::Init();

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	nLife = 0;
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CTumbleweed::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CTumbleweed::Update()
{
	nLife--;
	move();
	CObject2d::Update();

	if (nLife <= 0)
	{
		Uninit();
	}
}

//------------------------------------
// �`��
//------------------------------------
void CTumbleweed::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CTumbleweed *CTumbleweed::Create(D3DXVECTOR3 pos, bool b3D)
{
	CTumbleweed * pObject = new CTumbleweed;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos = pos;

		if (b3D)
		{
			popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// �X�N���[���T�C�Y
		}

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->nLife = 700;
		pObject->SetTexture(CTexture::TEXTURE_TITLE);		// �e�N�X�`���I��
		pObject->SetMove(D3DXVECTOR3(FloatRandam(-2.0f,-5.0f), 0.0f, 0.0f));		// move�̐ݒ�
		pObject->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));	// �T�C�Y�ݒ�
		pObject->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �F�ݒ�	
	}
	return pObject;
}

//------------------------------------
// �����n��
//------------------------------------
void CTumbleweed::move()
{
	m_rot.z+=0.1f;
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	SetRot(m_rot);
	m_pos += m_move;
}