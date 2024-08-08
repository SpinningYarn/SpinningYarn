#pragma once
#include "Object.h"
#include "WoolStat.h"

class IWool;
class TestWool;
class MouseManager;

class StatBox : public Object
{
public:
	StatBox(const int objectNum, std::string objectName);
	StatBox(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~StatBox();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;


	void PlusMinus();
	void UpdateStat(IWool* testWool);
	void EmptyStatBox();
	void SetEmpty();
	bool IsEmpty();

	void Remover();

	//void GetStat();
	//void GetImage();

	void UnDo();


	bool returnTestWool;

	int MouseCount;

	int targetWarmth;
	int targetAbsoptivity;
	int targetAeration;
	int targetPrice;
	int targetQuantity;
	int targetCount;

	eObjectDefine eOD;
	WoolSpcAbility m_spcAbil1;
	WoolSpcAbility m_spcAbil2;

	// Scene으로 가져가는 예외체크
	bool changeBox;
	bool StatBoxCheck;

	bool InactivateButton;

private:
	bool returnWoolStat;
	bool m_MouseClickOnce;

	IWool* m_dataIwool;

	MouseManager* m_pMouseManager;
	
};

