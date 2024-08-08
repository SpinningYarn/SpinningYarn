#pragma once
//#include "WoolStat.h"
#include "IWool.h"
#include "Object.h"
#include "Common.h"


using namespace std;

class MouseManager;


class TestWool : public IWool
{
public:
	TestWool(const int& objectNum, std::string objectName);
	TestWool(int objectNum, std::string objectName, double posX, double posY);
	~TestWool();

public:
	virtual void UpdateObject() override;	// ������Ʈ
	virtual void RenderObject() override;	// ����
	
	
	bool SendImage();
	bool returnItemBox;

	bool SendStat();
	bool returnStatBox;


	bool mouseCount;
private:
	MouseManager* m_pMouseManager;
};

