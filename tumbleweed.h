//=============================================================================
//
// 説明書
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _2DPOLYGONTEMPLATE_H_			// このマクロ定義がされてなかったら
#define _2DPOLYGONTEMPLATE_H_			// 二重インクルード防止のマクロ定義

//=============================================================================
//
// Object
// Author : 浜田琉雅
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// 転がる草
//-----------------------------------------------------------------------------
class CTumbleweed : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d座標で表示
		TYPE_3D,		// 3d座標で表示
		MAX			// あんただれや？
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
