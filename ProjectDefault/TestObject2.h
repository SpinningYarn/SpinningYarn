#pragma once
#include "Common.h"
#include "Object.h"

class D2DEngine;

class TestObject2 : public Object
{
public:
	TestObject2(const int& objectNum, std::string objectName);
	TestObject2(int objectNum, std::string objectName, double posX, double posY);
	~TestObject2();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩		

private:
	bool playingAnimation;
	D2DEngine* localD2D;
	bool m_raindowReady;
	bool ended = false;
	float rot = 0;
	int 데헷 = 1;
};

