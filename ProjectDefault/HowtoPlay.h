 #pragma once
 #include "Object.h"
 
 class MouseManager;
 
 /// <summary>
 /// ���� ��� ����
 /// </summary>
 class HowtoPlay : public Object
 {
 public:
 	HowtoPlay(const int& objectNum, std::string objectName);
 	HowtoPlay(const int objectNum, const std::string objectName, const double posX, const double posY);
 	~HowtoPlay();
 
 	virtual void UpdateObject() override;	// ������Ʈ
 	virtual void RenderObject() override;	// ����
 
    void DrawHowtoPlay();
 	void ExitWindow();
    void ChangePages();
    void Pages();

	bool ScreenOn;          //ȭ�鿡 ���� ����������

    int Count;              //������ ī��Ʈ 
 private:
 
 	MouseManager* m_pMouseManager;
 };
 
