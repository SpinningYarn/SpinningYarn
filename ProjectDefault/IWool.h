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
	int m_Warmth;			// ���¼�
	int m_Durability;		// ������
	int m_Aeration;			// ��⼺
	int m_Price;			// ����
	int m_UnlockPrice;		// ���� �ر� ����
	int m_Quantity;			// ����
	bool m_isUnlocked;		//�ر� ����
	
	WoolSpcAbility m_abil1;	//Ư���ɷ�
	WoolSpcAbility m_abil2;
private:
	eObjectDefine m_objectDefine;
};
