#pragma once
#include "IWool.h"
#include "Object.h"
#include "Common.h"


using namespace std;

class MouseManager;


class Burlap : public IWool
{
public:
	Burlap(const int& objectNum, std::string objectName);
	Burlap(int objectNum, std::string objectName, double posX, double posY);
	~Burlap();

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

