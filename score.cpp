//============================
//
// �X�R�A�ݒ�
// Author:hamada ryuuga
//
//============================
#include "score.h"
#include "manager.h"
#include "number.h"


int CScore::m_nScore;
CScore::CScore()
{
}

CScore::~CScore()
{
}

//===================
//����������
//===================
HRESULT CScore::Init()
{
	//m_posScore = D3DXVECTOR3(30.0f, 50.0f, 0.0f);

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{	
		m_pNumber[nCntScore] = CNumber::Create();
		m_pNumber[nCntScore]->SetPos(m_posScore);
		m_pNumber[nCntScore]->SetSize(D3DXVECTOR3 (30.0f, 30.0f, 0.0f));
		m_posScore += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	}

	return S_OK;
}

//===================
//�j������
//===================
void  CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_pNumber[nCntScore]->Uninit();
		m_pNumber[nCntScore] = nullptr;
	}

}

//===================
//�X�V����
//===================
void  CScore::Update(void)
{
}

//===================
//�`�揈��
//===================
void  CScore::Draw(void)
{
}

//===================
//�Z�b�g
//===================
void  CScore::Set(int nScore)
{
	int nCntScore;
	int aPosTexU[MAX_SCORE]; //�e���̐������i�[

	m_nScore = nScore;


	int nModScore = m_nScore;

	for (int i = 7; i >= 0; i--)
	{
		aPosTexU[i] = (nModScore % 10);
		nModScore /= 10;
	}
	
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (aPosTexU[nCntScore] != 0)
		{
			m_pNumber[nCntScore]->SetSpeed(5.0f);
			m_pNumber[nCntScore]->SetNumber(aPosTexU[nCntScore]);
		}
		else
		{
			m_pNumber[nCntScore]->SetSpeed(0.0f);
			m_pNumber[nCntScore]->SetNumber(0);
		}
		m_pNumber[nCntScore]->SetTex(PositionVec4(
	 	0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));
	}
}

//===================
//���Z
//===================
void CScore::Add(int nValue)
{//�X�R�A�̐ݒ��PointItem�̐������ݒ�
	if (*CManager::GetInstance()->GetMode() == CManager::MODE_GAME)
	{
		m_nScore += nValue;
		Set(m_nScore);
	}
}

//===================
//���擾
//===================
int &CScore::GetScore(void)
{
	return m_nScore;
}

CScore *CScore::Create(const D3DXVECTOR3 pos)
{
	CScore * pObject = nullptr;
	pObject = new CScore;

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->Init();
	}

	return pObject;
}
