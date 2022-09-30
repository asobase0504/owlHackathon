//=============================================================================
//
// ���̓���
// Author : YudaKaito
//
//=============================================================================
#ifndef _BIRD_H_			// ���̃}�N����`������ĂȂ�������
#define _BIRD_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"

class CBird : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d���W�ŕ\��
		TYPE_3D,		// 3d���W�ŕ\��
		MAX			// ���񂽂����H
	};

	CBird();
	~CBird() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CBird* Create();
private:
	void move();
private:
	D3DXVECTOR3 m_Testrot;
	int nLife;
};
#endif
