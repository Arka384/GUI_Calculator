#include<windows.h>
#include<winuser.h>
#include<iostream>
using namespace std;

#define Exit 1
#define add 2
#define sub 3
#define mul 4
#define div 5
#define answer 6

int windowHeight = 800, windowWidth = 600;
int windowX = 340, windowY = 120;
char res[20];

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

void AddMenu(HWND );
HMENU hMenu;//handeler for our menu
void AddControls(HWND );
HWND num1, num2, result;

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, LPSTR cmdLine, int ncmdshow) {
	// Register the window class
	WNDCLASSW wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = L"Window_Class";
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClassW(&wc);

	// Create the window
	CreateWindowW(L"Window_Class", L"name",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,			// Window style
		windowX, windowY,				// Window initial position
		windowHeight, windowWidth,						// Window size
		nullptr, nullptr, nullptr, nullptr);
	
	// Window loop
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    int i;
    char a[10],b[10];
    float n1,n2,n3;
	switch (msg) 
    {
        case WM_CREATE: //this is called when the window is created
            AddMenu(hwnd);  //passed window handeler as the window which have the window
            AddControls(hwnd);
            break;
        
        //for different menu items
        case WM_COMMAND:
            switch (wparam)
            {
                case Exit:
                    DestroyWindow(hwnd);
                    break;
                case add:
                    GetWindowText(num1, a, 10);
                    GetWindowText(num2, b, 10);
                    n1 = atof(a);
                    n2 = atof(b);
                    n3 = n1+n2;
                    itoa(n3, res, 10);
                    break;
                case sub:
                    GetWindowText(num1, a, 10);
                    GetWindowText(num2, b, 10);
                    n1 = atof(a);
                    n2 = atof(b);
                    n3 = n1-n2;
                    itoa(n3, res, 10);
                    break;
                case mul:
                    GetWindowText(num1, a, 10);
                    GetWindowText(num2, b, 10);
                    n1 = atof(a);
                    n2 = atof(b);
                    n3 = n1*n2;
                    itoa(n3, res, 10);
                    break;
                case div:
                    GetWindowText(num1, a, 10);
                    GetWindowText(num2, b, 10);
                    n1 = atof(a);
                    n2 = atof(b);
                    n3 = n1/n2;
                    itoa(n3, res, 10);
                    break;
                case answer:
                    SetWindowText(result, res);
                    break;
                default:
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        
        default:
            return DefWindowProcW(hwnd, msg, wparam, lparam);
	}
}

void AddMenu(HWND hwnd)
{
    hMenu = CreateMenu();
    HMENU hSubmenu = CreateMenu();
    AppendMenu(hSubmenu, MF_STRING, Exit, "Exit");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubmenu, "File");
    SetMenu(hwnd, hMenu);
}

void AddControls(HWND hwnd)
{
    num1 = CreateWindowW(L"Edit", L"1st Number", WS_VISIBLE | WS_CHILD | ES_RIGHT | WS_BORDER, 
        220, 30, 100, 30, hwnd, NULL, NULL, NULL);
    num2 = CreateWindowW(L"Edit", L"2nd Number", WS_VISIBLE | WS_CHILD | ES_RIGHT | WS_BORDER, 
        420, 30, 100, 30, hwnd, NULL, NULL, NULL);
    result = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_RIGHT | WS_BORDER, 
        220, 100, 300, 50, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"+", WS_VISIBLE | WS_CHILD, 220, 170, 50, 50, hwnd, (HMENU)add, NULL, NULL);
    CreateWindowW(L"Button", L"-", WS_VISIBLE | WS_CHILD, 320, 170, 50, 50, hwnd, (HMENU)sub, NULL, NULL);
    CreateWindowW(L"Button", L"*", WS_VISIBLE | WS_CHILD, 220, 240, 50, 50, hwnd, (HMENU)mul, NULL, NULL);
    CreateWindowW(L"Button", L"/", WS_VISIBLE | WS_CHILD, 320, 240, 50, 50, hwnd, (HMENU)div, NULL, NULL);

    CreateWindowW(L"Button", L"=", WS_VISIBLE | WS_CHILD, 420, 170, 100, 120, hwnd, (HMENU)answer, NULL, NULL);
}