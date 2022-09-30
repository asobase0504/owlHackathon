//=============================================================================
//
// ranking.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "ranking.h"
#include "read.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "time_text.h"

#include "manager.h"
#include "sound.h"
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CRanking::CRanking()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CRanking::~CRanking()
{
}

//*****************************************************************************
// ������
//*****************************************************************************
HRESULT CRanking::Init()
{
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);

	// �w�i�̍r��
	Bg = CObject2d::Create();
	Bg->SetTexture(CTexture::TEXTURE_RANKING);
	Bg->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));
	Bg->SetSize(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));

	m_bNewScore = false;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_fScore[nCnt] = 0.0f;
	}
	CRead Cread;
	Cread.ReadRanking(&m_fScore[0]);

	for (int i = 0; i < MAX_RANKING; i++)
	{
		D3DXVECTOR3 pos(CManager::GetInstance()->Pos);
		pos.x *= 0.75f;
		pos.y -= 100.0f * i - 200.0f;
		CManager::GetInstance()->GetText()->SetText(m_fScore[(MAX_RANKING-1) - i], pos);
	}

	return S_OK;
}

void CRanking::Uninit()
{
	CManager::GetInstance()->GetText()->AllDelete();

	CManager::GetInstance()->GetSound()->Stop();
}

void CRanking::Update()
{
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(KEY_DECISION))
	{
		CManager* maneger = CManager::GetInstance();
		//���[�h�̐ݒ�
		maneger->GetFade()->NextMode(CManager::MODE_TITLE);
	}

}

void CRanking::Draw()
{
}

//*****************************************************************************
// ���l�̐ݒ�
//*****************************************************************************
void CRanking::Create()
{
	
	
}