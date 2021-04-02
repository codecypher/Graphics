// HelloGDI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "HelloGDI.h"

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int WORLD_SIZE = 1000;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int POINT_SIZE = 10;
int MAX_NAME_LEN = 60;

RECT SQUARE = { 0, 0, 100, 100 };

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

string& leftTrim(string& str, string& chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

string& rightTrim(string& str, string& chars)
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string& trimString(string& str, string& chars)
{
    return leftTrim(rightTrim(str, chars), chars);
}

vector<int> split(const string& text, char delimiter) {
    string tmp;
    vector<int> stk;
    stringstream ss(text);
    while (getline(ss, tmp, delimiter)) {
        int n = stoi(tmp);
        stk.push_back(n);
    }
    return stk;
}

string to_string(vector<int> vec) {
    ostringstream vts;

    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<int>(vts, ", "));

        // Now add the last element with no delimiter
        vts << vec.back();
    }
    return vts.str();
}

int GetTitleBarHeight(HWND hwnd) {
    RECT wrect;
    GetWindowRect(hwnd, &wrect);
    RECT crect;
    GetClientRect(hwnd, &crect);
    POINT lefttop = { crect.left, crect.top }; // Practicaly both are 0
    ClientToScreen(hwnd, &lefttop);
    POINT rightbottom = { crect.right, crect.bottom };
    ClientToScreen(hwnd, &rightbottom);

    int left_border = lefttop.x - wrect.left;               // Windows 10: includes transparent part
    int right_border = wrect.right - rightbottom.x;         // As above
    int bottom_border = wrect.bottom - rightbottom.y;       // As above
    int top_border_with_title_bar = lefttop.y - wrect.top;  // There is no transparent part

    return top_border_with_title_bar;
}

VOID OnPaint(HDC hDC, HWND hWnd)
{
    Graphics graphics(hDC);
    Pen      pen(Color(255, 0, 0, 255));
    string   chars_to_trim = ".,/ ";
    string   sOutput = "";

    // Translate coordinates from World to Screen
    double x_ratio = (double(SCREEN_WIDTH) - 1.0) / (2.0 * WORLD_SIZE);   // 639 / 2000 = 0.3195
    double y_ratio = (double(SCREEN_HEIGHT) - 1.0) / (2.0 * WORLD_SIZE);  // 479 / 2000 = 0.2395

    //graphics.DrawLine(&pen, 0, 0, 200, 100);

    // Read from the text file
    //ifstream iFile("vector_list.txt");

    // Read vector file file line by line
    //string sLine;           // string to output the text file
    //while (getline(iFile, sLine)) {
    //    // Output the text from the file
    //    // cout << "HelloGDI: " << sText;

    //    trimString(sLine, chars_to_trim);

    //    std::ostringstream oss;
    //    vector<int> vList = split(sLine, ',');

    //    sOutput = to_string(vList) + "\n";
    //    // OutputDebugStringA(sOutput.c_str());

    //    // Translate coordinate from World to Screen
    //    double x_screen = (vList[0] + WORLD_SIZE) * x_ratio;
    //    double y_screen = (vList[1] + WORLD_SIZE) * y_ratio;
    //    sOutput = to_string(x_screen) + " " + to_string(y_screen) + "\n";
    //    OutputDebugStringA(sOutput.c_str());

    //    // Draw point on screen
    //    SolidBrush solidBrush(Color(255, 255, 0, 0));
    //    Status stat = graphics.FillEllipse(&solidBrush, x_screen, y_screen, POINT_SIZE, POINT_SIZE);
    //}

    // Close the file
    //iFile.close();

    RECT screen = { 
        (SQUARE.left) * x_ratio, 
        (SQUARE.top) * y_ratio,
        (SQUARE.right) * x_ratio,
        (SQUARE.bottom) * y_ratio
    };

    sOutput = to_string(SQUARE.left) + ", "
        + to_string(SQUARE.right) + ", "
        + to_string(SQUARE.right) + ", "
        + to_string(SQUARE.bottom) + "\n";
    OutputDebugStringA(sOutput.c_str());

    sOutput = to_string(screen.left) + ", " 
        + to_string(screen.right) + ", "
        + to_string(screen.right) + ", " 
        + to_string(screen.bottom) + "\n";
    OutputDebugStringA(sOutput.c_str());

    // Draw point on screen
    Pen redPren(Color(255, 255, 0, 0), 2);
    int nWidth  = screen.right - screen.left;
    int nHeight = screen.bottom - screen.top;
    Status stat = graphics.DrawRectangle(&redPren, screen.left, screen.top, nWidth, nHeight);

    // Resize window
    //RECT rc;
    //int nHeight = GetTitleBarHeight(hWnd);
    ////sOutput = "nHeight: " + to_string(nHeight);
    //GetClientRect(hWnd, &rc);
    //MapWindowPoints(hWnd, GetParent(hWnd), (LPPOINT)&rc, 2);
    //OutputDebugStringA(sOutput.c_str());
    //MoveWindow(hWnd, rc.left, rc.top, SCREEN_WIDTH, SCREEN_HEIGHT + nHeight, true);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HELLOGDI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HELLOGDI));
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    GdiplusShutdown(gdiplusToken);

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HELLOGDI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HELLOGDI);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


// FUNCTION: InitInstance(HINSTANCE, int)
//
// PURPOSE: Saves instance handle and creates main window
//
// COMMENTS:
// In this function, we save the instance handle in a global variable and
// create and display the main program window.
//
// Drawing a Line
// https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in global variable

   HWND hWnd = CreateWindowW(
       szWindowClass,           // window class name
       szTitle,                 // window caption
       WS_OVERLAPPEDWINDOW,     // window style
       CW_USEDEFAULT,           // initial x position
       0,                       // initial y position
       SCREEN_WIDTH,            // initial x size
       SCREEN_HEIGHT,           // initial y size
       nullptr,                 // parent window handle
       nullptr,                 // window menu handle
       hInstance,               // program instance handle
       nullptr);                // creation parameters

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            OnPaint(hdc, hWnd);
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

