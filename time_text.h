//=========================================
// 
// チュートリアル内クラス
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
// アプリケーションクラス
//-----------------------------------------
class CTImeText
{
public:	// メンバー関数
	CTImeText();
	~CTImeText();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	int SetText(float inText,D3DXVECTOR3 pos);
	void AllDelete();
private: // 動的メンバー変数

	/* フォント関係 */
	DESIGNVECTOR m_design;
	LPD3DXFONT m_font;
	std::vector<float> m_text;
	std::vector<D3DXVECTOR3> m_pos;
	bool isResetText;
};

#endif // !_GAME_H_
