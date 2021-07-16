#pragma once
class Camera
{
private:
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;

	D3DXVECTOR3 vEyePt;
	D3DXVECTOR3 vLookatPt;
	D3DXVECTOR3 vUpVec;
	D3DXVECTOR3 vRightVec;

	bool cameraFreeView;

	D3DXVECTOR2 rotation;
	D3DXVECTOR2 mousePos;

public:
	Camera();
	virtual ~Camera();

	bool onClick;


	void Rotate();
	void Update();
	void SetTransform();
};
