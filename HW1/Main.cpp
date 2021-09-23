//*****************************************************************************
//
// Main.cpp : Defines the entry point for the application.
// Creates a white RGB image with a black line and displays it.
// Two images are displayed on the screen.
// Left Pane: Input Image, Right Pane: Modified Image
//
// Author - Parag Havaldar
// Code used by students as a starter code to display and modify images
//
//*****************************************************************************


// Include class files
#include "Image.h"
#include <iostream>
#include <vector>
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
MyImage			inImage;						// image objects
HINSTANCE		hInst;							// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

std::vector<std::string> param;
// Main entry point for a windows application
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	// Create a separate console window to display output to stdout
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	// The rest of command line argument is truncated.
	// If you want to use it, please modify the code.
	if (lpCmdLine[0] == 0) {
		wprintf(L"No command line arguement.");
		return -1;
	}
	int cnt = 0;
	int last = 0;
	int length = _tcsclen(lpCmdLine);
	std::string lpCmdLineS = lpCmdLine;
	for (int cnt = 0; cnt <= length; cnt++) {

		if (lpCmdLineS[cnt] == ' ' || cnt == length) {
			param.push_back(lpCmdLineS.substr(last, cnt - last));
			last = cnt + 1;
		}
	}
	//lpCmdLine[cnt] = 0;
	int missFlag = 0;
	if (param.size() < 4) {
		printf("Missing %d parameter", 4 - param.size());
		missFlag = 1;
	}
	else {
		printf("The first parameter was: %s \n", (LPSTR)(LPCWSTR)param[0].c_str());
		printf("The second parameter was: %s \n", (LPSTR)(LPCWSTR)param[1].c_str());
		printf("The third parameter was: %s \n", (LPSTR)(LPCWSTR)param[2].c_str());
		printf("The forth parameter was: %s \n", (LPSTR)(LPCWSTR)param[3].c_str());
	}
	lpCmdLine = (LPSTR)(LPCWSTR)param[0].c_str();

	// Set up the images
	int w = 1920;
	int h = 1080;
	inImage.setWidth(w);
	inImage.setHeight(h);

	inImage.setImagePath(lpCmdLine);
	inImage.ReadImage();
	if(!missFlag){
		inImage.Modify(atoi(param[1].c_str()), atof(param[2].c_str()), atoi(param[3].c_str()));
	}

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_IMAGE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_IMAGE);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_IMAGE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_IMAGE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}


//
//   FUNCTION: InitInstance(HANDLE, int)
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void averageData(char*& Data, char*& Data3, const int& Height, const int& Width) {
	for (int i = 0; i < Width * Height; i++)
	{
		std::vector<int> temp;
		if (Data[3 * i] == 0 && i >= Width && i < (Width * Height - Width) && (i % Width != 0) && (i + 1) % Width != 0) {
			temp = { Data[3 * (i + 1)], Data[3 * (i - 1)],
				Data[3 * (i - Width)], Data[3 * (i - Width - 1)], Data[3 * (i - Width + 1)],
				Data[3 * (i + Width - 1)], Data[3 * (i + Width)], Data[3 * (i + Width + 1)] };
			std::sort(temp.begin(), temp.end());
			Data3[3 * i] = (temp[4] + temp[3]) / 2;
			temp = { Data[3 * (i + 1) + 1], Data[3 * (i - 1) + 1], Data[3 * (i - Width) + 1], Data[3 * (i - Width - 1) + 1],
				Data[3 * (i - Width + 1) + 1],Data[3 * (i + Width - 1) + 1], Data[3 * (i + Width) + 1], Data[3 * (i + Width + 1) + 1] };
			std::sort(temp.begin(), temp.end());
			Data3[3 * i + 1] = (temp[4] + temp[3]) / 2;
			temp = { Data[3 * (i + 1) + 2], Data[3 * (i - 1) + 2], Data[3 * (i - Width) + 2], Data[3 * (i - Width - 1) + 2],
				Data[3 * (i - Width + 1) + 2],Data[3 * (i + Width - 1) + 2], Data[3 * (i + Width) + 2], Data[3 * (i + Width + 1) + 2] };
			std::sort(temp.begin(), temp.end());
			Data3[3 * i + 2] = (temp[4] + temp[3]) / 2;
		}
		else {
			Data3[3 * i] = Data[3 * i];
			Data3[3 * i + 1] = Data[3 * i + 1];
			Data3[3 * i + 2] = Data[3 * i + 2];
		}
	}
}
const int points = 20;
std::vector<int> getError() {
	char* Data = inImage.getImageData();
	int Height = inImage.getHeight();
	int Width = inImage.getWidth();
	std::vector<int> errors;
	// Data2 salty picture
	int remove;
	int i;
	char* Data2 = inImage.getImageData();
	for (int percent = 0; percent <= points; percent++) {
	
		for (i = 0; i < round(Height * Width * percent/40); ++i) {
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			std::uniform_int_distribution<> distrib(1, Height * Width);
			remove = distrib(gen);
			Data2[3 * remove] = 0;
			Data2[3 * remove + 1] = 0;
			Data2[3 * remove + 2] = 0;
		}
		//int error2 = 0;
		//for (i = 0; i < Height * Width; i++)
		//{
		//	error2 += abs(Data2[3 * i] - Data[3 * i]) / 3 + abs(Data2[3 * i + 1] - Data[3 * i + 1]) / 3 + abs(Data2[3 * i + 2] - Data[3 * i + 2]) / 3;
		//}
		char* Data3 = new char[Height * Width * 3];
		averageData(Data2, Data3, Height, Width);
		int error = 0;
		for (i = 0; i < Height * Width; i++)
		{
			error += abs(Data3[3 * i] - Data[3 * i]) / 3 + abs(Data3[3 * i + 1] - Data[3 * i + 1]) / 3 + abs(Data3[3 * i + 2] - Data[3 * i + 2]) / 3;
		}
		errors.push_back(error);
	}
	delete Data;
	return errors;
}
char* getCircle(const int &x, const int &y) {
	double  ratio = atof(param[2].c_str());
	char* Data = inImage.getImageData();
	const char* Circle = inImage.getChangedData();
	int newx = int((x + 1) * ratio + 0.5) - 1;
	int newy = int((y + 1) * ratio + 0.5) - 1;
	char* Back = new char[3*inImage.getWidth() * inImage.getHeight()];
	for (int i = 0; i < inImage.getWidth() * inImage.getHeight(); i++)
	{
		Back[3 * i] = Data[3 * i];
		Back[3 * i+1] = Data[3 * i + 1];
		Back[3 * i+2] = Data[3 * i + 2];
	}
	for (int i = 0; i < inImage.getHeight(); i++) {
		for (int j = 0; j < inImage.getWidth(); j++) {
			if (round(sqrt((i - x) * (i - x) + (j - y) * (j - y))) < 50) {
				int differi = i - x;
				int differj = j - y;
				int newpos = max(((newx + differi) * inImage.getChangedWidth() + (newy + differj)), inImage.getChangedWidth());
				Back[3 * (i * inImage.getWidth() + j)] = Circle[3 * newpos];
				Back[3 * (i * inImage.getWidth() + j) + 1] = Circle[3 * newpos + 1];
				Back[3 * (i * inImage.getWidth() + j) + 2] = Circle[3 * newpos + 2];
			}
		}
	}
	return Back;
}
//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
int x = 0;
int y = 0;
int oldx = 0;
int oldy = 0;
int redraw = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	RECT rt;
	GetClientRect(hWnd, &rt);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case ID_MODIFY_IMAGE:
				   InvalidateRect(hWnd, &rt, false); 
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_MOUSEMOVE: {
			if (atoi(param[1].c_str()) == 2) {
				x = GET_Y_LPARAM(lParam);//LOWORD
				y = GET_X_LPARAM(lParam);//HIWORD
				if (x > 80) {
					redraw = 1;
					x = x - 80;//x is Height
					InvalidateRect(hWnd, NULL, false);
				}
			}
			break;
		}

		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);
				if (atoi(param[1].c_str()) < 3){
					
					char text[1000];
					strcpy(text, "The original image is shown as follows. \n");
					DrawText(hdc, text, strlen(text), &rt, DT_LEFT);
					strcpy(text, "\nUpdate program with your code to modify input image. \n");
					DrawText(hdc, text, strlen(text), &rt, DT_LEFT);

					BITMAPINFO bmi;
					CBitmap bitmap;
					memset(&bmi, 0, sizeof(bmi));
					bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
					bmi.bmiHeader.biPlanes = 1;
					bmi.bmiHeader.biBitCount = 24;
					bmi.bmiHeader.biCompression = BI_RGB;
					if (atoi(param[1].c_str()) == 1) {
						bmi.bmiHeader.biWidth = inImage.getChangedWidth();
						bmi.bmiHeader.biHeight = -inImage.getChangedHeight();  // Use negative height.  DIB is top-down.
						bmi.bmiHeader.biSizeImage = inImage.getChangedWidth() * inImage.getChangedHeight();
						SetDIBitsToDevice(hdc,
							0, 80, inImage.getChangedWidth(), inImage.getChangedHeight(),
							0, 0, 0, inImage.getChangedHeight(),
							inImage.getChangedData(), &bmi, DIB_RGB_COLORS);
					}
					else if (atoi(param[1].c_str()) == 2) {
						bmi.bmiHeader.biWidth = inImage.getWidth();
						bmi.bmiHeader.biHeight = -inImage.getHeight();  // Use negative height.  DIB is top-down.
						bmi.bmiHeader.biSizeImage = inImage.getWidth() * inImage.getHeight();
						if (redraw == 0) {
							SetDIBitsToDevice(hdc,
								0, 80, inImage.getWidth(), inImage.getHeight(),
								0, 0, 0, inImage.getHeight(),
								inImage.getImageData(), &bmi, DIB_RGB_COLORS);
						}
						if (redraw == 1) {
							SetDIBitsToDevice(hdc,
								0, 80, inImage.getWidth(), inImage.getHeight(),
								0, 0, 0, inImage.getHeight(),
								getCircle(x,y), &bmi, DIB_RGB_COLORS);
							redraw = 0;
						}
					}
				}
				else {
					std::vector<int> errors = getError();
					
					int Max= *max_element(std::begin(errors), std::end(errors));
					int Min = *min_element(std::begin(errors), std::end(errors));
					HGDIOBJ hPen = CreatePen(PS_SOLID, 5, RGB(45, 45, 45)); //ExtCreatePen(PS_COSMETIC, dwPenStyle[i], 1, &lb, 0, NULL); 
					HGDIOBJ hPenOld = SelectObject(hdc, hPen);
					POINT tickPnts[points+1];
					for (int i = 0; i < points+1 ; i++) {
						tickPnts[i] = { 50+ i * 30, 600 - int(double(errors[i]) / (Max - Min) * 500.0) };
						printf("%d:%d \n",i,int(errors[i]));
					}
					MoveToEx(hdc, tickPnts[0].x, tickPnts[0].y, NULL);
					PolylineTo(hdc, tickPnts, points);
					SelectObject(hdc, hPenOld);
					DeleteObject(hPen);
				}
	   
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




// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

