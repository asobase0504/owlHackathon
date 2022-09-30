//============================
//
// TUTORIAL画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _TUTORIAL_H_		//このマクロが定義されてなかったら
#define _TUTORIAL_H_		//2重インクルード防止のマクロ定義

#include "main.h"
#include "object.h"
#include "object2d.h"

class CTutorial :public CObject
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CObject2d *m_bg;	
};

#endif
