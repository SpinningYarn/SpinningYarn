#pragma once
#include "Object.h"
using namespace std;

class ResultProduct : public Object
{
public:
	ResultProduct(const int objectNum, string objectName);
	ResultProduct(const int objectNum, const string& objectName, const double posX, const double posY);
	~ResultProduct();

public:
	virtual void UpdateObject() override;
	virtual void RenderObject() override;
	void SetCurrentDivide(double divide, int Amount);

private:
	double m_DivideAmount;			//총 몇등분 할것인가
	double m_CurrentDivide;			//화면에 나눠져보이는 부분을 어떻게 할것인가
	double m_CurrentY;
};

