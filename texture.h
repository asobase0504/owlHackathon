//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		/* ↓ タイトル ↓ */
		TEXTURE_TITLE,			// タイトルロゴ
		TEXTURE_PRESSENTER,		// プレスエンター
		TEXTURE_START,			// スタート
		TEXTURE_TUTORIAL,		// チュートリアル
		TEXTURE_TUTORIALBG,		// チュートリアル背景

		/* ↓　ゲーム　↓ */
		TEXTURE_TUMBLEWEED,		// タンブルウィード
		TEXTURE_WILDERNESS,		// 荒野BG
		TEXTURE_PLAYER1_1,		// ガンマン１-１
		TEXTURE_PLAYER1_2,		// ガンマン１-２
		TEXTURE_PLAYER1_3,		// ガンマン１-3
		TEXTURE_PLAYER2_1,		// ガンマン２-１
		TEXTURE_PLAYER2_2,		// ガンマン２-2
		TEXTURE_PLAYER2_3,		// ガンマン２-3
		TEXTURE_PLAYER_CIKIN,	// ガンマン3-1
		TEXTURE_BIRD,			// 鳥
		TEXTURE_SABOTEN,		// サボテン
		TEXTURE_READY,			// Reagy
		TEXTURE_GO,				// GO
		TEXTURE_MAKU,			// 幕
		TEXTURE_1PWIN,			// 1PWin
		TEXTURE_2PWIN,			// 2PWin
		TEXTURE_DRAW,			// 引き分け
		TEXTURE_MAX,
		TEXTURE_NONE,	// 使用しない
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
