//=============================================================================
//
// 暗幕
// Author : YudaKaito
//
//=============================================================================
#ifndef _CURTAIN_H_			// このマクロ定義がされてなかったら
#define _CURTAIN_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"

class CBlackIn;
class CBlackOut;

class CCurtain
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d座標で表示
		TYPE_3D,		// 3d座標で表示
		MAX			// あんただれや？
	};

	CCurtain();
	~CCurtain();
	
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetOut();

	static CCurtain* Create();
private:
	bool isIn;
	CBlackIn* m_blackIn[2];
	CBlackOut* m_blackOut[2];
};
#endif
