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

public:
	Camera();
	virtual ~Camera();

	float cameraSpeed;
	bool cameraFreeView;

	void Update();
	void SetTransform();

	void FrontTranslate(float speed);
	void SideTranslate(float speed);

	void RotationCross(float angle);
	void RotationUp(float angle);

	void Translate();
};
