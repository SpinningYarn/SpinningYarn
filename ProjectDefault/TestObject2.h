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

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�		

private:
	bool playingAnimation;
	D2DEngine* localD2D;
	bool m_raindowReady;
	bool ended = false;
	float rot = 0;
	int ���� = 1;
};

