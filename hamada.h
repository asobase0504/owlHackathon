//=============================================================================
//
// �֗��֐�
// Author : �l�c����
//
//=============================================================================

#ifndef _HAMADA_H_			// ���̃}�N����`������ĂȂ�������
#define _HAMADA_H_			// ��d�C���N���[�h�h�~�̃}�N����`


#include "renderer.h"

namespace hmd
{

	D3DXMATRIX *giftmtx(D3DXMATRIX *pOut,D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	float easeInSine(float X);
	float easeInQuad(float X);
}



#endif
