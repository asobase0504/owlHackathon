//=============================================================================
//
// 鳥の動き
// Author : YudaKaito
//
//=============================================================================
#ifndef _BIRD_H_			// このマクロ定義がされてなかったら
#define _BIRD_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"

class CBird : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d座標で表示
		TYPE_3D,		// 3d座標で表示
		MAX			// あんただれや？
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
