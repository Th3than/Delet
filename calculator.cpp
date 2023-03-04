#include <windows.h>
#include <stdio.h>

HWND box1,box2,btp,btm,btmu,btd;
char num1[50];
char num2[50];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
		CreateWindow("STATIC","  Please input two numbers", WS_VISIBLE | WS_CHILD, 25, 20, 200, 20, hwnd, NULL, NULL, NULL);

		box1 = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE, 50, 50, 150, 25, hwnd, NULL, NULL, NULL);
		box2 = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE, 50, 80, 150, 25, hwnd, NULL, NULL, NULL);

		btp = CreateWindow("BUTTON","+",WS_BORDER|WS_CHILD|WS_VISIBLE, 50, 115, 30, 30, hwnd, (HMENU) 1, NULL, NULL);
		btm = CreateWindow("BUTTON","-",WS_BORDER|WS_CHILD|WS_VISIBLE, 90, 115, 30, 30, hwnd, (HMENU) 2, NULL, NULL);
		btmu = CreateWindow("BUTTON","*",WS_BORDER|WS_CHILD|WS_VISIBLE, 130, 115, 30, 30, hwnd, (HMENU) 3, NULL, NULL);
		btd = CreateWindow("BUTTON","/",WS_BORDER|WS_CHILD|WS_VISIBLE, 170, 115, 30, 30, hwnd, (HMENU) 4, NULL, NULL);
		
		break;
		/* Upon destruction, tell the main thread to stop */
		case WM_COMMAND: {
			int temp=0;
			int temp2=0;
			temp = GetWindowText(box1, &num1[0],50);
			temp2 = GetWindowText(box2, &num2[0],50);
			double result;
			char numto[100];

			switch (LOWORD(wParam))
			{
			case 1:
				result = atof(num1) + atof(num2);
				sprintf(numto,"%f",result);
				::MessageBox(hwnd,numto,"Result",MB_OK);
				break;
			case 2:
				result = atof(num1) - atof(num2);
				sprintf(numto,"%f",result);
				::MessageBox(hwnd,numto,"Result",MB_OK);
				break;
			case 3:
				result = atof(num1) * atof(num2);
				sprintf(numto,"%f",result);
				::MessageBox(hwnd,numto,"Result",MB_OK);
				break;
			case 4:
				result = atof(num1) / atof(num2);
				sprintf(numto,"%f",result);
				::MessageBox(hwnd,numto,"Result",MB_OK);
				break;
			}
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(173, 216, 230));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPED|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}