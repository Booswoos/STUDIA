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
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>

#define WM_START 199
#define TMR 200
#define SPD_ADD 201
#define SPD_DEC 202
#define TIME_DEC 203
#define TIME_ADD 204
#define PI 3.14

const int x = 1200;
const int y = 1000;
float spd = 1;
int time_step = 800;
int it = 1;
int base_x = 30;
int base_y = 800;
int second_x = 800;
int second_y = 120;
int third_x = 800;
int third_y = 430;
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
	  file.open("outputRobotForwardB01.log", std::ios::in);


	  float tmp1 = 0, tmp2 = 0, tmp3 = 0,tmp4;
	 
	  while (!file.eof())
	  {
		  
		  file >> tmp1 >> tmp2 >> tmp3>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4>>tmp4;
		  data.pitch.push_back(tmp1);
		  data.roll.push_back(tmp2);
		  data.yaw.push_back(tmp3);
		 
	  }
  }

