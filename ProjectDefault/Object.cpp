#include "Object.h"

Object::Object(const int objectNum, const std::string& objectName)		// ������Ʈ ����� �̸��� �ε��� �ʱ�ȭ
	: m_Index (objectNum), m_Name (objectName), m_posX(0), m_posY(0), renderOrder(0)
{

}

Object::Object(const int objectNum, const std::string& objectName, const double posX, const double posY)		// ������Ʈ ����� �̸��� �ε���, X��ǥ, Y��ǥ �ʱ�ȭ
	: m_Index(objectNum), m_Name(objectName), m_posX(posX), m_posY(posY), renderOrder(0)
{

}

Object::~Object()
{

}

const int Object::GetObjectIndex()							// ������Ʈ �ε��� ��������
{
	return m_Index;
}

const std::string& Object::GetObjectName()					// ������Ʈ ��ȣ ��������
{
	return m_Name;
}

const double Object::GetPositionX()								// ������Ʈ X��ǥ ��������
{
	return m_posX;
}

const double Object::GetPositionY()								// ������Ʈ Y��ǥ ��������
{
	return m_posY;
}

const double Object::SetPositionX(double num)
{
	m_posX += num;
	return m_posX;
}

const double Object::SetPositionY(double num)
{
	m_posY += num;
	return m_posY;
}

void Object::SetOriginX(double num)
{
	m_posX = num;
}

