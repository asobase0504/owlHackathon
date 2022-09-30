//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "title.h"
#include "input.h"
#include "manager.h"
#include "Bg.h"
#include "player.h"
#include "fade.h"
#include "sound.h"
#include "ranking.h"
#include "2dpolygontemplate.h"
#include "tumbleweed.h"

//========================
// コンストラクター
//========================
CTitle::CTitle()
{
}
//========================
// デストラクト
//========================
CTitle::~CTitle()
{
}

//================
//初期化処理
//================
HRESULT CTitle::Init(void)
{
	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 EnemyPos = CManager::Pos;
	m_alpha = 1.2f;

	m_addX = 0;
	m_addY = 0;
	ModeSelect = false;
	NextMode = MODE::MODE_GAME;

	EnemyPos.z -= 30.0f;

	D3DXVECTOR3 Size(3.8f, 3.8f, 3.8f);
	D3DXVECTOR3 Rot(0.0f, 1.57f, 0.0f);

	// 背景の荒野
	Bg = CObject2d::Create();
	Bg->SetTexture(CTexture::TEXTURE_WILDERNESS);
	Bg->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));
	Bg->SetSize(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f, CManager::SCREEN_HEIGHT * 0.5f, 0.0f));

	// サボテン
	Saboten[0] = CObject2d::Create();
	Saboten[0]->SetTexture(CTexture::TEXTURE_SABOTEN);
	Saboten[0]->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f + 300.0f, CManager::SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f));
	Saboten[0]->SetSize(D3DXVECTOR3(20.0f, 60.0f, 0.0f));

	// サボテン
	Saboten[1] = CObject2d::Create();
	Saboten[1]->SetTexture(CTexture::TEXTURE_SABOTEN);
	Saboten[1]->SetPos(D3DXVECTOR3(CManager::SCREEN_WIDTH * 0.5f - 300.0f, CManager::SCREEN_HEIGHT * 0.5f + 150.0f, 0.0f));
	Saboten[1]->SetSize(D3DXVECTOR3(20.0f, 60.0f, 0.0f));
	
	////GonFoxのTITLE文字
	//m_Bg[1] = CBg::Create();
	//m_Bg[1]->SetTexture(CTexture::TEXTURE_GAME);
	//m_Bg[1]->SetSize(CManager::Pos*0.8f);
	//m_Bg[1]->SetPos(BGPos);
	//m_Bg[1]->SetBgType(CBg::STOP);
	//m_Bg[1]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
	
	//TITLE文字
	{
		m_list[0] = CObject2d::Create(1);
		m_list[0]->SetTexture(CTexture::TEXTURE_TITLE);
		m_list[0]->SetSize(CManager::Pos * 0.5f);
		D3DXVECTOR3 pos = CManager::Pos;
		pos.y *= 0.5f;
		m_list[0]->SetPos(pos);
		m_list[0]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
	//ゲームスタートの文字
	m_list[1] = CObject2d::Create(1);
	m_list[1]->SetTexture(CTexture::TEXTURE_FOXTITLE);
	m_list[1]->SetSize(CManager::Pos);
	m_list[1]->SetPos(CManager::Pos);
	m_list[1]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	//モード選択時の背景黒くするやつ
	fade = CObject2d::Create(2);
	fade->SetTexture(CTexture::TEXTURE_NONE);
	fade->SetSize(CManager::Pos);
	fade->SetPos(CManager::Pos);
	fade->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 120.0f;

	//ゲームの文字
	m_object2d[0] = CObject2d::Create(2);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TITLEGAME);
	m_object2d[0]->SetSize(CManager::Pos);
	m_object2d[0]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y - y, 0.0f));
	m_object2d[0]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));


	//チュートリアルの文字
	m_object2d[1] = CObject2d::Create(2);
	m_object2d[1]->SetTexture(CTexture::TEXTURE_TITLETUTORIAL);
	m_object2d[1]->SetSize(CManager::Pos);
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y, 0.0f));
	m_object2d[1]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//ランキングの文字
	m_object2d[2] = CObject2d::Create(2);
	m_object2d[2]->SetTexture(CTexture::TEXTURE_TITLERANKIN);
	m_object2d[2]->SetSize(CManager::Pos);
	m_object2d[2]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[2]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 120.0f;

	//おわりの文字
	m_object2d[3] = CObject2d::Create(2);
	m_object2d[3]->SetTexture(CTexture::TEXTURE_TITLEEND);
	m_object2d[3]->SetSize(CManager::Pos);
	m_object2d[3]->SetPos(D3DXVECTOR3(CManager::Pos.x, CManager::Pos.y + y, 0.0f));
	m_object2d[3]->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	m_tumbleweedPopCount = rand() % 70;

	CRanking::SetScore(0);

	return S_OK;
}

//================
//破棄
//================
void CTitle::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();

	CModelManager::ReleaseAll();
}

//==================
//更新処理
//==================
void CTitle::Update(void)
{
	m_tumbleweedPopCount--;
	if (m_tumbleweedPopCount <= 0)
	{
		m_tumbleweedPopCount = rand() % 150;
		CTumbleweed::Create();
	}

	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(KEY_DECISION))
	{
		CManager* maneger = CManager::GetInstance();
		//maneger->GetSound()->Play(CSound::LABEL_SE_ON);
		if (ModeSelect)
		{//一回押された	
			switch (NextMode)
			{
			case MODE::MODE_GAME:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_TUTORIAL:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_TUTORIAL);
				break;
			case MODE::MODE_RANKING:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_RANKING);
				break;
			case MODE::MODE_END:
				//ゲームの終了
				PostQuitMessage(0);
				break;
			default:
				break;
			}		
		}
		else
		{
			//画面黒くする
			fade->SetCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

			//文字を出し
			for (int i = 0; i < 4; i++)
			{
				m_object2d[i]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}

			//今使ってるやつを明るく
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			ModeSelect = true;
		}

	}
	if (ModeSelect)
	{
		if (CInputpInput->Trigger(KEY_UP))
		{
			//CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//モード選択
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode - 1);


			if (NextMode < MODE::MODE_GAME)
			{
				NextMode = MODE::MODE_END;
			}

	
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(KEY_DOWN))
		{
			//CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_NO);
			//モード選択
			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			NextMode = (MODE)(NextMode + 1);

			if (NextMode >= MODE::MODE_MAX)
			{
				NextMode = MODE::MODE_GAME;
			}

			m_object2d[NextMode]->SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(DIK_F1))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
	}
	if (CInputpInput->Trigger(DIK_F2))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
	}

#endif // DEBUG
}
//==================
//描画処理
//==================
void CTitle::Draw(void)
{

}