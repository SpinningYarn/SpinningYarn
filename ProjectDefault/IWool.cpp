#include "IWool.h"

class Object;

IWool::IWool(const int& objectNum, std::string objectName,
	int warmth, int durability, int aeration,
	int price, int unlockPrice, int quantity,
	bool isUnlocked, eObjectDefine obDefine, WoolSpcAbility abil1, WoolSpcAbility abil2)
	:Object(objectNum, objectName),
	m_Warmth(warmth),
	m_Durability(durability),
	m_Aeration(aeration),
	m_Price(price),
	m_UnlockPrice(unlockPrice),
	m_Quantity(quantity),
	m_isUnlocked(isUnlocked),
	m_objectDefine(obDefine),
	m_abil1(abil1),
	m_abil2(abil2)
{
	
}

IWool::IWool(int objectNum, std::string objectName, double posX, double posY,
	int warmth, int durability, int aeration,
	int price, int unlockPrice, int quantity,
	bool isUnlocked, eObjectDefine obDefine, WoolSpcAbility abil1, WoolSpcAbility abil2)
	:Object(objectNum, objectName, posX, posY),
	m_Warmth(warmth),
	m_Durability(durability),
	m_Aeration(aeration),
	m_Price(price),
	m_UnlockPrice(unlockPrice),
	m_Quantity(quantity),
	m_isUnlocked(isUnlocked),
	m_objectDefine(obDefine),
	m_abil1(abil1),
	m_abil2(abil2)
{
}

IWool::~IWool()
{
}

eObjectDefine IWool::GetObjectDefine()
{
	return m_objectDefine;
}

