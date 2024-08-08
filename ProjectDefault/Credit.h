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

	static int m_credits;	//������

	float m_SrcX;			//pos�� ������ �ϵ��ڵ��� ��ǥ
	float m_SrcY;			//�� ���� �������� ���ڴ�

	float m_DstX;			//pos���� �׸� ũ�� ��ǥ
	float m_DstY;

	float m_sizeX;			//ũ��
	float m_sizeY;			//�׳� �־

	int m_padding;			//������ �ڸ��� �þ�� ���� �÷��� ����
};

