//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _MANEAGER_H_			// このマクロ定義がされてなかったら
#define _MANEAGER_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"

class CRenderer;
class CInput;
class CTexture;
class CObject;
class CResult;
class CTitle;
class CFade;
class CSound;
class CTImeText;

class CManager
{
public:
	// スクリーンの幅
	static const int SCREEN_WIDTH = 1280;
	// スクリーンの高さ
	static const int SCREEN_HEIGHT = 720;

public:

	static const D3DXVECTOR3 Pos;

	//画面(モード)の種類
	enum MODE
	{
		MODE_TITLE = 0,		//タイトル画面
		MODE_GAME,			//ゲーム画面
		MODE_RESULT,		//リザルト画面
		MODE_FADE,			//フェード画面
		MODE_RANKING,		//ランキング画面
		MODE_GAMEOVER,
		MODE_TUTORIAL,
		MODE_NAMESET,
		MODE_MAX
	};

public: // 静的メンバー変数
	static CManager* m_manager;
	static float m_fTime;
public: // 静的関数
	static CManager* GetInstance();
	static float GetPLTime() { return m_fTime; }
	static void SetPLTime(float fTime) { m_fTime = fTime; }

private: // シングルトン
	CManager();

public:	// メンバー関数
	~CManager();

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	CRenderer *GetRenderer();
	CTexture* GetTexture();	// テクスチャの情報の取得
	CFade* GetFade();	// 
	MODE* GetMode();	//
	CTImeText* GetText();
	void SetMode(CManager::MODE mode);
	CSound * CManager::GetSound();

private:
	CTexture *m_pTexture;
	CRenderer * m_cRenderer;
	CFade* m_Fade;
	CObject*m_Game;
	CSound*m_Sound;
	CTImeText* m_text;
	MODE m_mode;

	CInput *m_Input;

};



#endif
