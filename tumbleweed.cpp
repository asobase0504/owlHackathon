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
CTumbleweed *CTumbleweed::Create()
{
	int isLeft = rand() % 2;

	D3DXVECTOR3 pos(isLeft == 0 ? 800.0f : -800.0f, FloatRandam(-120.0f, -150.0f), 0.0f);
	D3DXVECTOR3 move(FloatRandam(2.0f, 5.0f), 0.0f, 0.0f);

	if (isLeft == 0)
	{
		move *= -1;
	}

	CTumbleweed * pObject = new CTumbleweed;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos = pos;

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// �X�N���[���T�C�Y

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->nLife = 700;
		pObject->SetTexture(CTexture::TEXTURE_TUMBLEWEED);		// �e�N�X�`���I��
		pObject->SetMove(move);		// move�̐ݒ�
		pObject->SetSize(D3DXVECTOR3(25.0f, 25.0f, 0.0f));	// �T�C�Y�ݒ�
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