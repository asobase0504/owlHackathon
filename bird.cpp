//============================
//
// ���̓���
// Author: Yuda Kaito
//
//============================
#include "bird.h"
#include "utility.h"

#include "sound.h"
#include "manager.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CBird::CBird() :CObject2d(0)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CBird::~CBird()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CBird::Init()
{
	CObject2d::Init();

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CROW);

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CBird::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CBird::Update()
{
	CObject2d::Update();
	//����
	move();
}

//------------------------------------
// �`��
//------------------------------------
void CBird::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CBird *CBird::Create()
{
	D3DXVECTOR3 pos(800.0f, FloatRandam(180.0f, 280.0f), 0.0f);
	D3DXVECTOR3 move(FloatRandam(4.0f, 7.0f), 0.0f, 0.0f);

	move *= -1;

	CBird * pObject = new CBird;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 popPos = pos;

		popPos = ScreenCastWorld(&popPos, D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));		// �X�N���[���T�C�Y

		pObject->Init();
		pObject->SetPos(popPos);
		pObject->nLife = 700;
		pObject->SetTexture(CTexture::TEXTURE_BIRD);		// �e�N�X�`���I��
		pObject->SetMove(move);		// move�̐ݒ�
		pObject->SetSize(D3DXVECTOR3(25.0f, 25.0f, 0.0f));	// �T�C�Y�ݒ�
		pObject->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �F�ݒ�
	}
	return pObject;
}


//------------------------------------
// �����n��
//------------------------------------
void CBird::move()
{
	m_pos += m_move;
}