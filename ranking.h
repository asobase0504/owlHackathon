//=============================================================================
//
// ranking.h
// Author : koduna hirohito
//
//=============================================================================
#ifndef _RANKING_H_			//このマクロ定義がされなかったら
#define _RANKING_H_			//2重インクルード防止のマクロ定義

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "name.h"
#include "object.h"

class CObject2d;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRanking :public CObject
{
private:
	static const int MAX_RANKING_DIGIT = 8;
	static const int MAX_AIRFRAME = 3;
	static const int MAX_STAGE = 6;
	static const int RANKING_MAX = 4;

public:
	struct NameData
	{
		int nNameNumIndex[RANKING_MAX];
	};


	static const int MAX_RANKING = 5;
	CRanking();
	~CRanking();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Create();

private:
	float m_fScore[MAX_RANKING];
	bool m_bNewScore;
	NameData m_NameData[MAX_RANKING];
	CObject2d *Bg;
};

#endif