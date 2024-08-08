 #pragma once
 #include "Object.h"
 
 class MouseManager;
 
 /// <summary>
 /// 게임 방법 설명
 /// </summary>
 class HowtoPlay : public Object
 {
 public:
 	HowtoPlay(const int& objectNum, std::string objectName);
 	HowtoPlay(const int objectNum, const std::string objectName, const double posX, const double posY);
 	~HowtoPlay();
 
 	virtual void UpdateObject() override;	// 업데이트
 	virtual void RenderObject() override;	// 렌더
 
    void DrawHowtoPlay();
 	void ExitWindow();
    void ChangePages();
    void Pages();

	bool ScreenOn;          //화면에 뭐든 켜져있을떄

    int Count;              //페이지 카운트 
 private:
 
 	MouseManager* m_pMouseManager;
 };
 
