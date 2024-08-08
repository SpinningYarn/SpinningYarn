#pragma once
#include "Object.h"

const int SPACE = 5;

/// <summary>
/// 
/// 직조 시스템 내에서 첫 진입 시 시작하기 버튼
/// 고양이가 입장 한 후 시작하기 버튼이 활성화 됨
/// 활성화 된 이후 시작 타이머가 게임 내부의 타이머가 흐르게 됨
/// 
/// 2022.02.23 YJH
/// </summary>

class Dantto;

class StartButton : public Object
{
public:
	StartButton(const int objectNum, std::string objectName);
	StartButton(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~StartButton();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩	
	bool RetryButtonClick();					// 스페이스바가 눌렸는지를 리턴
	bool GameStartButtonClick(Dantto* p_Dantto);// 게임 시작 버튼 눌렸는지를 리턴
	bool GetDrawFlag();
	void SetDrawFlag(bool OX);

private:
	int m_ButtonSizeX;
	int m_ButtonSizeY;
	bool m_DrawFlag;
};
