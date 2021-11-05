
#include "stdafx.h"





LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

void draw_compass(HDC hdc,data data,HWND hwnd);
void draw_diagram(HDC hdc, data data,HWND hwnd);

HWND main_button,add_speed,decrease_speed,add_amplitude,decrease_amplitude,start_button;
HWND label_a, label_s;
HWND label_N, label_E, label_S, label_W;;
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
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW+1;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);



	// Create the window
	
	hwnd=CreateWindowEx(WS_EX_CLIENTEDGE, CLASS_NAME, "ZAD 10B", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, x, y, NULL, NULL, currentInstance, NULL);
	//Create button
	start_button = CreateWindow("button", "START", WS_CHILD | WS_VISIBLE, x*0.1, 0.05*y, 120, 40, hwnd, (HMENU)WM_START, currentInstance, NULL);
	main_button = CreateWindow( "button", "show diagram", WS_CHILD | WS_VISIBLE, x*0.2, 0.1*y, 120, 40, hwnd, (HMENU)WM_DIAGRAM, currentInstance, NULL);
	add_speed = CreateWindowEx(0,"button", "+", WS_CHILD | WS_VISIBLE, x*0.3, 0.15*y, 40, 40, hwnd, (HMENU)WM_A_AMPLITUDE, currentInstance, NULL);
	decrease_speed = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE, x*0.15, 0.15*y, 40, 40, hwnd, (HMENU)WM_D_AMPLITUDE, currentInstance, NULL);
	add_amplitude = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE, x*0.3, 0.2*y, 40, 40, hwnd, (HMENU)WM_A_SPEED, currentInstance, NULL);
	decrease_speed = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE, x*0.15, 0.2*y, 40, 40, hwnd, (HMENU)WM_D_SPEED, currentInstance, NULL);
	label_a = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, x*0.2, 0.15*y, 120, 40, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_a , " AMPLITUDE");
	label_s = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, x*0.2, 0.2*y, 120, 40, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_s, " SPEED");
	label_N = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 990, 30, 20, 20, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_N, " N");
	label_E = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 1200, 235, 20, 20, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_E, " E");
	label_S = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 990, 450, 20, 20, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_S, " S");
	label_W = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER, 780, 235, 20, 20, hwnd, NULL, currentInstance, NULL);
	SetWindowText(label_W, " W");
	
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

bool diagram=false;
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
			case WM_DIAGRAM:
			{
				//MessageBox(hwnd, "gz", "alert", NULL);
				diagram = true;
				RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
				break;
			}
			case WM_A_AMPLITUDE:
			{
				if(amp<=2)
					amp += 0.2;
				break;
			}
			case WM_D_AMPLITUDE:
			{
				if(amp>0.2)
					amp -= 0.2;
				break;
			}
			case WM_A_SPEED:
			{
				spd+=100;
				break;
			}
			case WM_D_SPEED:
			{
				spd-=100;
				break;
			}
			case WM_START:
			{
				start = true;
				break;
			}
		}
	case WM_TIMER:
	
		//MessageBox(hwnd, "erg", "rrtrere", NULL);
		ontick = true;
		//diagram = true;
		RedrawWindow(hwnd, 0, 0, RDW_INVALIDATE);
		KillTimer(hwnd, tmr_id);
		break;
		

	case WM_PAINT:
		if (start) {
			if (ontick)
			{
				if (diagram)
				{
					//MessageBox(hwnd, "5665", "56", NULL);
					hdc = BeginPaint(hwnd, &ps);
					draw_diagram(hdc, data, hwnd);
					EndPaint(hwnd, &ps);
					UpdateWindow(hwnd);
					
				}
				
				else
				{


					//SetTimer(hwnd, TMR, 25, 0);
					hdc = BeginPaint(hwnd, &ps);
					draw_compass(hdc, data, hwnd);
					EndPaint(hwnd, &ps);
					UpdateWindow(hwnd);
				}
				ontick = false;
				SetTimer(hwnd, tmr_id, spd, NULL);
				
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


float  calc_angle(float px,int py)
{
	float angle;
	angle = atan2(-px, py);
	return angle;
}


void draw_compass(HDC hdc,data data,HWND hwnd)
{
	//data data;
	//input(data);

	float tmp=0;
	int dist = 0;
	float rad = 0;
	const int circle_x = 400, circle_y = 400;
	float point_x = x / 2+300;
	float point_y = y / 4;
	float multiplier = point_x / 5.2;


	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0),6);  
	Gdiplus::Pen c_pen(Gdiplus::Color(255, 166, 166, 166),6);
	Gdiplus::SolidBrush Brush(Gdiplus::Color(255, 166, 166, 166));
	gf.DrawEllipse(&pen, int(point_x) - circle_x / 2, int(point_y) - circle_y / 2, circle_x, circle_y);
	gf.FillEllipse(&Brush, int(point_x) - circle_x / 2, int(point_y) - circle_y / 2, circle_x, circle_y);
	for (int i = 0; i < data.pitch.size(); i++)
	{
		if (i == 0)
		{
			gf.DrawLine(&pen, point_x, point_y, point_x, point_y - multiplier * cos(0));
			Sleep(200);
		}
		if (i != 0)
		{
		
			gf.DrawLine(&c_pen, point_x, point_y, point_x + multiplier * sin(tmp), point_y - multiplier * cos(tmp));
		//	draw_diagram(hdc,data,i);
		}
		rad = calc_angle(data.pitch[i],data.roll[i]);
		tmp = rad;
			gf.DrawLine(&pen, point_x, point_y, point_x + multiplier * sin(rad), point_y - multiplier * cos(rad));
			Sleep(15);
		
	}


}

void draw_diagram(HDC hdc, data data, HWND hwnd)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 122, 0),2);
	Gdiplus::Pen pen2(Gdiplus::Color(255, 104, 122, 50),2);
	Gdiplus::Pen pen3(Gdiplus::Color(255, 200, 122, 120),2);
	Gdiplus::Pen pen4(Gdiplus::Color(255, 255, 255, 255),3);
	if (it == random)
		{
		gf.DrawLine(&pen4, base_x - 20, base_y, x, base_y);
		gf.DrawLine(&pen4, base_x, base_y - 400, base_x, base_y + 250);
		}
//for (int it = 1; it < data.pitch.size(); it++)
	//	int z = i + 1;
		//for (i; i<z; i++)
	//	{
			base_y += 1;
			base_x += 1;

			gf.DrawLine(&pen, base_x - 1, abs(int(amp*(-data.roll[it - 1]) + base_y - it)), base_x, abs(int(amp*( -data.roll[it]) + base_y - it)));
			gf.DrawLine(&pen2, base_x - 1, abs(int(amp*(-data.pitch[it - 1]) + base_y - it)), base_x, abs(int(amp*( -data.pitch[it]) + base_y - it)));
			gf.DrawLine(&pen3, base_x - 1, abs(int(amp*(-data.yaw[it - 1]) + base_y - it)), base_x, abs(int(amp*(-data.yaw[it]) + base_y - it)));
			it++;
		
	//	}
}
