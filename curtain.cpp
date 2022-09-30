//============================
//
// ２Dpolygon設定
// Author:Yuda Kaito
//
//============================

#include "curtain.h"
#include "utility.h"
#include "manager.h"

#include "blackin.h"
#include "blackout.h"

//------------------------------------
// コンストラクタ
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
// デストラクタ
//------------------------------------
CCurtain::~CCurtain()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CCurtain::Init()
{

	return S_OK;
}

//------------------------------------
// 終了
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
// 更新
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
// 描画
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
