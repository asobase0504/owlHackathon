//=============================================================================
//
// ���͏��� [inputkeydata.h]
// Author : KOZUNA HIROHITO
// 
//=============================================================================

#ifndef _INPUT_KEY_DATA_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_KEY_DATA_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�񋓌^��`
//----------------------------------------------------------------------------

//�����L�[�ꗗ
enum STAN_DART_INPUT_KEY
{						//					�L�[�{�[�h						�W���C�p�b�h
	KEY_UP = 0,			//��			 W & UP							�X�e�B�b�N��@���@�\���L�[��
	KEY_UP_LEFT,		//����			(W&A)  &  (UP&Left)				�X�e�B�b�N����@���@�i�\���L�[��@���@�\���L�[���j
	KEY_UP_RIGHT,		//�E��			(W&D)  &  (UP&Right)			�X�e�B�b�N�E��@���@�i�\���L�[��@���@�\���L�[�E�j
	KEY_DOWN,			//��			 S  & Down						�X�e�B�b�N���@���@�\���L�[��
	KEY_DOWN_LEFT,		//����			(S&A)  &  (Down&Left)			�X�e�B�b�N�����@���@�i�\���L�[���@���@�\���L�[���j
	KEY_DOWN_RIGHT,		//�E��			(S&D)  &  (Down&Right)			�X�e�B�b�N�E���@���@�i�\���L�[���@���@�\���L�[�E�j
	KEY_LEFT,			//��			 A  &  Left)					�X�e�B�b�N���@���@�\���L�[��
	KEY_RIGHT,			//�E			 D  &  Right					�X�e�B�b�N�E�@���@�\���L�[�E
	KEY_DECISION,		//����			 �G���^�[�L�[								A
	KEY_SHOT,			//�X�y�[�X		 �X�y�[�X�L�[								R1
	KEY_BACK,			//�o�b�N		 �o�b�N�X�y�[�X�L�[ & B						B
	KEY_SHIFT,			//�V�t�g		 �V�t�g���E									L1
	KEY_MOVE,			//�ړ��n���ׂ�
	KEY_PAUSE,			//�|�[�Y�{�^��	 P											START
	KEY_MAX
};

//�L�[���(�W���C�p�b�h�\���L�[�̂�)
enum JOYKEY_DIRECT_CROSS
{
	JOYKEY_CROSS_UP = 0,
	JOYKEY_CROSS_UP_RIGHT = 4500,
	JOYKEY_CROSS_RIGHT = 9000,
	JOYKEY_CROSS_DOWN_RIGHT = 13500,
	JOYKEY_CROSS_DOWN = 18000,
	JOYKEY_CROSS_DOWN_LEFT = 22500,
	JOYKEY_CROSS_LEFT = 27000,
	JOYKEY_CROSS_UP_LEFT = 31500,
	JOYKEY_CROSS_MAX
};

//�L�[���(�W���C�p�b�h)
enum DirectJoypad
{
	JOYPAD_X = 0,				//X�{�^��
	JOYPAD_Y,					//Y�{�^��
	JOYPAD_A,					//A�{�^��
	JOYPAD_B,					//B�{�^��
	JOYPAD_L1,					//L1�{�^��
	JOYPAD_R1,					//R1�{�^��
	JOYPAD_L2,					//L2�{�^��
	JOYPAD_R2,					//R2�{�^��
	JOYPAD_LT,					//���X�e�B�b�N�������݃{�^��
	JOYPAD_RT,					//�E�X�e�B�b�N�������݃{�^��
	JOYPAD_BACK,				//�o�b�N�{�^��
	JOYPAD_START,				//�X�^�[�g�{�^��
	JOYPAD_HOME,				//�z�[���{�^��
	JOYPAD_UP,					//��
	JOYPAD_UP_LEFT,				//����
	JOYPAD_UP_RIGHT,			//�E��
	JOYPAD_DOWN,				//��
	JOYPAD_DOWN_LEFT,			//����
	JOYPAD_DOWN_RIGHT,			//�E��
	JOYPAD_LEFT,				//��
	JOYPAD_RIGHT,				//�E
	JOYPAD_MAX
};

//�L�[���(�W���C�p�b�h)
enum InputType
{
	INPUT_TYPE_KEYBOARD = 0,
	INPUT_TYPE_JOYPAD,
	INPUT_TYPE_MAX
};

#endif

