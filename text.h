//============================
//
// TEXT
// Author:hamada ryuuga
//
//============================

#ifndef _TEXT_H_
#define _TEXT_H_

#include "object2d.h"

class CText : public CObject2d
{
public:

	enum Type
	{
		GON = 0,
		MASUO,
		MAX
	};

	CText(int list);
	~CText();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CText* Create(Type talkType, int DeleteTime, int SpeedText, const char * Text);

	void Releasetimer(int nTimar);
private:
	D3DXCOLOR  m_col;
	int m_DesTimarMax;//������ő厞��
	int m_DesTimar;//�����鎞��

	int m_TextSize;//�����̃T�C�Y
	int m_Addnumber;//1�̕��������Z�����܂ł̎���
	int m_AddCount;//���������Z�����܂ł̃J�E���g
	int m_AddLetter;//�������ړ���邩�w��

	bool m_isRelease;

	LPD3DXFONT m_pFont = nullptr;

	std::string m_Text;
	std::string m_ALLText;

	void TextLetter(const char * Text, int SpeedText);
};


#endif#pragma once
