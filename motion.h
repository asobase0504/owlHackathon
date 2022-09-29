//**************************************************************************************************
//
// ���[�V��������(motion.h)
// Auther�F�������l
// �T�v : ���[�V�����N���X�̐ݒ�
//
//**************************************************************************************************
#ifndef _MOTION_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include"main.h"
#include "renderer.h"



//=============================================================================
// ���[�V�����N���X
// Author : �������l
// �T�v : ���[�V�����ݒ���s���N���X
//=============================================================================
class CMotion
{
public:

	enum MODELCOLLAR
	{
		LET = 0,
		BLUE,
		YELLOW,
		GREEN,
		NON,
		MAX
	};
	//***************************************************************************
	// �萔��`
	//***************************************************************************
	static const unsigned int MAX_MOTION = (7);					// ���[�V�������̍ő吔
	static const unsigned int MAX_MODEL_PARTS = (30);				// ���f�����̍ő吔
	static const unsigned int MAX_KEY = (64);						// �L�[�̍ő吔
	static const unsigned int MAX_KEYSET = (64);					// �L�[�ݒ�̍ő吔
	static const unsigned int MOTION_BLEND_FRAM = (12);				// ���[�V�����u�����h�̃t���[����	

	//***************************************************************
	// �p�[�c�t�@�C���\���̂��`
	//***************************************************************
	struct PartsFile
	{
		char	aName[MAX_MODEL_PARTS];		// ���O
	};

	//***************************************************************
	// �L�[�\���̂��`
	//***************************************************************
	struct MyKey
	{
		D3DXVECTOR3		pos;	// ���݈ʒu
		D3DXVECTOR3		rot;	// ���݂̌���
	};

	//***************************************************************
	// �L�[�ݒ�\���̂��`
	//***************************************************************
    struct MyKeySet
	{
		int		nFrame;			// �t���[����
		MyKey	key[MAX_KEY];	// �L�[���
	};

	//***************************************************************
	// ���[�V�����ݒ�\���̂��`
	//***************************************************************
	struct MyMotion
	{
		int				nNumKey;				// �L�[��
		int				nCntKeySet;				// �L�[�Z�b�g�J�E���g
		int				nCntFrame;				// �t���[���J�E���g
		bool			bLoop;					// ���[�v�g�p��
		MyKeySet		keySet[MAX_KEYSET];		// �L�[�ݒ���
	};

	//***************************************************************
	// ���f���p�[�c�\���̂��`
	//***************************************************************
	struct Parts
	{
		LPD3DXMESH		pMesh;					// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffer;				// �}�e���A�����ւ̃|�C���^
		DWORD			nNumMat;				// �}�e���A�����̐�
		D3DXMATRIX		mtxWorld;				// ���[���h�}�g���b�N�X
		D3DXVECTOR3		posOrigin;				// ���̈ʒu
		D3DXVECTOR3		rotOrigin;				// ���̌���
		D3DXVECTOR3		pos;					// ���݂̈ʒu
		D3DXVECTOR3		rot;					// ���݂̌���
		D3DXVECTOR3		posDest;				// �ړI�̈ʒu
		D3DXVECTOR3		rotDest;				// �ړI�̌���
		int				nIdxModelParent;		// �e���f���̃C���f�b�N�X��
		int				nType;					// �p�[�c�̃^�C�v
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMotion(char *pFileName);
	~CMotion();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	// ������
	void Init(void);

	// �p�[�c�̐ݒ�
	void SetParts(D3DXMATRIX mtxWorld, CMotion::MODELCOLLAR Type);							// �}�e���A���f�[�^

	// ���[�V�����̍Đ�
	bool PlayMotion(const int nCntMotionSet);

	// ���[�V�����u�����h
	bool MotionBlend(const int nCntMotionSet);	

	// ���[�V�����ǂݍ���
	void LoodSetMotion(char *pFileName);

	// �I��
	void Uninit(void);

	// �J�E���g���Z�b�g
	void CntReset(const int nNumMotionOld);

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	MyMotion	*m_motion;							// ���[�V����
	Parts		*m_parts;							// �p�[�c
	PartsFile	m_partsFile[MAX_MODEL_PARTS];		// �p�[�c��X�t�@�C����
	int			m_nMaxParts;						// �p�[�c��
	int			m_nType;
};

class CModel
{
public: /* ��` */

	CModel();
	~CModel() {};

	// �I������
	void Uninit() 
	{
		if (pBuffer != NULL)
		{// ���_�o�b�t�@�[�̉��
			pBuffer->Release();
			pBuffer = NULL;
		}

		if (pMesh != NULL)
		{// ���b�V���̉��
			pMesh->Release();
			pMesh = NULL;
		}
	}

	int				nType;					// �p�[�c�̃^�C�v
	LPD3DXMESH		pMesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffer;				// �}�e���A�����ւ̃|�C���^
	DWORD			nNumMat;				// �}�e���A�����̐�
	char		    m_xFilename[256];
};

//=============================================================================
// ���f���}�l�[�W���[�@
// Author : �l�c����
// �T�v : ���f���̃f�[�^��ۑ����Ă���
//=============================================================================
class CModelManager
{
public: /* ��` */


	static const int MODEL_MAX = 100;

private:
	static CModelManager * ms_ModelManager;

public:
	CModelManager();		// �f�t�H���g�R���X�g���N�^
	~CModelManager();	// �f�X�g���N�^

public: /* �����o�֐� */
	static CModelManager *GetManager();
	CModel* Load(const char *pXFileName);	
	CModel* LoadXfile(const char *pXFileName);	// �w��̓ǂݍ���
	static void ReleaseAll();
public: /* �����o�ϐ� */
	CModel* m_apModel[MODEL_MAX];
};





#endif

