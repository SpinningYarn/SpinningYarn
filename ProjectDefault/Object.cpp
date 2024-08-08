#include "Object.h"

Object::Object(const int objectNum, const std::string& objectName)		// 오브젝트 요소인 이름과 인덱스 초기화
	: m_Index (objectNum), m_Name (objectName), m_posX(0), m_posY(0), renderOrder(0)
{

}

Object::Object(const int objectNum, const std::string& objectName, const double posX, const double posY)		// 오브젝트 요소인 이름과 인덱스, X좌표, Y좌표 초기화
	: m_Index(objectNum), m_Name(objectName), m_posX(posX), m_posY(posY), renderOrder(0)
{

}

Object::~Object()
{

}

const int Object::GetObjectIndex()							// 오브젝트 인덱스 가져오기
{
	return m_Index;
}

const std::string& Object::GetObjectName()					// 오브젝트 번호 가져오기
{
	return m_Name;
}

const double Object::GetPositionX()								// 오브젝트 X좌표 가져오기
{
	return m_posX;
}

const double Object::GetPositionY()								// 오브젝트 Y좌표 가져오기
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

