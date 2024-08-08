#pragma once
#include "Object.h"
using namespace std;

class StageManager;

/// <summary>
/// ����
/// ���⼭ ������ ��� �κ��丮�� ��ǰ���� ������Ʈ �ɰ���
/// </summary>

class D2DEngine;
class MouseManager;
class Credit;
class Inventory;
class IWool;

class Shop : public Object
{
public:
	Shop(const int objectNum, string objectName);
	Shop(const int objectNum, const string& objectName, const double posX, const double posY);
	~Shop();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

	//�Լ� �ּ��� CPP ����
	void UnlockItems(Credit* crd, vector<IWool*> iwools, Inventory* inven = nullptr);
	void UpdateCredits(Credit* crd);
	void OpenStore();
	void CloseStore();
	void RotateIcon();
	bool GetActivated();

	void ResetInfos();
private:
	StageManager* m_pStageManager;

	float m_iconSrcX;				//������ ��ǥ
	float m_iconSrcY;
	float m_iconDstX;
	float m_iconDstY;

	float m_containerSrcX;			//�׵θ� �ڽ� ��ǥ
	float m_containerSrcY;
	float m_containerDstX;
	float m_containerDstY;

	float m_imageBoxSrcX;			//���� �� �̹��� �ڽ� ��ǥ
	float m_imageBoxSrcY;
	float m_imageBoxDstX;
	float m_imageBoxDstY;

	float m_imageSrcX;				//���� �� �̹��� ��ǥ
	float m_imageSrcY;
	float m_imageDstX;
	float m_imageDstY;

	float m_statBoxSrcX;			//���� �� ����ǥ�� �ڽ� ��ǥ
	float m_statBoxSrcY;
	float m_statBoxDstX;
	float m_statBoxDstY;

	float m_statTextSrcX;			//���� �� ������ ǥ�õǴ� ��ǥ
	float m_statTextSrcY;
	float m_statTextDstX;
	float m_statTextDstY;

	float m_unlockButtonSrcX;		//�رݹ�ư ��ǥ
	float m_unlockButtonSrcY;
	float m_unlockButtonDstX;
	float m_unlockButtonDstY;

	float m_closeButtonSrcX;		//���� �ݱ� ��ư ��ǥ
	float m_closeButtonSrcY;
	float m_closeButtonDstX;
	float m_closeButtonDstY;

	float m_boxIntervalX;			//�ڽ� ����
	float m_boxIntervalY;

private:
	int m_productAmount;			//���� ǰ�� ����
	int m_curCredit;				//�����ݰ� ���ϱ� ����
	int m_1stPrice;					//�ر� ���ݵ�	//�رݰ��� ��밡�� �ٸ���
	int m_2ndPrice;
	int m_3rdPrice;
	int m_4thPrice;

	float m_rot;					//ȸ����
	bool m_rotStatus;
	bool m_isActivated;
private:
	bool m_firstItemUnlocked;		//�����۵� �ر� ����
	bool m_secondItemUnlocked;
	bool m_thirdItemUnlocked;
	bool m_fourthItemUnlocked;
private:
	D2DEngine* m_localD2D;
	MouseManager* m_localMouse;
	bool m_mouseClickOnce;
};

