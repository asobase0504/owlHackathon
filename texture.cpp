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
	"data/TEXTURE/wa.jpg",			//�ʉ摜
	"data/TEXTURE/gon.png",			//GON
	"data/TEXTURE/fire.png",		//��
	"data/TEXTURE/ice.png",			//�X
	"data/TEXTURE/storm.png",		//��
	"data/TEXTURE/sun.png",         //��
	"data/TEXTURE/daia.png",		//CRYSTAL
	"data/TEXTURE/Score001.png",	//score
	"data/TEXTURE/impact.png",		//��
	"data/TEXTURE/Iceburst.png",	//�X	
	"data/TEXTURE/tempest.png",		//��
	"data/TEXTURE/rain.png",		//��
	"data/TEXTURE/smoke.jpg",		//��
	"data/TEXTURE/light.png",		//��
	"data/TEXTURE/Box.png",			//BOX�w�i
	"data/TEXTURE/HIT.png",			//���i�N���X�^����HIT�j
	"data/TEXTURE/MagicCircle1.png",//���@�w
	"data/TEXTURE/MagicCircle3.png",
	"data/TEXTURE/MagicCircle4.png",
	"data/TEXTURE/MagicCircle5.png",
	"data/TEXTURE/MagicCircle2.png",
	"Data/TEXTURE/star.png",		//�w�i�P
	"Data/TEXTURE/town.png",		//�w�i�Q
	"Data/TEXTURE/moon.png",		//�w�i�R
	"Data/TEXTURE/BG.png",			//��������TITLE
	"Data/TEXTURE/GonBG.png",
	"Data/TEXTURE/Fox.png",
	"Data/TEXTURE/gamestart.png",
	"Data/TEXTURE/start.png",
	"Data/TEXTURE/tutorial.png",
	"Data/TEXTURE/ranking.png",
	"Data/TEXTURE/end.png",			
	"Data/TEXTURE/Getrotation.png",	//�������烊�U���g
	"Data/TEXTURE/siro.jpg",
	"Data/TEXTURE/wallpaper_00405.jpg",//�������烉���L���O
	"Data/TEXTURE/ranking_rank.png",
	"Data/TEXTURE/ranking000.png",
	"Data/TEXTURE/ranking001.png",
	"Data/TEXTURE/alphabet_ucase.png",
	"Data/TEXTURE/cover.png",
	"Data/TEXTURE/tutoria.png",
	"Data/TEXTURE/sky_00290.png",
	"Data/TEXTURE/pause004.png",
	"Data/TEXTURE/pause000.png",
	"Data/TEXTURE/pause001.png",
	"Data/TEXTURE/pause002.png",
	"Data/TEXTURE/Bosscover.png",
	"Data/TEXTURE/controller.png",
	"Data/TEXTURE/gonText.png",
	"Data/TEXTURE/kumaText.png",
	"Data/TEXTURE/NameSet000.png",
	"Data/TEXTURE/pipo-gwspinitem013.png",
	"Data/TEXTURE/explosion.png",
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
