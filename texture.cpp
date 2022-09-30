//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "manager.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�X
	/* �� �^�C�g�� �� */
	"Data/TEXTURE/Title/Title.png",
	"Data/TEXTURE/Title/PressEnterorA.png",
	"Data/TEXTURE/Title/Start.png",
	"Data/TEXTURE/Title/Tutorial.png",
	"Data/TEXTURE/Title/TutorialBG.png",
	
	/* �� �Q�[�� �� */
	"Data/TEXTURE/Game/tumbleweed.png",
	"Data/TEXTURE/Game/wilderness.png",
	"Data/TEXTURE/Game/gunman1_1.png",
	"Data/TEXTURE/Game/gunman1_2.png",
	"Data/TEXTURE/Game/gunman1_3.png",
	"Data/TEXTURE/Game/gunman3_1.png",
	"Data/TEXTURE/Game/gunman3_2.png",
	"Data/TEXTURE/Game/gunman3_3.png",
	"Data/TEXTURE/Game/cikin.png",
	"Data/TEXTURE/Game/bird.png",
	"Data/TEXTURE/Game/saboten.png",
	"Data/TEXTURE/Game/Ready.png",
	"Data/TEXTURE/Game/GO.png",
	"Data/TEXTURE/Game/maku.jpeg",
	"Data/TEXTURE/Game/1PWin.png",
	"Data/TEXTURE/Game/2PWin.png",
	"Data/TEXTURE/Game/Draw.png",
	"Data/TEXTURE/Game/Crow01.png",
	"Data/TEXTURE/Game/Crow02.png",

	/* �� �����L���O �� */
	"Data/TEXTURE/RANKING/ranking.jpg",
	"Data/TEXTURE/RANKING/Ranking.png",
	"Data/TEXTURE/RANKING/12345.png",
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}
