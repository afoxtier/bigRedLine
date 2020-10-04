// bigRedLine.cpp : Defines the entry point for the application.
//by Aidan Fox-Tierney based on vidual Studio's GUI template

#include "framework.h"
#include "CommCtrl.h"
#include "bigRedLine.h"
#include "day.h"
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//My fancy-shmancy schedule holding bits and some functions to help them interact
Day** days;
int numDays = 0;

bool addDay(HWND hWnd);
bool getDate(int& month, int& day, int& year, HWND hWnd);
bool sameDate(int& month, int& day, int& year);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    days = new Day * ();
    days[0] = new Day(10, 3, 2020);
    Task taskTest(std::string("HackUC"), std::string("Stay up all night scratching your head."), 0, 12, 24);
    days[0]->addTask(taskTest);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BIGREDLINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BIGREDLINE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIGREDLINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BIGREDLINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
        MessageBox(NULL, _T("Window failed to open!"), _T("Big Red Line Error"), NULL);
        return FALSE;
   }

   HWND addDayBtn = CreateWindow(L"BUTTON", L"Add Day",
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
       0, 0, 70,20, hWnd, (HMENU)IDC_DAYADD,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
   if (!addDayBtn)
   {
       MessageBox(NULL, _T("Button failed to open!"), _T("Big Red Line Error"), NULL);
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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDC_DAYADD:
                if (!addDay(hWnd))
                {
                    MessageBox(NULL, _T("Day creation failed!"), _T("Add Day Error"), NULL);
                    MessageBeep(MB_ICONINFORMATION);
                }
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
            // TODO: Add any drawing code that uses hdc here...
            WCHAR dayInfo[100];
            WCHAR taskInfo[200];

            days[0]->getTask(&taskInfo[0], 0);

            swprintf_s(dayInfo, 100, L"%d/%d/%d", 
                days[0]->getMonth(), days[0]->getDay(), days[0]->getYear());

            TextOut(hdc, 0, 30, dayInfo, _tcslen(dayInfo));

            TextOut(hdc, 0, 60, taskInfo, _tcslen(taskInfo));

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


//Message handler for calandar dialog box
bool CALLBACK Calendar(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        return  true;
        break;
    }
    return  true;
}


// Message handler for about box.
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


//Prompts user to add a day to the list and returns false if error
bool addDay(HWND hWnd)
{
    int tempMonth, tempDay, tempYear;
    
    if (!getDate(tempMonth, tempDay, tempYear, hWnd))
    {
        return false;
    }//if date invalid
    else if (sameDate(tempMonth, tempDay, tempYear))
    {
        return false;
    }//if day already made

    days[numDays] = new Day(tempMonth, tempDay, tempYear);
    numDays++;
} //addDay()


bool getDate(int& month, int& day, int& year, HWND hWnd)
{
    RECT calRect;
    HWND dialogWindow = NULL;
    HWND CalendarWindow = NULL;

    //Create calendar to pick date from
    //make dialog box first
    dialogWindow = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DATE_PICKER), hWnd, (DLGPROC)Calendar);
    if (!dialogWindow)
    {
        MessageBox(NULL, _T("Calendar's dialog box failed to be created!"), _T("Dialog Window Error"), NULL);
        return false;
    }

    //then make actual calendar
    CalendarWindow = CreateWindowEx(0, MONTHCAL_CLASS, L"", WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_DAYSTATE,
        0, 0, 0, 0, dialogWindow, (HMENU)IDC_MONTHCAL, hInst, NULL);
    if (!CalendarWindow)
    {
        MessageBox(NULL, _T("Calendar's calendar failed to be created!"), _T("Calendar Window Error"), NULL);
        return false;
    }

    //get min size and resize
    MonthCal_GetMinReqRect(CalendarWindow, &calRect);
    SetWindowPos(CalendarWindow, NULL, 0, 0, calRect.right, calRect.bottom, SWP_NOZORDER);

    ShowWindow(dialogWindow, SW_SHOW);

    return true;
} //getDate()


//Checks to see if there would be a duplicate day
bool sameDate(int& month, int& day, int& year)
{
    if (numDays > 0)
    {
        for (int i = 0; i < numDays; i++)
        {
            if (days[i]->getMonth() == month &&
                days[i]->getDay() == day &&
                days[i]->getYear() == year)
            {
                return true;
            } //if dates the same
        } //for all days
    } //if there are days
    
    return false;
} //sameDate()