//=============================================================================
//
// 暗転
// Author : YudaKaito
//
//=============================================================================
#ifndef _BLACKIN_H_			// このマクロ定義がされてなかったら
#define _BLACKIN_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"


class CBlackIn : public CObject2d
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d座標で表示
		TYPE_3D,		// 3d座標で表示
		MAX			// あんただれや？
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
