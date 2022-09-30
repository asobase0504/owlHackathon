//============================
//
// �QDpolygon�ݒ�
// Author:Yuda Kaito
//
//============================

#include "blackout.h"
#include "utility.h"
#include "manager.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBlackOut::CBlackOut() :CObject2d(3)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CBlackOut::~CBlackOut()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CBlackOut::Init()
{
	CObject2d::Init();

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CBlackOut::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CBlackOut::Update()
{
	CObject2d::Update();
	//����
	move();
	nLife--;
	if (nLife <= 0)
	{
		Uninit();
	}
}

//------------------------------------
// �`��
//------------------------------------
void CBlackOut::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBlackOut *CBlackOut::Create(bool isLeft)
{
	CBlackOut * pObject = new CBlackOut;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos;
		pObject->isLeft = isLeft;
		if (pObject->isLeft)
		{
			popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			popPos.x -= CManager::GetInstance()->Pos.x * 0.5f;
			pObject->SetMove(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));		// move�̐ݒ�
		}
		else
		{
			popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			popPos.x += CManager::GetInstance()->Pos.x * 0.5f;
			pObject->SetMove(D3DXVECTOR3(1.0f, 0.0f, 0.0f));		// move�̐ݒ�
		}

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// �X�N���[���T�C�Y

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);		// �e�N�X�`���I��
		D3DXVECTOR3 size(CManager::Pos);
		size.x *= 0.5f;
		pObject->SetSize(size);	// �T�C�Y�ݒ�
		pObject->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	// �F�ݒ�

		pObject->nLife = 650;
	}
	return pObject;
}


//------------------------------------
// �����n��
//------------------------------------
void CBlackOut::move()
{
	//if (isLeft)
	//{
	//	m_rot.z -= 0.01f;
	//}

	////�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	//SetRot(m_rot);
	m_pos += m_move;
}