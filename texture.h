//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		/* �� �^�C�g�� �� */
		TEXTURE_TITLE,			// �^�C�g�����S
		TEXTURE_PRESSENTER,		// �v���X�G���^�[
		TEXTURE_START,			// �X�^�[�g
		TEXTURE_TUTORIAL,		// �`���[�g���A��
		TEXTURE_TUTORIALBG,		// �`���[�g���A���w�i

		/* ���@�Q�[���@�� */
		TEXTURE_TUMBLEWEED,		// �^���u���E�B�[�h
		TEXTURE_WILDERNESS,		// �r��BG
		TEXTURE_PLAYER1_1,		// �K���}���P-�P
		TEXTURE_PLAYER1_2,		// �K���}���P-�Q
		TEXTURE_PLAYER1_3,		// �K���}���P-3
		TEXTURE_PLAYER2_1,		// �K���}���Q-�P
		TEXTURE_PLAYER2_2,		// �K���}���Q-2
		TEXTURE_PLAYER2_3,		// �K���}���Q-3
		TEXTURE_PLAYER_CIKIN,	// �K���}��3-1
		TEXTURE_BIRD,			// ��
		TEXTURE_SABOTEN,		// �T�{�e��
		TEXTURE_READY,			// Reagy
		TEXTURE_GO,				// GO
		TEXTURE_MAKU,			// ��
		TEXTURE_1PWIN,			// 1PWin
		TEXTURE_2PWIN,			// 2PWin
		TEXTURE_DRAW,			// ��������
		TEXTURE_MAX,
		TEXTURE_NONE,	// �g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
