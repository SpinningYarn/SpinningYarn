#pragma once
#include "Common.h"
#include "Object.h"

class AverageObject : public Object
{
public:
	AverageObject(const int& objectNum, std::string objectName);
	AverageObject(int objectNum, std::string objectName, double posX, double posY);
	~AverageObject();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�		

private:
	
};
