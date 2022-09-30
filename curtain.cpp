//============================
//
// �QDpolygon�ݒ�
// Author:Yuda Kaito
//
//============================

#include "curtain.h"
#include "utility.h"
#include "manager.h"

#include "blackin.h"
#include "blackout.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CCurtain::CCurtain()
{
	for (int i = 0; i < 2; i++)
	{
		m_blackIn[i] = nullptr;
		m_blackOut[i] = nullptr;
	}
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CCurtain::~CCurtain()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CCurtain::Init()
{

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CCurtain::Uninit()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_blackIn[i] != nullptr)
		{
			m_blackIn[i]->Uninit();
			m_blackIn[i] = nullptr;
		}
		if (m_blackOut[i] != nullptr)
		{
			m_blackOut[i]->Uninit();
			m_blackOut[i] = nullptr;
		}
	}
}

//------------------------------------
// �X�V
//------------------------------------
void CCurtain::Update()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_blackIn[i] != nullptr)
		{
			m_blackIn[i]->Update();
		}
		if (m_blackOut[i] != nullptr)
		{
			m_blackOut[i]->Update();
		}
	}
}

//------------------------------------
// �`��
//------------------------------------
void CCurtain::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		if (m_blackIn[i] != nullptr)
		{
			m_blackIn[i]->Update();
		}
		if (m_blackOut[i] != nullptr)
		{
			m_blackOut[i]->Update();
		}
	}
}

void CCurtain::SetOut()
{
	for (int i = 0; i < 2;i++)
	{
		if (m_blackIn[i] != nullptr)
		{
			m_blackIn[i]->Uninit();
			m_blackIn[i] = nullptr;
		}

	}
	if (m_blackOut[0] == nullptr)
	{
		m_blackOut[0] = CBlackOut::Create(true);
	}
	if (m_blackOut[1] == nullptr)
	{
		m_blackOut[1] = CBlackOut::Create(false);
	}
}

//------------------------------------
// create
//------------------------------------
CCurtain *CCurtain::Create()
{
	CCurtain * pObject = new CCurtain;

	if (pObject->m_blackIn[0] == nullptr)
	{
		pObject->m_blackIn[0] = CBlackIn::Create(true);
	}

	if (pObject->m_blackIn[1] == nullptr)
	{
		pObject->m_blackIn[1] = CBlackIn::Create(false);
	}

	return pObject;
}
