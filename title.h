//**************************************************
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//**************************************************
#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"
#include "object2d.h"

class CBg;
class C3dpolygon;

class CTitle :public CObject
{

	//���(���[�h)�̎��
	enum MODE
	{
		MODE_GAME = 0,			//�Q�[�����	
		MODE_TUTORIAL,
		MODE_RANKING,		//�����L���O���
		MODE_END,
		MODE_MAX
	};

public:
	CTitle();
	~CTitle();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	
private:
	CBg *m_Bg[4];
	CObject2d *Bg;
	CObject2d *Saboten[4];

	C3dpolygon *m_3dpolygon[4];

	CObject2d *m_object2d[4];

	CObject2d *m_list[2];

	CObject2d *fade;
	int m_addX;
	int m_addY;
	int m_tumbleweedPopCount;

	MODE NextMode;
	bool Sizcontroller;
	bool ModeSelect;
	float m_alpha;

};

#endif