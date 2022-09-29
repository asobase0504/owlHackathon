//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//���̃}�N����`������ĂȂ�������
#define _SOUND_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#include <xaudio2.h>

//==================================================
// ��`
//==================================================
class CSound
{
	/* ����`�� */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_BGM_TITLE = 0,	// �^�C�g��
		LABEL_BGM_GAME,
		LABEL_BGM_BOSS1,
		LABEL_BGM_BOSS2,
		LABEL_BGM_RESET,
		LABEL_BGM_TUTORIAL,
		LABEL_BGM_RANKING,
		LABEL_SE_HIT,			// HIT
		LABEL_SE_SHOT,			// SHOT
		LABEL_SE_FLARE,			// FLARE
		LABEL_SE_ICE,			// ICE
		LABEL_SE_STORM,			// 
		LABEL_SE_SUN,			// 
		LABEL_SE_MOVE,			// 
		LABEL_SE_NO,			// �L�����Z��
		LABEL_SE_ON,			// ����
		LABEL_SE_KIKEN,			// 
		LABEL_SE_TAIKO,				// 
		LABEL_SE_RAION,				// 
		LABEL_SE_ROBO,				
		LABEL_SE_BOOTH,				// 
		LABEL_SE_YOBI,				// 
		LABEL_SE_GOLD,				// 
		LABEL_MAX,	
	};

	struct SParam
	{
		char *pFileName;	// �t�@�C����
		int loop;			// ���[�v
	};

	static const SParam PARAM[];	// �p�����[�^�̏��

	/* �������o�֐��� */
public:
	CSound();	// �f�t�H���g�R���X�g���N�^
	~CSound();	// �f�X�g���N�^

public:
	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT Play(ELabel sound);
	void Stop(ELabel label);
	void Stop();

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// �`�����N�̃`�F�b�N
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�̓ǂݍ���

	/* �������o�ϐ��� */
private: 
	IXAudio2* m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_pDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_sizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif // !_SOUND_H_
