#pragma once
#include "Common.h"
#include "eObjectDefine.h"

class Object
{
public:
	Object(const int objectNum, const std::string& objectName);								// 생성할때 오브젝트에 인덱스, 이름을 부여
	Object(const int objectNum, const std::string& objectName, const double posX, const double posY);	// 생성할때 오브젝트에 인덱스, 이름, x와 y좌표를 부여

	~Object();
	
	/// 순수가상함수이기에 반드시 하위 오브젝트에서 구현해야함!!!!!
	virtual void UpdateObject() abstract;				// 오브젝트를 업데이트 -> 오브젝트를 부모로 둔 각자 객체에서 오버라이딩 할 예정
	virtual void RenderObject() abstract;				// 오브젝트를 그리기 -> 오브젝트를 부모로 둔 각자 객체에서 오버라이딩 할 예정
	
	const int GetObjectIndex();							// 오브젝트 인덱스 가져오기
	const std::string& GetObjectName();					// 오브젝트 이름 가져오기
	const double GetPositionX();						// 오브젝트 X좌표 가져오기
	const double GetPositionY();						// 오브젝트 Y좌표 가져오기
	const double SetPositionX(double num);				// 오브젝트 X좌표 변경
	const double SetPositionY(double num);				// 오브젝트 Y좌표 변경
	void SetOriginX(double num);

	int renderOrder;									//렌더링 순서
private:
	int m_Index;										// 오브젝트 본인의 인덱스 (고유 번호)
	std::string m_Name;									// 오브젝트 본인의 이름 (고유 이름)
	double m_posX;										// 오브젝트의 X좌표
	double m_posY;										// 오브젝트의 Y좌표
};