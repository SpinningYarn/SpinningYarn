#pragma once
#include "Object.h"
#include "WoolStat.h"

class IWool;
class TestWool2;
class MouseManager;


class StatBox2 : public Object
{
public:
	StatBox2(const int objectNum, std::string objectName);
	StatBox2(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~StatBox2();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

	void PlusMinus2();
	void UpdateStat2(IWool* testWool);
	void EmptyStatBox();
	void SetEmpty();
	bool IsEmpty();

	//void GetStat2();
	//void GetImage2();

	void UnDo2();

	bool returnTestWool2;

	int MouseCount2;

	int targetWarmth2;
	int targetAbsoptivity2;
	int targetAeration2;
	int targetPrice2;
	int targetQuantity2;
	int targetCount2;

	eObjectDefine eOD;
	WoolSpcAbility m_spcAbil1;
	WoolSpcAbility m_spcAbil2;

	bool changeBox;
	bool InactivateButton2;

private:
	bool m_MouseClickOnce;
	MouseManager* m_pMouseManager;

	
};

