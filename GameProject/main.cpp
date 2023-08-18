// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GameProject.h"
#include "yhApplication.h"
#include "yhSceneManager.h"

//
#include "yhTexture.h"
#include "yhResources.h"
#include "yhInput.h"
#include "yhTile.h"
#include "yhPlayerTemplate.h"
#include "CommonInclude.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
yh::Application application;

ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartupInput gdiplusStartupInput;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndToolProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //Gdiplus::GdiplusStartup
    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, szWindowClass, WndProc);
    MyRegisterClass(hInstance, L"Tool", WndToolProc);


    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEPROJECT));

    MSG msg;

    // GetMessage : 프로세스에 발생한 메시지를 메세지큐에서 꺼내옴
    //              (msg.message == WM_QUIT) return false;
    //              WM_QUIT 이외의 메세지가 발생 한 경우는 return true; 

    // PeekMessage : 프로세스에 발생한 메시지를 메세지큐에서 꺼내옴
    //               PM_REMOVE -> 발생한 메세지를 가져올 때 메세지큐에서 제거 (GetMessage 랑 동일하게 하기 위해서...)
    //               메세지큐에 메세지 유/무 에 상관없이 함수가 리턴됨
    //               리턴값이 true 인 경우 메세지가 있었다. 리턴값이 false 인 경우 메세지가 큐에 없었다.

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임 로직 돌려줘~
            // (게임 실행)
            application.Run();
        }
    }

    if (msg.message == WM_QUIT)
    {
        //
    }

    yh::SceneManager::Release();
    yh::Resources::Release();

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_GAMEPROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);

    HWND hWndTool = CreateWindowW(L"Tool", szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, 384, 400, nullptr, nullptr, hInstance, nullptr);

    // Gdiplus 초기화

    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    application.Initialize(hWnd);

    //status(플레이어 정보) 파일 초기화
    std::ofstream ofs("..\\Resources\\SaveData\\status.txt", std::ios::out | std::ios::trunc);
    if (ofs.fail())
    {
        std::cout << "Error!" << std::endl;
    }
    ofs << 0;
    ofs << "\n";
    ofs << 0;
    ofs << "\n";
    ofs << 0;
    ofs << "\n";
    ofs << 3;
    ofs << "\n";
    ofs << 0;
    ofs << "\n";

    ofs.close();

    //플레이어 위치 정보 초기화
    std::ofstream ofs2("..\\Resources\\SaveData\\PlayerPosition.txt", std::ios::out | std::ios::trunc);
    if (ofs2.fail())
    {
        std::cout << "Error!" << std::endl;
    }
    ofs2 << 0.0f;
    ofs2 << "\n";
    ofs2 << 0.0f;
    ofs2 << "\n";
    ofs2.close();


    //플레이어 방향 정보 초기화

    std::ofstream ofs3("..\\Resources\\SaveData\\PlayerDirection.txt", std::ios::out | std::ios::trunc);
    if (ofs3.fail())
    {
        std::cout << "Error!" << std::endl;
    }
    ofs3 << (int)yh::Directions::Backward;
    ofs3.close();


    if (!hWnd)
    {
        return FALSE;
    }

    //main
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    /// tool
    RECT rect = { 0, 0, 384, 400 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(hWndTool
        , nullptr, 1280, 720
        , rect.right - rect.left
        , rect.bottom - rect.top
        , 0);
    ShowWindow(hWndTool, nCmdShow);
    UpdateWindow(hWndTool);

    

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);


        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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


LRESULT CALLBACK WndToolProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
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
    case WM_LBUTTONDOWN:
    {
        POINT mousePos = {};
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);

        int idxX = mousePos.x / (TILE_WIDTH);
        int idxY = mousePos.y / (TILE_HEIGHT);

        yh::Tile::mSelectedX = idxX;
        yh::Tile::mSelectedY = idxY;
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //Rectangle(hdc, 0, 0, 100, 100);
        //여기서 이미지 를 그려준다.

        yh::Texture* springFloor
            = yh::Resources::Find<yh::Texture>(L"SprintFloorTile");

        TransparentBlt(hdc
            , 0, 0, springFloor->GetWidth(), springFloor->GetHeight()
            , springFloor->GetHdc()
            , 0, 0, springFloor->GetWidth(), springFloor->GetHeight()
            , RGB(255, 0, 255));

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
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
