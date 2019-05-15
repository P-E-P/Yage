#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <windowsx.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <fstream>
using namespace std;
#include <direct.h>
#include <commdlg.h>
#include <malloc.h>
#include <cmath>
#include <string.h>
#include <tchar.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>


struct SimpleVertex
	{
	XMFLOAT3 Pos;//12 byte
	XMFLOAT2 Tex;//8 byte
	XMFLOAT3 Norm;//12 byte
	};



//for matrix and vector operations, some handy functions:
float length(const XMFLOAT3 &v);
XMFLOAT3 mul(const XMMATRIX &M, const XMFLOAT3 &rhs);
XMMATRIX mul(const XMMATRIX &lhs, const XMMATRIX &rhs);
float dot(XMFLOAT3 a, XMFLOAT3 b);
XMFLOAT3 cross(XMFLOAT3 a, XMFLOAT3 b);
XMFLOAT3 normalize(const  XMFLOAT3 &a);
XMFLOAT3 operator+(const XMFLOAT3 lhs, const XMFLOAT3 rhs);
XMFLOAT2 operator+(const XMFLOAT2 lhs, const XMFLOAT2 rhs);
XMFLOAT3 operator-(const XMFLOAT3 lhs, const XMFLOAT3 rhs);

