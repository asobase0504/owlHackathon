//============================
//
// ���U���g���
// Author:hamada ryuuga
//
//============================
//------------------------
// �C���N���[�h
//------------------------
#include "tutorial.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "motion.h"
#include "bg.h"
#include "particle_manager.h"
#include "score.h"
#include "life.h"
#include "text.h"
#include "multiply.h"

//========================
// �R���X�g���N�^�[
//========================
CTutorial::CTutorial()
{
}

//========================
// �f�X�g���N�g
//========================
CTutorial::~CTutorial()
{
}

//========================
// ����������
//========================
HRESULT CTutorial::Init(void)
{
	m_bg = CObject2d::Create();
	m_bg->SetTexture(CTexture::TEXTURE_TUTORIALBG);
	m_bg->SetPos(CManager::Pos);
	m_bg->SetSize(CManager::Pos);
	m_bg->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//========================
// �I������
//========================
void CTutorial::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	
	if (m_bg != nullptr)
	{
		m_bg->Uninit();
	}

	CManager::GetInstance()->GetSound()->Stop();
	CModelManager::ReleaseAll();
}

//========================
// �X�V����
//========================
void CTutorial::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(KEY_DECISION))
	{
		//���[�h�̐ݒ�
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
	}
}

//========================
// �`�揈��
//========================
void CTutorial::Draw(void)
{

}