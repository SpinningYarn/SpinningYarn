#pragma once
#include "IWool.h"
#include "Object.h"
#include "Common.h"

using namespace std;

class MouseManager;
class StatBox;

class TestWool2 : public IWool
{
public:
	TestWool2(const int& objectNum, std::string objectName);
	TestWool2(int objectNum, std::string objectName, double posX, double posY);
	~TestWool2();

public:
	virtual void UpdateObject() override;	// 업데이트
	virtual void RenderObject() override;	// 렌더


	bool SendImage2();
	bool returnItemBox2;

	bool SendStat2();
	bool returnStatBox2;


	bool mouseCount;
private:
	MouseManager* m_pMouseManager;

};
