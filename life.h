//=============================================================================
//
// LIFE
// Author : �l�c����
//
//=============================================================================


#ifndef _LIFE_H_			// ���̃}�N����`������ĂȂ�������
#define _LIFE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object2d.h"
#include "texture.h"

class CLife : public CObject2d
{
private:


public:
	static CLife *Create(const D3DXVECTOR3 & pos, float Life);

	CLife(const int list);
	~CLife() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;
	
	void SetDamage(const int Damage);
	static bool GetMaxLife() { return m_MaxHp; };

private:
	float m_Life;
	float m_MaxLife;
	static bool m_MaxHp;
	D3DXVECTOR3 m_SetUpPos;
	CObject2d *m_object2d[1];

};

#endif

