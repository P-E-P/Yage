#include "camera.h"

#define ANGLE_SPEED 0.001
#define SPEED 0.03

Camera::Camera(XMVECTOR Eye, XMVECTOR At, XMVECTOR Up, XMMATRIX projection)
{
	XMStoreFloat4x4(&start, XMMatrixLookAtLH(Eye, At, Up));
	XMStoreFloat4x4(&view, XMMatrixLookAtLH(Eye, At, Up));
	XMStoreFloat4x4(&this->projection, projection);

	angle_y = 0;
	pos = XMFLOAT3(0, 0, 0);
}


Camera::~Camera()
{
}

void Camera::onTick()
{

	angle_y = Mouse::getInstance().getX() / 100.0f;

	XMMATRIX Ry, Rx, T;

	Ry = XMMatrixRotationY(angle_y);
	Rx = XMMatrixRotationX(angle_x);
	//translation
	XMFLOAT3 lookat_worldcoord = XMFLOAT3(0, 0, SPEED);
	XMFLOAT3 normal_worldcoord = XMFLOAT3(SPEED, 0, 0);
	XMMATRIX R = Rx * Ry;
	XMFLOAT3 lookat_viewcoord = mul(R, lookat_worldcoord);
	XMFLOAT3 normal_viewcoord = mul(R, normal_worldcoord);

	if (Keyboard::getInstance().getKeyState(VK_UP)) {
		pos = pos - lookat_viewcoord;
	}
	if (Keyboard::getInstance().getKeyState(VK_DOWN)) {
		pos = pos + lookat_viewcoord;
	}

	if (Keyboard::getInstance().getKeyState(VK_LEFT)) {
		pos = pos + normal_viewcoord;
	}
	if (Keyboard::getInstance().getKeyState(VK_RIGHT)) {
		pos = pos - normal_viewcoord;
	}

	T = XMMatrixTranslation(-pos.x, -pos.y, pos.z);

	XMStoreFloat4x4(&view,T * XMLoadFloat4x4(&start) * Ry * Rx);
}

XMMATRIX Camera::getView() const
{
	return XMLoadFloat4x4(&view);
}

XMMATRIX Camera::getProjection() const
{
	return XMLoadFloat4x4(&projection);
}