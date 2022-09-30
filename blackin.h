//=============================================================================
//
// �Ó]
// Author : YudaKaito
//
//=============================================================================
#ifndef _BLACKIN_H_			// ���̃}�N����`������ĂȂ�������
#define _BLACKIN_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"


class CBlackIn : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d���W�ŕ\��
		TYPE_3D,		// 3d���W�ŕ\��
		MAX			// ���񂽂����H
	};

	CBlackIn();
	~CBlackIn() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CBlackIn* Create(bool isLeft);

	bool GetStop() { return isStop; }
private:
	bool isLeft;
	bool isStop;
	int nLife;
	D3DXVECTOR3 m_rot;

	void move();
};
#endif
