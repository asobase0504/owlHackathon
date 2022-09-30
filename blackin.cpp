//============================
//
// �QDpolygon�ݒ�
// Author:Yuda Kaito
//
//============================

#include "blackin.h"
#include "utility.h"
#include "manager.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBlackIn::CBlackIn() :
	CObject2d(3),
	isStop(false)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CBlackIn::~CBlackIn()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CBlackIn::Init()
{
	CObject2d::Init();

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CBlackIn::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CBlackIn::Update()
{
	CObject2d::Update();
	//����

	if ((isLeft && m_pos.x >= CManager::GetInstance()->Pos.x * 0.5f) || (!isLeft && m_pos.x <= CManager::GetInstance()->Pos.x * 1.5f))
	{
		isStop = true;
	}
	else
	{
		move();
	}
}

//------------------------------------
// �`��
//------------------------------------
void CBlackIn::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBlackIn *CBlackIn::Create(bool isLeft)
{
	CBlackIn * pObject = new CBlackIn;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos;
		pObject->isLeft = isLeft;
		if (pObject->isLeft)
		{
			popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			popPos.x -= CManager::GetInstance()->Pos.x * 1.5f;
			pObject->SetMove(D3DXVECTOR3(10.0f, 0.0f, 0.0f));		// move�̐ݒ�
		}
		else
		{
			popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			popPos.x += CManager::GetInstance()->Pos.x * 1.5f;
			pObject->SetMove(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));		// move�̐ݒ�
		}

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// �X�N���[���T�C�Y

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->SetTexture(CTexture::TEXTURE_MAKU);		// �e�N�X�`���I��
		D3DXVECTOR3 size(CManager::Pos);
		size.x *= 0.5f;
		pObject->SetSize(size);	// �T�C�Y�ݒ�
		pObject->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �F�ݒ�

		pObject->nLife = 650;
	}
	return pObject;
}


//------------------------------------
// �����n��
//------------------------------------
void CBlackIn::move()
{
	//if (isLeft)
	//{
	//	m_rot.z -= 0.01f;
	//}

	////�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	//SetRot(m_rot);
	m_pos += m_move;
}