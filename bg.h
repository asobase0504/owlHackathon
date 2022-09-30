//=============================================================================
//
// BG�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================
#ifndef _BG_H_			// ���̃}�N����`������ĂȂ�������
#define _BG_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CBg : public C3dpolygon
{
public:
	enum BgType
	{
		MOVE = 0,	// ������[��
		STOP,		// �����Ȃ���[��
		MAX			// ���񂽂����H
	};

	static CBg *CBg::Create();

	CBg(const int list);
	~CBg() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;

	void SetBgType(const BgType &Type) { BgType = Type; };

private:
	D3DXVECTOR3 m_Speed;
	D3DXVECTOR3 m_MoveSpeed;
	D3DXVECTOR3 m_AddSpeed;
	BgType BgType;
};

#endif
