//=========================================
// 
// �`���[�g���A�����N���X
// Author YudaKaito
// 
//=========================================
#ifndef _TIME_TEXT_H_
#define _TIME_TEXT_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <d3dx9.h>

//-----------------------------------------
// �A�v���P�[�V�����N���X
//-----------------------------------------
class CTImeText
{
public:	// �����o�[�֐�
	CTImeText();
	~CTImeText();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	int SetText(float inText,D3DXVECTOR3 pos);
	void AllDelete();
private: // ���I�����o�[�ϐ�

	/* �t�H���g�֌W */
	DESIGNVECTOR m_design;
	LPD3DXFONT m_font;
	std::vector<float> m_text;
	std::vector<D3DXVECTOR3> m_pos;
	bool isResetText;
};

#endif // !_GAME_H_
