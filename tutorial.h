//============================
//
// TUTORIAL��ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//============================
#ifndef _TUTORIAL_H_		//���̃}�N������`����ĂȂ�������
#define _TUTORIAL_H_		//2�d�C���N���[�h�h�~�̃}�N����`

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
