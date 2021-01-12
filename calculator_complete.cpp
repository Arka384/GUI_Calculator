#include<windows.h>
#include<winuser.h>
#include<iostream>
using namespace std;

#define add 10
#define sub 11
#define mul 12
#define div 13
#define answer 14
#define AC 15
#define Clear 16
#define Exit 17


int windowHeight = 336, windowWidth = 600;
int windowX = 340, windowY = 120;
char res[20];

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

void AddMenu(HWND );
HMENU hMenu;//handeler for our menu
void AddControls(HWND );
HWND num1, num2, result;
void AppendMessege(char[] );
void BackSpace(void);
void GetResult(void);
int GetVal(char );
float GetResultInt(char [], char [], int );

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
	CreateWindowW(L"Window_Class", L"Calculator",
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
    char ch[20];
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
                case 1:
                    AppendMessege("1");
                    break;
                case 2:
                    AppendMessege("2");
                    break;
                case 3:
                    AppendMessege("3");
                    break;
                case 4:
                    AppendMessege("4");
                    break;
                case 5:
                    AppendMessege("5");
                    break;
                case 6:
                    AppendMessege("6");
                    break;
                case 7:
                    AppendMessege("7");
                    break;
                case 8:
                    AppendMessege("8");
                    break;
                case 9:
                    AppendMessege("9");
                    break;
                case 0:
                    AppendMessege("0");
                    break;
                case add:
                    AppendMessege("+");
                    break;
                case sub:
                    AppendMessege("-");
                    break;
                case mul:
                    AppendMessege("*");
                    break;
                case div:
                    AppendMessege("/");
                    break;
                case answer:
                    GetResult();
                    break;
                case AC:
                    SetWindowText(result, "");
                    break;
                case Clear:
                    BackSpace();
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

void AppendMessege(char n[])
{
    char c[20];
    GetWindowText(result, c, 20);
    strcat(c, n);
    SetWindowText(result, c);
}
void BackSpace()
{
    char s[20];
    GetWindowText(result, s, 20);
    s[strlen(s)-1] = '\0';
    SetWindowText(result, s);
}

void GetResult()
{
    char str[20], res[50], a[20], b[20], op1, op2;
    int l = strlen(str);
    int j=0,i=0,m=0,n=0;
    float FloatRes=0.0;

    GetWindowText(result, str, 20);

    while(GetVal(str[i]) == 1 || GetVal(str[i]) == 6)
        a[m++] = str[i++];
    op1 = str[i++];
    a[m] = '\0';

    while(str[i] != '\0')
    {
        n=0;
        while(GetVal(str[i]) == 1 || GetVal(str[i]) == 6)
            b[n++] = str[i++];
        if(str[i] != '\0')
            op2 = str[i++];
        b[n] = '\0';

        FloatRes = GetResultInt(a,b,GetVal(op1));
        sprintf(res, "%f", FloatRes);

        strcpy(a, res);
        op1 = op2;

    }
    SetWindowText(result, a);
}

float GetResultInt(char a[], char b[], int o)
{
    float x,y,z=0.0;
    x = atof(a);
    y = atof(b);
    switch(o)
    {
        case 2:
            z = x+y;
            break;
        case 3:
            z = x*y;
            break;
        case 4:
            z = x-y;
            break;
        case 5:
            z = x/y;
            break;
        default:
            break;
    }
    return z;
}

int GetVal(char c)
{
    if(c >= 48 && c <= 57)
        return 1;
	else if(c==43)//add
		return 2;
	else if(c==42)//mul
		return 3;
	else if(c==45)//sub
		return 4;
	else
		return 5;//div
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
    result = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_RIGHT | WS_BORDER, 
        22, 10, 280, 170, hwnd, NULL, NULL, NULL);

    //numbers
    CreateWindowW(L"button", L"1", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        22, 190, 60, 60, hwnd, (HMENU)1, NULL, NULL);
    CreateWindowW(L"button", L"4", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        22, 260, 60, 60, hwnd, (HMENU)4, NULL, NULL);
    CreateWindowW(L"button", L"7", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        22, 330, 60, 60, hwnd, (HMENU)7, NULL, NULL);

    CreateWindowW(L"button", L"2", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        92, 190, 60, 60, hwnd, (HMENU)2, NULL, NULL);
    CreateWindowW(L"button", L"5", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        92, 260, 60, 60, hwnd, (HMENU)5, NULL, NULL);
    CreateWindowW(L"button", L"8", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        92, 330, 60, 60, hwnd, (HMENU)8, NULL, NULL);

    CreateWindowW(L"button", L"3", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        162, 190, 60, 60, hwnd, (HMENU)3, NULL, NULL);
    CreateWindowW(L"button", L"6", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        162, 260, 60, 60, hwnd, (HMENU)6, NULL, NULL);
    CreateWindowW(L"button", L"9", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        162, 330, 60, 60, hwnd, (HMENU)9, NULL, NULL);

    CreateWindowW(L"button", L"0", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        92, 400, 60, 60, hwnd, (HMENU)0, NULL, NULL);

    //operators
    CreateWindowW(L"button", L"+", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        242, 190, 60, 60, hwnd, (HMENU)add, NULL, NULL);
    CreateWindowW(L"button", L"-", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        242, 260, 60, 60, hwnd, (HMENU)sub, NULL, NULL);
    CreateWindowW(L"button", L"*", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        242, 330, 60, 60, hwnd, (HMENU)mul, NULL, NULL);
    CreateWindowW(L"button", L"/", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        242, 400, 60, 60, hwnd, (HMENU)div, NULL, NULL);

    //Other button
    CreateWindowW(L"button", L"=", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        22, 470, 280, 60, hwnd, (HMENU)answer, NULL, NULL);
    CreateWindowW(L"button", L"AC", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        162, 400, 60, 60, hwnd, (HMENU)AC, NULL, NULL);
    CreateWindowW(L"button", L"<-", WS_VISIBLE | WS_CHILD | ES_CENTER, 
        22, 400, 60, 60, hwnd, (HMENU)Clear, NULL, NULL);
}