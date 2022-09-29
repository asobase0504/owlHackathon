//=============================================================================
//
// 3dpolygon
// Author : �l�c����
//
//=============================================================================


#ifndef _3DPOLYGON_H_			// ���̃}�N����`������ĂȂ�������
#define _3DPOLYGON_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "texture.h"
#include "object2d.h"

#define SIZEX (45.0f)
#define SIZEY (90.0f)
#define TIMER (m_nTimer + 90)

class  C3dpolygon : public CObject
{
protected:
	//polygon�̊�T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:

	static C3dpolygon *Create(int list = 0);

	C3dpolygon(int list = 0);
	~C3dpolygon() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	virtual const D3DXVECTOR3 *GetPos() const;
	virtual void SetPos(const D3DXVECTOR3 &pos);
	virtual void SetMove(const D3DXVECTOR3 &move) { m_Move = move; };
	
	void SetTexture(CTexture::TEXTURE texture);
	void SetTex(PositionVec4 Tex);
	void SetSize(const D3DXVECTOR3 &size);
	void SetCollar(D3DXCOLOR Collar);
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	LPDIRECT3DVERTEXBUFFER9 &GetVtx();

	static void PolygonReset() { m_MaxPolygon = 0; };
protected:
	float m_nScale;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos; //polygon�̈ʒu
	D3DXVECTOR3 m_Size;
	D3DXMATRIX m_mtxWorld;					// �}�g���b�N�X
	int  m_nTimer;
	D3DXVECTOR3  m_Move;
private:
	static int m_MaxPolygon;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = nullptr;
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

};

#endif
