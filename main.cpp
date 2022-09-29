//=============================================================================
//
// ���C��
// Author : �l�c����
//
//=============================================================================

#include "renderer.h"
#include "main.h"
#include "object.h"
#include "object2d.h"
#include "resource1.h"
#include "input.h"
#include "manager.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef _DEBUG
// FPS�J�E���^
int g_nCountFPS;
#endif // _DEBUG

//CRenderer *cRenderer = nullptr;
//CInput *p_Input;

CManager* pManeager;

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2DC)),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCE(IDR_MENU1),
		CLASS_NAME,
		LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL))
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	pManeager = CManager::GetInstance();

	if (FAILED(pManeager->Init(hWnd, TRUE, hInstance)))	//��ʃT�C�Y
	{//���������������s�����ꍇ
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();
#ifdef _DEBUG
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = dwExecLastTime;
#endif // _DEBUG

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// ���b�Z�[�W���[�v
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
				// FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}
#endif // _DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ // 1/60�b�o��
				// ���݂̎��Ԃ�ۑ�
				dwExecLastTime = dwCurrentTime;

				pManeager->Update();

				pManeager->Draw();

#ifdef _DEBUG
				dwFrameCount++;
#endif // _DEBUG
			}
		}
	}

	if (pManeager != nullptr)
	{// �I������

		pManeager->Uninit();
		delete pManeager;
		pManeager = nullptr;
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDA_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_40004:
			MessageBox(hWnd, "2022/9/25�}�X�^�[��", "�o�[�W����1.00", MB_OK);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: // [ESC]�L�[�������ꂽ
			// �E�B���h�E��j��
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef _DEBUG

//=============================================================================
// ����
//=============================================================================
int Gettime(void)
{
	return g_nCountFPS;
}

#endif // _DEBUG
