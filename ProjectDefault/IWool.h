#pragma once
#include "Object.h"
#include "Common.h"
#include "WoolStat.h"

class IWool : public Object
{
public:
	IWool(const int& objectNum, std::string objectName, 
		int warmth, int durability, int aeration,
		int price, int unlockPrice, int quantity,
		bool isUnlocked, eObjectDefine obDefine, WoolSpcAbility abil1, WoolSpcAbility abil2);

	IWool(int objectNum, std::string objectName, double posX, double posY, 
		int warmth, int durability, int aeration,
		int price, int unlockPrice, int quantity, 
		bool isUnlocked, eObjectDefine obDefine, WoolSpcAbility abil1, WoolSpcAbility abil2);

	~IWool();

public:
	eObjectDefine GetObjectDefine();

public:
	int m_Warmth;			// 보온성
	int m_Durability;		// 내구성
	int m_Aeration;			// 통기성
	int m_Price;			// 가격
	int m_UnlockPrice;		// 상점 해금 가격
	int m_Quantity;			// 수량
	bool m_isUnlocked;		//해금 여부
	
	WoolSpcAbility m_abil1;	//특수능력
	WoolSpcAbility m_abil2;
private:
	eObjectDefine m_objectDefine;
};
