#pragma once
#include "IWool.h"
#include "Object.h"
#include "Common.h"


using namespace std;

class MouseManager;


class Cotton : public IWool
{
public:
	Cotton(const int& objectNum, std::string objectName);
	Cotton(int objectNum, std::string objectName, double posX, double posY);
	~Cotton();

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

