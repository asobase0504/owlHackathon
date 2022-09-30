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
CBlackOut *CBlackOut::Create()
{
	CBlackOut * pObject = new CBlackOut;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// �X�N���[���T�C�Y
		
		pObject->Init();
		pObject->SetPos(popPos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);		// �e�N�X�`���I��
		pObject->SetMove(D3DXVECTOR3(0.0f, 1.75f, 0.0f));		// move�̐ݒ�
		pObject->SetSize(CManager::Pos);	// �T�C�Y�ݒ�
		pObject->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	// �F�ݒ�
	}
	return pObject;
}


//------------------------------------
// �����n��
//------------------------------------
void CBlackOut::move()
{
	m_pos += m_move;
}