#include <list>

#include "camera.h"
#include "skybox.h"
#include "scene.h"
#include "keyboard.h"
#include "mouse.h"
#include "engine.h"

#define MAX_LOADSTRING 1000
#define TIMER1 111


HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
HWND hMain = NULL;
static char MainWin[] = "MainWin";
HBRUSH  hWinCol = CreateSolidBrush(RGB(180, 180, 180));

Engine* engine;


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

//rasterizer states
ID3D11RasterizerState				*rs_CW, *rs_CCW, *rs_NO, *rs_Wire;
//depth state
ID3D11DepthStencilState				*ds_on, *ds_off;
//	structures we need later

XMMATRIX g_world;//model: per object position and rotation and scaling of the object


// TODO: make this better
ID3D11Buffer* vertexBufferShape = NULL;


HRESULT InitDevice()
{

	RECT rc;
	GetClientRect(hMain, &rc);	//getting the windows size into a RECT structure
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;


	//world
	g_world = XMMatrixIdentity();
	


	engine = new Engine(hMain, width, height);


	HRESULT hr = S_OK;
	//rasterizer states:
	//setting the rasterizer:
	D3D11_RASTERIZER_DESC RS_CW, RS_Wire;

	RS_CW.AntialiasedLineEnable = FALSE;
	RS_CW.CullMode = D3D11_CULL_BACK;
	RS_CW.DepthBias = 0;
	RS_CW.DepthBiasClamp = 0.0f;
	RS_CW.DepthClipEnable = true;
	RS_CW.FillMode = D3D11_FILL_SOLID;
	RS_CW.FrontCounterClockwise = false;
	RS_CW.MultisampleEnable = FALSE;
	RS_CW.ScissorEnable = false;
	RS_CW.SlopeScaledDepthBias = 0.0f;
	//rasterizer state clockwise triangles
	engine->renderer->device->CreateRasterizerState(&RS_CW, &rs_CW);
	//rasterizer state counterclockwise triangles
	RS_CW.CullMode = D3D11_CULL_FRONT;
	engine->renderer->device->CreateRasterizerState(&RS_CW, &rs_CCW);
	RS_Wire = RS_CW;
	RS_Wire.CullMode = D3D11_CULL_NONE;
	//rasterizer state seeing both sides of the triangle
	engine->renderer->device->CreateRasterizerState(&RS_Wire, &rs_NO);
	//rasterizer state wirefrime
	RS_Wire.FillMode = D3D11_FILL_WIREFRAME;
	engine->renderer->device->CreateRasterizerState(&RS_Wire, &rs_Wire);

	//init depth stats:
	//create the depth stencil states for turning the depth buffer on and of:
	D3D11_DEPTH_STENCIL_DESC		DS_ON, DS_OFF;
	DS_ON.DepthEnable = true;
	DS_ON.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DS_ON.DepthFunc = D3D11_COMPARISON_LESS;
	// Stencil test parameters
	DS_ON.StencilEnable = true;
	DS_ON.StencilReadMask = 0xFF;
	DS_ON.StencilWriteMask = 0xFF;
	// Stencil operations if pixel is front-facing
	DS_ON.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DS_ON.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DS_ON.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DS_ON.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Stencil operations if pixel is back-facing
	DS_ON.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DS_ON.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DS_ON.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DS_ON.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Create depth stencil state
	DS_OFF = DS_ON;
	DS_OFF.DepthEnable = false;
	engine->renderer->device->CreateDepthStencilState(&DS_ON, &ds_on);
	engine->renderer->device->CreateDepthStencilState(&DS_OFF, &ds_off);



	// FIXME: This part doesn't seems right, have you inverted the view? You should not set negative value for camera...
	Camera* cam = new Camera(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
		XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f),
		XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 10000.0f));

	Skybox* skybox = new Skybox(cam, L"my_skybox.jpg", engine->renderer, rs_CCW, ds_off, rs_CW, ds_on);
	Scene* scene = new Scene(skybox, cam);

	engine->addScene(scene);


	// Add objects to the scene
	

	return S_OK;
}


void Render()
{
	engine->render();
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
	{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	hInst = hInstance;
	MSG msg;

	// Globale Zeichenfolgen initialisieren
	LoadString(hInstance, 103, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, 104, szWindowClass, MAX_LOADSTRING);

	WNDCLASSEX wcex;
	BOOL Result = TRUE;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, NULL);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);
	Result = (RegisterClassEx(&wcex) != 0);
	RECT rc = { 0, 0, 1920, 1080 };
	hMain = CreateWindow(L"WindowClass", L"Final project",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if (hMain == 0)	return 0;

	ShowWindow(hMain, nCmdShow);
	UpdateWindow(hMain);


	if (FAILED(InitDevice())) {
		return 0;
	}


	msg = { 0 };
	while (msg.message != WM_QUIT)
		{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render();
		}
	}

	return (int)msg.wParam;
}

void redr_win_full(HWND hwnd, bool erase)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	InvalidateRect(hwnd, &rt, erase);
}

void OnLBD(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	Mouse::getInstance().setCoords(x, y);
	Mouse::getInstance().setKeyFlags(keyFlags);
}

void OnRBD(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	Mouse::getInstance().setCoords(x, y);
	Mouse::getInstance().setKeyFlags(keyFlags);
}

void OnChar(HWND hwnd, UINT ch, int cRepeat)
{

}

void OnLBU(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (x > 250)
	{
		PostQuitMessage(0);
	}
	Mouse::getInstance().setCoords(x, y);
	Mouse::getInstance().setKeyFlags(keyFlags);
}

void OnRBU(HWND hwnd, int x, int y, UINT keyFlags)
{
	Mouse::getInstance().setCoords(x, y);
	Mouse::getInstance().setKeyFlags(keyFlags);
}

void OnMM(HWND hwnd, int x, int y, UINT keyFlags)
{

	engine->VsConstData.mouse_x = (float)(x - 370) / 500.0;
	engine->VsConstData.mouse_y = (float)y / 500.0;
	engine->VsConstData.some_variable_c = 0;
	engine->VsConstData.some_variable_d = 0;

	Mouse::getInstance().setCoords(x, y);
	Mouse::getInstance().setKeyFlags(keyFlags);
}

BOOL OnCreate(HWND hwnd, CREATESTRUCT FAR* lpCreateStruct)
{
	hMain = hwnd;
	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HWND hwin;

	switch (id)
		{
			default:
				break;
		}

}

void OnTimer(HWND hwnd, UINT id) { }

void OnPaint(HWND hwnd) { }

void OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	Keyboard::getInstance().downKey(vk);
}

void OnKeyUp(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{

	Keyboard::getInstance().upKey(vk);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{

	PAINTSTRUCT ps;
	HDC hdc;
	switch (message){

		HANDLE_MSG(hwnd, WM_CHAR, OnChar);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLBD);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, OnLBU);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMM);
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);

		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_KEYDOWN, OnKeyDown);
		HANDLE_MSG(hwnd, WM_KEYUP, OnKeyUp);
		HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
			case WM_PAINT:
				hdc = BeginPaint(hMain, &ps);
				EndPaint(hMain, &ps);
				break;
			case WM_ERASEBKGND:
				return (LRESULT)1;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hwnd, message, wParam, lParam);
		}
	return 0;
	}