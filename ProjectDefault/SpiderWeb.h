#pragma once
#include "IWool.h"
#include "Object.h"
#include "Common.h"

using namespace std;

class MouseManager;


class SpiderWeb : public IWool
{
public:
	SpiderWeb(const int& objectNum, std::string objectName);
	SpiderWeb(int objectNum, std::string objectName, double posX, double posY);
	~SpiderWeb();

public:
	virtual void UpdateObject() override;	// 업데이트
	virtual void RenderObject() override;	// 렌더


	bool SendImage();
	bool returnItemBox;

	bool SendStat();
	bool returnStatBox;


	bool mouseCount;
private:
	MouseManager* m_pMouseManager;
};

