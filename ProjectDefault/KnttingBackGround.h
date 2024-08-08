#pragma once
#include "Object.h"

/// <summary>
/// 
/// ���� �ý��� ���Զ����� ���������� ������ ���ȭ�� ������Ʈ
/// ���̾ ���ϴ����� �����Ͽ� �׻� ���� �Ʒ��� ��ġ��
/// 
/// 2022.02.09 YJH
/// </summary>

class KnttingBackGround : public Object
{
public:
	KnttingBackGround(const int objectNum, std::string objectName);
	KnttingBackGround(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~KnttingBackGround();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�	

private:
	int m_ScreenSizeX;
	int m_ScreenSizeY;
};

