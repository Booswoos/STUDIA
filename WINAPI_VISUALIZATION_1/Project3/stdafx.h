// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <SDKDDKVer.h>


// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
//#include <windows.h>
//#include <gdiplus.h>
#include <math.h>

#include <iostream>
#include <fstream>
#define WM_START 199
#define WM_DIAGRAM 201
#define WM_A_AMPLITUDE 202
#define WM_D_AMPLITUDE 203
#define WM_A_SPEED 204
#define WM_D_SPEED 205
#define PI 3.14159
#define TMR 206

const int x = 1400;
const int y = 1000;
float spd = 1000;
float amp = 1;
int it = 1; int base_x = 70;
int base_y = 670;
int tmr_id = 1;
int random;


typedef struct {
	std::vector <float> roll;
	std::vector <float> pitch;
	std::vector <float> yaw;} 
data;

  void input(data &data)
  {
	  std::fstream file;
	  file.open("outputRotateB01.log", std::ios::in);


	  float tmp1 = 0, tmp2 = 0, tmp3 = 0,tmp4;
	 
	  while (!file.eof())
	  {
		  
		  file >> tmp1 >> tmp2 >> tmp3>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4;
		  data.pitch.push_back(tmp1);
		  data.roll.push_back(tmp2);
		  data.yaw.push_back(tmp3);
		 
	  }
  }

