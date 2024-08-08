#pragma once
#include "Object.h"

/// <summary>
/// 
/// �߰��� �ٴ�
/// ����̰� ���ظ� �ϸ�
/// ������ ����
/// 
/// 2022.02.16 YJH
/// </summary>

class Needle : public Object
{
public:
	Needle(const int objectNum, std::string objectName);
	Needle(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~Needle();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

	void MoveNeedleX(double MoveSize);			// SIZE��ŭ ������
	void MoveNeedleY(double MoveSize);			// SIZE��ŭ ������
	double GetNeedleX();
	void SetOriginX();


private:
	double m_NeedleX;
	double m_NeedleY;
};

