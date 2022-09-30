//=============================================================================
//
// 暗転
// Author : 浜田琉雅
//
//=============================================================================
#ifndef _BLACKOUT_H_			// このマクロ定義がされてなかったら
#define _BLACKOUT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"


class CBlackOut : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d座標で表示
		TYPE_3D,		// 3d座標で表示
		MAX			// あんただれや？
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
