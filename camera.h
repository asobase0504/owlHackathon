//============================
//
// �J�����ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "renderer.h"

class CCamera
{


public:
	CCamera();
	~CCamera();

	void Init(void);//������
	void Uninit(void);//�j��
	void Update(void);//�X�V
	void Set(int Type);//��ʐݒ�
	D3DXMATRIX *GetMtxProje();
	D3DXMATRIX *GetMtxView();
	D3DXVECTOR3 *GetPos();
	D3DXVECTOR3 *GetRot();
private:

	 float m_Speed = 1.0f;

	 float m_rotSpeed = 0.05f;
	 float m_rotSpeed2 = D3DX_PI / 2;

	 D3DXVECTOR3 m_posV;	//�ʒu
	 D3DXVECTOR3 m_posR;	//�����_
	 D3DXVECTOR3 m_vecU;	//�x�N�g��
	 D3DXVECTOR3 m_directionV; //��]�̌����ʒu
	 D3DXVECTOR3 m_directionR;//��]�̌��������_
	 D3DXVECTOR3 m_rot;//�ʒu��]
	 float m_fDistance;//����
	 float m_fDistanceY;
	 D3DVIEWPORT9 m_viewport;
	 D3DXVECTOR3 posVDest, m_posRDest;
	 D3DXMATRIX m_MtxProje; //�v���W�F�N�V�����}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	 D3DXMATRIX m_MtxView; //�r���[�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	 int m_Type;

};
#endif

