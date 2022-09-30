#include "time_text.h"
#include "manager.h"

CTImeText::CTImeText()
{
}

CTImeText::~CTImeText()
{
}

HRESULT CTImeText::Init()
{
	// �t�H���g�̃��[�h
	AddFontResourceEx("data/font/FZ�S���^����.otf", FR_PRIVATE, &m_design);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���ڂ̃t�H���g�̐���
	D3DXCreateFont(device, 28, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Harenosora"), &m_font);

	return E_NOTIMPL;
}

void CTImeText::Uninit()
{
	RemoveFontResourceEx(TEXT("data/font/Harenosora.otf"), FR_PRIVATE, &m_design);

	if (m_font != nullptr)
	{
		m_font->Release();
		m_font = nullptr;
	}
}

void CTImeText::Update()
{
}

void CTImeText::Draw()
{
	TCHAR str[256];

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 device = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int i = 0; i < m_text.size(); i++)
	{
		RECT rect = { (int)m_pos[i].x, (int)m_pos[i].y, SCREEN_WIDTH, SCREEN_HEIGHT };
		sprintf(str, ("%1.4f"), m_text[i]);

		m_font->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	}
}

int CTImeText::SetText(float intime, D3DXVECTOR3 pos)
{
	m_text.push_back(intime);
	m_pos.push_back(pos);

	return m_text.size() - 1;
}
