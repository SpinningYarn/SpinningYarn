#pragma once
#include "Common.h"
#include "eObjectDefine.h"

class Object
{
public:
	Object(const int objectNum, const std::string& objectName);								// �����Ҷ� ������Ʈ�� �ε���, �̸��� �ο�
	Object(const int objectNum, const std::string& objectName, const double posX, const double posY);	// �����Ҷ� ������Ʈ�� �ε���, �̸�, x�� y��ǥ�� �ο�

	~Object();
	
	/// ���������Լ��̱⿡ �ݵ�� ���� ������Ʈ���� �����ؾ���!!!!!
	virtual void UpdateObject() abstract;				// ������Ʈ�� ������Ʈ -> ������Ʈ�� �θ�� �� ���� ��ü���� �������̵� �� ����
	virtual void RenderObject() abstract;				// ������Ʈ�� �׸��� -> ������Ʈ�� �θ�� �� ���� ��ü���� �������̵� �� ����
	
	const int GetObjectIndex();							// ������Ʈ �ε��� ��������
	const std::string& GetObjectName();					// ������Ʈ �̸� ��������
	const double GetPositionX();						// ������Ʈ X��ǥ ��������
	const double GetPositionY();						// ������Ʈ Y��ǥ ��������
	const double SetPositionX(double num);				// ������Ʈ X��ǥ ����
	const double SetPositionY(double num);				// ������Ʈ Y��ǥ ����
	void SetOriginX(double num);

	int renderOrder;									//������ ����
private:
	int m_Index;										// ������Ʈ ������ �ε��� (���� ��ȣ)
	std::string m_Name;									// ������Ʈ ������ �̸� (���� �̸�)
	double m_posX;										// ������Ʈ�� X��ǥ
	double m_posY;										// ������Ʈ�� Y��ǥ
};