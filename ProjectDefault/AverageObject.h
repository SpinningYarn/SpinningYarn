#pragma once
#include "Common.h"
#include "Object.h"

class AverageObject : public Object
{
public:
	AverageObject(const int& objectNum, std::string objectName);
	AverageObject(int objectNum, std::string objectName, double posX, double posY);
	~AverageObject();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩		

private:
	
};
