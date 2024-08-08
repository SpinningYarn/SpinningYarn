#pragma once
#include "Object.h"

const int SPACE = 5;

/// <summary>
/// 
/// ���� �ý��� ������ ù ���� �� �����ϱ� ��ư
/// ����̰� ���� �� �� �����ϱ� ��ư�� Ȱ��ȭ ��
/// Ȱ��ȭ �� ���� ���� Ÿ�̸Ӱ� ���� ������ Ÿ�̸Ӱ� �帣�� ��
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

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�	
	bool RetryButtonClick();					// �����̽��ٰ� ���ȴ����� ����
	bool GameStartButtonClick(Dantto* p_Dantto);// ���� ���� ��ư ���ȴ����� ����
	bool GetDrawFlag();
	void SetDrawFlag(bool OX);

private:
	int m_ButtonSizeX;
	int m_ButtonSizeY;
	bool m_DrawFlag;
};
