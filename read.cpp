//=============================================================================
//
// read.cpp
// Author : koduna hirohito
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "read.h"
#include <stdio.h>
#include "manager.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CRead::CRead()
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CRead::~CRead()
{
}

//*****************************************************************************
// �����L���O�̃��[�h
//*****************************************************************************
void CRead::ReadRanking(float *pRanking)
{
	float fPLTime = CManager::GetPLTime();
	float aTime[CRanking::MAX_RANKING + 1] = {};
	aTime[CRanking::MAX_RANKING] = fPLTime;
	FILE *pFile = nullptr;			//�t�@�C���|�C���^�[�錾
	pFile = fopen("Ranking.txt", "r");

	if (pFile == nullptr)
	{//�J���Ȃ��������p
		return;
	}
	for (int nCnt = 0; nCnt < CRanking::MAX_RANKING; nCnt++)
	{
		fscanf(pFile, "%f", &aTime[nCnt]);
	}
	//�t�@�C�������
	fclose(pFile);

	float fScore = 0.0f;
	CRanking::NameData namedata = {};

	for (int nCnt1 = 0; nCnt1 < CRanking::MAX_RANKING; nCnt1++)
	{
		for (int nCnt2 = (nCnt1 + 1); nCnt2 < CRanking::MAX_RANKING + 1; nCnt2++)
		{
			if (aTime[nCnt1] >= aTime[nCnt2])
			{
				fScore = aTime[nCnt2];
				aTime[nCnt2] = aTime[nCnt1];
				aTime[nCnt1] = fScore;
			}
		}
	}

	for (int nCnt1 = 0; nCnt1 < CRanking::MAX_RANKING; nCnt1++)
	{
		pRanking[nCnt1] = aTime[nCnt1];
	}

	SaveRanking(&aTime[0]);
}

//*****************************************************************************
// �����L���O�̃Z�[�u
//*****************************************************************************
void CRead::SaveRanking(const float *pRanking)
{
	FILE *pFile = nullptr;			//�t�@�C���|�C���^�[�錾
	pFile = fopen("Ranking.txt", "w");

	if (pFile == nullptr)
	{//�J���Ȃ��������p
		return;
	}
	for (int nCnt = 0; nCnt < CRanking::MAX_RANKING; nCnt++)
	{
		fprintf(pFile, "%f\n",pRanking[nCnt]);
	}
	//�t�@�C�������
	fclose(pFile);
}