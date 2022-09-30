//=============================================================================
//
// �Ö�
// Author : YudaKaito
//
//=============================================================================
#ifndef _CURTAIN_H_			// ���̃}�N����`������ĂȂ�������
#define _CURTAIN_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"

class CBlackIn;
class CBlackOut;

class CCurtain
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d���W�ŕ\��
		TYPE_3D,		// 3d���W�ŕ\��
		MAX			// ���񂽂����H
	};

	CCurtain();
	~CCurtain();
	
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetOut();

	static CCurtain* Create();
private:
	bool isIn;
	CBlackIn* m_blackIn[2];
	CBlackOut* m_blackOut[2];
};
#endif
