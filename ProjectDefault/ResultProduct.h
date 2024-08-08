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
	double m_DivideAmount;			//�� ���� �Ұ��ΰ�
	double m_CurrentDivide;			//ȭ�鿡 ���������̴� �κ��� ��� �Ұ��ΰ�
	double m_CurrentY;
};

