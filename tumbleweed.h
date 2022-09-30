//=============================================================================
//
// ������
// Author : �l�c����
//
//=============================================================================


#ifndef _2DPOLYGONTEMPLATE_H_			// ���̃}�N����`������ĂȂ�������
#define _2DPOLYGONTEMPLATE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// �]���鑐
//-----------------------------------------------------------------------------
class CTumbleweed : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d���W�ŕ\��
		TYPE_3D,		// 3d���W�ŕ\��
		MAX			// ���񂽂����H
	};

	CTumbleweed();
	~CTumbleweed() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CTumbleweed* Create(D3DXVECTOR3 pos, bool b3D);
private:
	void move();
private:
	D3DXVECTOR3 m_rot;
	int nLife;
};
#endif