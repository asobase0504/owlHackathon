//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//このマクロ定義がされてなかったら
#define _SOUND_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#include <xaudio2.h>

//==================================================
// 定義
//==================================================
class CSound
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_BGM_TITLE = 0,	// タイトル
		LABEL_BGM_GAME,
		LABEL_BGM_BOSS1,
		LABEL_BGM_BOSS2,
		LABEL_BGM_RESET,
		LABEL_BGM_TUTORIAL,
		LABEL_BGM_RANKING,
		LABEL_SE_SHOT,			// SHOT
		LABEL_SE_CROW,			// カラス
		LABEL_SE_CAN,			// 空き缶の音
		LABEL_SE_SET_UP,		// 銃を構える音
		LABEL_SE_DROP_GUM,		// 銃を落とす
		LABEL_SE_WEED,			// 草
		LABEL_SE_WIND,			// 風
		LABEL_SE_SELECT,		// 選択音
		LABEL_MAX,	
	};

	struct SParam
	{
		char *pFileName;	// ファイル名
		int loop;			// ループ
	};

	static const SParam PARAM[];	// パラメータの情報

	/* ↓メンバ関数↓ */
public:
	CSound();	// デフォルトコンストラクタ
	~CSound();	// デストラクタ

public:
	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT Play(ELabel sound);
	void Stop(ELabel label);
	void Stop();

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// チャンクのチェック
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// チャンクデータの読み込み

	/* ↓メンバ変数↓ */
private: 
	IXAudio2* m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;		// マスターボイス
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE* m_pDataAudio[LABEL_MAX];					// オーディオデータ
	DWORD m_sizeAudio[LABEL_MAX];					// オーディオデータサイズ
};

#endif // !_SOUND_H_
