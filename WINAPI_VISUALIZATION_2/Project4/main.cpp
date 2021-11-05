
#include "stdafx.h"





LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
void draw_diagram(HDC hdc, data data);

HWND start_button,time_add,time_dec,spd_add,spd_dec;
HWND label_spd, label_amp,label_XY,label_XZ;
HWND hwnd;
int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) 
{

	data data;
	input(data);
	
	srand(time(NULL));
	random = (rand() % 10) + 1;
	it = random;

	//GDI INIT
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);


	// Register the window class
	const char *CLASS_NAME = "WindowClass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);



	// Create the window
	
	hwnd=CreateWindowEx(WS_EX_CLIENTEDGE, CLASS_NAME, "ZAD 11a", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, x, y, NULL, NULL, currentInstance, NULL);
	//Create button
	start_button = CreateWindow("button", "START", WS_CHILD | WS_VISIBLE, x*0.125, 0.03*y, 120, 40, hwnd, (HMENU)WM_START, currentInstance, NULL);
	spd_dec = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE, x*0.05, 0.1*y, 60, 30, hwnd, (HMENU)SPD_DEC, currentInstance, NULL);
	spd_add = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE, x*0.25, 0.1*y, 60, 30, hwnd, (HMENU)SPD_ADD, currentInstance, NULL);
	time_dec = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE, x*0.05, 0.15*y, 60, 30, hwnd, (HMENU)TIME_DEC, currentInstance, NULL);
	time_add = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE, x*0.25, 0.15*y, 60, 30, hwnd, (HMENU)TIME_ADD, currentInstance, NULL);
	label_spd = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, x*0.125, y*0.1, 120, 30, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_spd, " SPEED");
	label_amp = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, x*0.125,y*0.15, 120, 30, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_amp, "TIME_STEP");
	label_XY = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, x*0.425, y*0.05, 120, 30, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_XY, " XY Position");
	label_XZ = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, x*0.425, y*0.3, 120, 30, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_XZ, "XZ Postion");


	
	
	UpdateWindow(hwnd);

	



	if (hwnd == NULL)
	{
		MessageBox(NULL, "TERAZ TO PO MNIE","RIP", MB_ICONEXCLAMATION);
		return 1;
	}
	
	
	

	ShowWindow(hwnd, cmdCount); // Poka¿ okienko...
	UpdateWindow(hwnd);
	//SetTimer(hwnd, tmr_id, 1000, NULL);
	// Window loop
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	

	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return 0;
}

bool start = false;
bool ontick= true;

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	HDC hdc;
	PAINTSTRUCT ps;
	data data;
	input(data);
	int id;
	id = LOWORD(param);
	switch (msg) {
	case WM_COMMAND:
		switch (id) {
		
			case WM_START:
			{
				start = true;
				break;
			}
			case SPD_ADD:
				spd++;
				break;
			case SPD_DEC:
				spd--;
				break;
			case TIME_ADD:
				time_step+=50;
				break;
			case TIME_DEC:
				time_step-=50;
				break;
		}
	case WM_TIMER:
	
		ontick = true;
		
		RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
		KillTimer(hwnd, tmr_id);
		break;
		

	case WM_PAINT:
		if (start) {
			if (ontick)
			{
					hdc = BeginPaint(hwnd, &ps);
					draw_diagram(hdc, data);
					EndPaint(hwnd, &ps);
					UpdateWindow(hwnd);

					SetTimer(hwnd, TMR, time_step, 0);
					
				
				ontick = false;
				//SetTimer(hwnd, tmr_id, time_step, NULL);
				
			}
		}
		break;
		
		
	case WM_DESTROY:
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		break;
	
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
	
	return 0;
	}



void draw_diagram(HDC hdc, data data)
{
	
	
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 122, 122, 122),2);
	Gdiplus::Pen pen2(Gdiplus::Color(255, 74, 172, 50),2);
	Gdiplus::Pen pen3(Gdiplus::Color(255, 200, 202, 120),2);
	Gdiplus::Pen pen4(Gdiplus::Color(255, 0, 0, 0));
	Gdiplus::Pen pen5(Gdiplus::Color(255, 0, 0, 255),2);
	
	for (int z = 0; z < spd; z++)
	{
		if (it < data.pitch.size())
		{
			if (it == random)
			{
				gf.DrawLine(&pen4, base_x - 30, base_y, x, base_y);
				gf.DrawLine(&pen4, base_x, base_y - 200, base_x, base_y + 250);
				gf.DrawLine(&pen4, second_x - 200, second_y, x, second_y);
				gf.DrawLine(&pen4, second_x, second_y - 1500, second_x, second_y + 150);
				gf.DrawLine(&pen4, third_x - 200, third_y, x, third_y);
				gf.DrawLine(&pen4, third_x, third_y - 150, third_x, third_y + 150);

			}

			//ALL DIAGRAM
			base_x += 1;
			base_y += 1;
			gf.DrawLine(&pen, base_x - 1, abs(int((-data.roll[it - 1]) + base_y - it)), base_x, abs(int((-data.roll[it]) + base_y - it)));
			gf.DrawLine(&pen2, base_x - 1, abs(int((-data.pitch[it - 1]) + base_y - it)), base_x, abs(int((-data.pitch[it]) + base_y - it)));
			gf.DrawLine(&pen3, base_x - 1, abs(int((-data.yaw[it - 1]) + base_y - it)), base_x, abs(int((-data.yaw[it]) + base_y - it)));

			//XY DIAGRAM
			gf.DrawLine(&pen5, second_x + (int((data.roll[it - 1]))), second_y - (int((data.pitch[it - 1]))), second_x + (int((data.roll[it]))), second_y - (int((data.pitch[it]))));
			//XZ DIAGRAM
			gf.DrawLine(&pen5, third_x + (int((data.roll[it - 1]))), third_y - (int((data.yaw[it - 1]))), third_x + (int((data.roll[it]))), third_y - (int((data.yaw[it]))));



			it++;
		}
	}
	//}

}



