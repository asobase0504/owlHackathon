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
		pos.y -= 70.0f * i;
		CManager::GetInstance()->GetText()->SetText(m_fScore[i], pos);
	}

	return S_OK;
}

void CRanking::Uninit()
{
	CManager::GetInstance()->GetText()->AllDelete();
}

void CRanking::Update()
{
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Press(KEY_DECISION))
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