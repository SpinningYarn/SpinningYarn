#pragma once
#include "Object.h"
using namespace std;

class StageManager;

class Credit : public Object
{
public:
	Credit(const int objectNum, string objectName);
	Credit(const int objectNum, const string& objectName, const double posX, const double posY);
	~Credit();

public:
	virtual void UpdateObject() override;
	virtual void RenderObject() override;
	
	int GetCredits();
	void AddCredits(int addt);
	void SetCredits(int credits);
	void UpdatePadding();

private:
	StageManager* m_pStageManager;

	static int m_credits;	//소지금

	float m_SrcX;			//pos가 없을때 하드코딩할 좌표
	float m_SrcY;			//쓸 일이 없었으면 좋겠다

	float m_DstX;			//pos부터 그릴 크기 좌표
	float m_DstY;

	float m_sizeX;			//크기
	float m_sizeY;			//그냥 넣어봄

	int m_padding;			//소지금 자릿수 늘어나면 같이 늘려줄 여백
};

