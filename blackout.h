//=============================================================================
//
// �Ó]
// Author : �l�c����
//
//=============================================================================
#ifndef _BLACKOUT_H_			// ���̃}�N����`������ĂȂ�������
#define _BLACKOUT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"


class CBlackOut : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d���W�ŕ\��
		TYPE_3D,		// 3d���W�ŕ\��
		MAX			// ���񂽂����H
	};

	CBlackOut();
	~CBlackOut() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CBlackOut* Create();
private:
	bool isOut;

	void move();
};
#endif
