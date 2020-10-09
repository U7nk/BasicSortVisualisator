#include "Draw.cpp"
#include "Mass.h"
#include <iostream>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
//================================Global vars==============
unsigned int massSize = 100; // var for functions
int massToSort[100]; // array to sort. size need to be 100. 
const char mainMessage[] = "Выберите алгоритм сортировки"; // message on top of the main menu
int algIndex = 1;  // var for switch between algorithms
int status = 0; // var for switch between pages 
double elapsedTime; // var with timer counted time
const char qSortMessage[] = "quickSort"; // name of sorting algorithm for the main menu
const char BubbleSortMessage[] = "Bubble Sort"; // name of sorting algorithm for the main menu

//======================Timer=============================
/** Use to init the clock */
#define TIMER_INIT \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER t1,t2; \
    QueryPerformanceFrequency(&frequency);


/** Use to start the performance timer */
#define TIMER_START QueryPerformanceCounter(&t1);

/** Use to stop the performance timer and output the result to the standard stream. Less verbose than \c TIMER_STOP_VERBOSE */
#define TIMER_STOP \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart; \


//====================Buttons identificators===================================
#define IDB_Button1 		100
#define IDB_ButtonL 		101
#define IDB_ButtonR 		102
#define ID_AlgInfo          103
#define IDB_ButtonBack 		104
#define IDB_ButtonRandomize 105
#define IDB_ButtonStart 	106








// message prz
LONG WINAPI WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam){
	HINSTANCE hInst;
	static HWND hwndButton;
	static HWND hwndButtonL;
	static HWND hwndButtonR;
	static HWND hwndAlgInfo;
	static HWND hwndChooseAlgText;
	static HWND hwndButtonBack,hwndButtonRandomize,hwndButtonStart;
	
	PAINTSTRUCT ps;
 	RECT rect;
 	HDC hDC, hCmpDC;
 	HBITMAP hBmp;
 	LOGBRUSH br;
	HBRUSH brush;
	RECT rect1;
	rect1.bottom = 600;
	rect1.right = 1450;
	rect1.top = 0;
	rect1.left = 50;
	RECT time;
	time.bottom = 70;
	time.right = 100;
 	time.top = 0;
	time.left = 0;

	
	COLORREF colorText = RGB(46,35,40);
	COLORREF colorBr = RGB(255,255,255);
	switch(msg){
		case WM_CREATE:
			
			InvalidateRect(hWnd,NULL,false);
			
			hwndButton = CreateWindow( 
    			"BUTTON",  // Predefined class; Unicode assumed 
    			"Начать",      // Button text 
    			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    			520,        // x position 
    			100,       // y position 
    			70,        // Button width
    			30,        // Button height
    			hWnd,      // Parent window
    			(HMENU) IDB_Button1,       
    			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), 
    			NULL);      // Pointer not needed.
    		ShowWindow(hwndButton, SW_SHOWNORMAL);
	hwndButtonL = CreateWindow( 
    			"BUTTON",  // Predefined class; Unicode assumed 
    			"<<",      // Button text 
    			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
    			520,         // x position 
    			30,         // y position 
    			70,        // Button width
    			30,        // Button height
    			hWnd,     // Parent window
    			(HMENU) IDB_ButtonL,       
    			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), 
    			NULL);      // Pointer not needed.
			ShowWindow(hwndButtonL, SW_SHOWNORMAL);
	hwndButtonR = CreateWindow( 
    			"BUTTON",  // Predefined class; Unicode assumed 
    			">>",      // Button text 
    			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
    			900,         // x position 
    			30,         // y position 
    			70,        // Button width
    			30,        // Button height
    			hWnd,     // Parent window
    			(HMENU) IDB_ButtonR,       
    			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), 
    			NULL);      // Pointer not needed.
			ShowWindow(hwndButtonR, SW_SHOWNORMAL);
	
	hwndButtonBack = CreateWindow( 
    			"BUTTON",  // Predefined class; Unicode assumed 
    			"Назад",      // Button text 
    			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
    			100,         // x position 
    			500,         // y position 
    			70,        // Button width
    			30,        // Button height
    			hWnd,     // Parent window
    			(HMENU) IDB_ButtonBack,       
    			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), 
    			NULL);      // Pointer not needed.
    		ShowWindow(hwndButtonBack, SW_HIDE);
    hwndButtonRandomize = CreateWindow( 
    			"BUTTON",  // Predefined class; Unicode assumed 
    			"Рандомизировать массив",      // Button text 
    			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles 
    			100,         // x position 
    			535,         // y position 
    			250,        // Button width
    			30,        // Button height
    			hWnd,     // Parent window
    			(HMENU) IDB_ButtonRandomize,       
    			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), 
    			NULL);      // Pointer not needed.
    		ShowWindow(hwndButtonRandomize, SW_HIDE);
    hwndButtonStart = CreateWindow( 
    			"BUTTON",  // Predefined class; Unicode assumed 
    			"Начать",      // Button text 
    			WS_CHILD|WS_VISIBLE,  // Styles 
    			100,         // x position 
    			570,         // y position 
    			70,        // Button width
    			30,        // Button height
    			hWnd,     // Parent window
    			(HMENU) IDB_ButtonStart,       
    			(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), 
    			NULL);      // Pointer not needed.
			ShowWindow(hwndButtonStart, SW_HIDE);
			
			break;
		case WM_PAINT:
			
			GetClientRect(hWnd, &rect);
			br.lbStyle = BS_SOLID;
 			br.lbColor = colorBr;
 			brush = CreateBrushIndirect(&br);
 		
			switch (status){
				case 0:
					
					hDC = BeginPaint(hWnd, &ps);
 					hCmpDC = CreateCompatibleDC(hDC);

 					hBmp = CreateCompatibleBitmap(hDC, rect.right - rect.left,rect.bottom - rect.top);
 					SelectObject(hCmpDC, hBmp);
 					FillRect(hCmpDC, &rect, brush);
 					
					switch(algIndex){
						case 1:
							TextOut(hCmpDC,710,36,qSortMessage,9);
							break;
						case 2:
							TextOut(hCmpDC,710,36,BubbleSortMessage,11);
							break;
					}
					DrawText(hCmpDC,mainMessage,-1,&rect,DT_CENTER | DT_SINGLELINE  ); 
					SelectObject(hDC, hCmpDC);
					DeleteObject(brush);
					
					BitBlt(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top,hCmpDC, 0, 0, SRCCOPY);
					
					break;
				case 1:
					string TIMER_TIME = std::to_string(elapsedTime);
    				TIMER_TIME += " сек.";
					const char *CTIMER_TIME = TIMER_TIME.c_str();
    				
					hDC = BeginPaint(hWnd, &ps);
 					
					hCmpDC = CreateCompatibleDC(hDC);
 					hBmp = CreateCompatibleBitmap(hDC, rect.right - rect.left,rect.bottom - rect.top);
 					SelectObject(hCmpDC, hBmp);
 					FillRect(hCmpDC, &rect, brush);
 					
					DrawDiag(hCmpDC,massToSort,massSize);
					TextOut(hCmpDC,100,420,"Метод сортировки:",17);
					switch(algIndex){
						case 1:
							TextOut(hCmpDC,310,420,qSortMessage,9);
							break;
						case 2:
							TextOut(hCmpDC,300,420,BubbleSortMessage,11);
							break;
					}
					TextOut(hCmpDC,100,450,"Время затраченное на сортировку:",32);
					if (DRAW_COMPLETED){
						TextOut(hCmpDC,450,450,CTIMER_TIME,TIMER_TIME.size());
					}
					else{
						TextOut(hCmpDC,450,450,"Неизвестно",10);
					}
					
					SetStretchBltMode(hDC, COLORONCOLOR);
					BitBlt(hDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top,hCmpDC, 0, 0, SRCCOPY);
					SelectObject(hDC, hCmpDC);
					DeleteObject(brush);
					
					EndPaint(hWnd,&ps);
					
 					break;
			}
			
			DeleteObject(hCmpDC);
			DeleteDC(hCmpDC);
 			DeleteObject(hBmp);
 			ReleaseDC(hWnd,hDC);
			hCmpDC = NULL;
			EndPaint(hWnd,&ps);
			
 			return 0;
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
				break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
		{
			switch(wParam){
				case IDB_Button1:
					InvalidateRect(hWnd,NULL,true);
					
					
					status = 1;
					ShowWindow((HWND)lParam,SW_HIDE);
					ShowWindow(hwndButtonBack,SW_SHOWNORMAL);
					
					ShowWindow(hwndButtonRandomize, SW_SHOWNORMAL);
					ShowWindow(hwndButtonStart, SW_SHOWNORMAL);
					ShowWindow(hwndButtonL,SW_HIDE);
					ShowWindow(hwndButtonR,SW_HIDE);
					
					break;
				case IDB_ButtonL:
					InvalidateRect(hWnd,NULL,false);
					algIndex++;
					if (algIndex > 2){
						algIndex = 1;
					} 
					DRAW_COMPLETED = false;
					
					break;
				case IDB_ButtonR:
					InvalidateRect(hWnd,NULL,false);
					algIndex--;
					if (algIndex < 1){
						algIndex = 2;
					} 
					DRAW_COMPLETED = false;
					
					break;
				case IDB_ButtonBack:
					STOP = true;
					status = 0;
					ShowWindow(hwndButtonR, SW_SHOWNORMAL);
					ShowWindow(hwndButton,SW_SHOWNORMAL);
					ShowWindow(hwndButtonL,SW_SHOWNORMAL);
					ShowWindow((HWND)lParam,SW_HIDE);
					ShowWindow(hwndButtonStart, SW_HIDE);
					ShowWindow(hwndButtonRandomize, SW_HIDE);
					InvalidateRect(hWnd,NULL,false);
					break;		
				case IDB_ButtonRandomize:
					if (STOP)
					{
						STOP = false;
					}
					else
					{
						STOP = true;
					}
					std::random_shuffle(massToSort,massToSort + massSize);
					DRAW_COMPLETED = false;
					InvalidateRect(hWnd,&rect1,false);
					
					break;
				case IDB_ButtonStart:
					if (STOP)
					{
						STOP = false;
					}
					else
					{
						STOP = true;
					}
					DRAW_COMPLETED = false;
					switch (algIndex)
					{
						case 1: // qsort
							{
							TIMER_INIT
   							TIMER_START
   							massQSort(massToSort,100,hWnd);
   							TIMER_STOP
							}
							break;
						case 2: // bubble sort
							{
							TIMER_INIT
   							TIMER_START
   							massBubbleSort(massToSort,100,hWnd);
   							TIMER_STOP
							}
							break;
					}
					
				
					InvalidateRect(hWnd,&rect,false);
					
					break;	
			}
			break;
		}
		case WM_SIZE:
			GetClientRect(hWnd, &rect);
			SetWindowSize(rect.right - rect.left, rect.bottom - rect.top);
			break;
		case WM_ERASEBKGND:
			return 1;
			break;
		default:
			return DefWindowProc(hWnd,msg,wParam,lParam);
	
	}
	
	return 0;
}



int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	massIncInit(massToSort,massSize);
	
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	const char g_szClassName[] = "myWindowClass";
	
	wc.cbSize 			= sizeof(WNDCLASSEX);
	wc.style 			= 0;
	wc.lpfnWndProc 		= WndProc;
	wc.cbClsExtra 		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance 		= hInstance;
	wc.hIcon 			= LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor 			= LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground 	= HBRUSH(NULL_BRUSH);
	wc.lpszMenuName 	= NULL;
	wc.lpszClassName 	= g_szClassName;
	wc.hIconSm 			= LoadIcon(NULL,IDI_APPLICATION);
	
	if(!RegisterClassEx(&wc)){
		MessageBox(NULL,"Class not registered","Error",MB_ICONINFORMATION | MB_OK);
		return 0;
	}
	
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Put title here",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1500, 700,
		NULL, NULL, hInstance, NULL);
	
	
    
	if (hwnd == NULL){
		MessageBox(NULL,"Window Creation Failed","Error",MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	
	
    			
	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);
	
	
	
	while (GetMessage(&Msg,NULL, 0, 0) > 0){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		
	}
	
	return Msg.wParam;
	
}
