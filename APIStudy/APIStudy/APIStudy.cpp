// APIStudy.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "APIStudy.h"

#define MAX_LOADSTRING 100


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);  //About <- 왠진모르지만 필요업승

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APISTUDY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APISTUDY));

    MSG msg;
	//DWORD <- unsigned long
    // 기본 메시지 루프입니다.
	//GetMessage 의경우 게임을 만들때 적합하지 않다..  <-Message가 들어올때까지 Block되어있음(Message가들어올때까지 프로그램 정지)
	//PeekMessage로 사용  <- Message가있으면 true반환  없으면 false 반환
	while (WM_QUIT!=msg.message) //<-종료메세지
	{

		//PM_REMOVE: Message Queue에서 먼저 들어온 Message를 제거함
		//PM_NOREMOVE: Message Queue에서 Message를 제거하지 않고 그대로둠
		while (PeekMessage(&msg, nullptr, 0, 0,PM_NOREMOVE)) 
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

	}

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APISTUDY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_APISTUDY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//CallBack 함수: 사용자가 아니라 시스템이 호출하는 함수.

	// 함수 호출 규약
	// 인자 전달 순서는 어떻게 하며, 함수 종료될 때 스택 정리를 누가 할 것인가?
	// __cdecl:		인자 전달 순서 오른쪽 -> 왼쪽 진행. 호출자가 stack 정리.
	// __stdcall:	인자 전달 순서 오른쪽 -> 왼쪽 진행. 피호출자가 stack 정리.
	// __fastcall:	인자 전달 순서 오른쪽 -> 왼쪽 진행. 피호출자가 stack 정리.
	// __thiscall:	인자 전달 순서 오른쪽 -> 왼쪽 진행. 피호출자가 stack 정리.

	switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: //창을 그릴때마다 호출 예: 최소화햇다가 띄울때, window크기를 바꿀때 등... 
        {
            PAINTSTRUCT ps;
			// DC(Device Context): 그리기에 필요한 정보들을 보관하는 메모리(버퍼).
			// HDC: DC의 핸들.
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

			// MoveToEx: 그리기 시작점(커서 포인트, CP)을 옮기는 함수.
			// 마지막 인자에는 이동하기 전의 커서 포인트 위치가 기록됨.			
			//LineTo(hdc, 200, 100);
			//LineTo(hdc, 100, 200);
			//LineTo(hdc, 100, 100);
			//LineTo(hdc, 200, 200);
			//LineTo(hdc, 50, 100);
			Rectangle(hdc, 100, 100, 400, 400); // 사각형 그리기 함수
			Rectangle(hdc, 450, 100, 750, 400); // 사각형 그리기 함수
			Rectangle(hdc, 800, 100, 1100, 400); // 사각형 그리기 함수
			Rectangle(hdc, 100, 100, 400, 400); // 사각형 그리기 함수
			MoveToEx(hdc, 135, 125, nullptr);
			LineTo(hdc, 270, 125);
			LineTo(hdc, 135, 270);
			MoveToEx(hdc, 315, 110, nullptr);
			LineTo(hdc, 315, 285);
			Rectangle(hdc, 145, 300, 315, 375); // 사각형 그리기 함수

			MoveToEx(hdc, 485, 125, nullptr);
			LineTo(hdc, 715, 125);
			LineTo(hdc, 485, 275);
			MoveToEx(hdc, 600, 200, nullptr);
			LineTo(hdc, 715, 270);
			MoveToEx(hdc, 485, 300, nullptr);
			LineTo(hdc, 715, 300);
			MoveToEx(hdc, 600, 300, nullptr);
			LineTo(hdc, 600, 350);
			MoveToEx(hdc, 485, 325, nullptr);
			LineTo(hdc, 485, 385);
			LineTo(hdc, 715, 385);

			Ellipse(hdc, 835, 125, 950, 250);	  // 원 그리기 함수
			MoveToEx(hdc, 950, 175, nullptr);
			LineTo(hdc, 1035, 175);
			MoveToEx(hdc, 950, 200, nullptr);
			LineTo(hdc, 1035, 200);
			MoveToEx(hdc, 1035, 125, nullptr);
			LineTo(hdc, 1035, 275);

			//LineTo(hdc,)

			Ellipse(hdc, 890, 265, 1005,390 );	  // 원 그리기 함수


			
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
