#pragma once
#include "Object.h"
using namespace std;

class D2DEngine;
class Shop;
class GameMenu;
class MouseManager;
class DragAndDrop;
class SceneManager;
class IWool;

/// <summary>
/// �κ��丮
/// �������� ������ ������Ʈ���� ���� ǥ�õ� ����
/// ������ ������ Scene������ ���� Ȯ����ư ���� lock��� �ʿ�
/// ������ ������Ʈ : 2023.02.18 LKH
/// </summary>
class Inventory : public Object
{
public:
	Inventory(const int objectNum, string objectName, SceneManager* pSceneManager);
	Inventory(const int objectNum, const string& objectName, SceneManager* pSceneManager, const double posX, const double posY);
	~Inventory();
public:
	virtual void UpdateObject() override;
	virtual void RenderObject() override;

	//�Լ� �ּ��� CPP ����
	void UpdateShowList();
	void UpdateStatBox();
	void UpdateStatBox2();
	void UpdateSendIWool(IWool* obj);
	void UpdateSendIWool2(IWool* obj);
	void EmptySendIWool();
	void EmptySendIWool2();
	IWool* GetSendIWool();
	IWool* GetSendIWool2();
	void GetCurrentScene();
	void PressButton();
	void AddObject(IWool* obj);
	int GetItemListSize();
	bool CheckItem(eObjectDefine eOD);
	void ResetInfos();
private:
	D2DEngine* m_localD2D;			//��������� �ִ°� �´��� �𸣰ڴ�.. �ٵ� GetInstance �Ź��ϴ°ź��� ������
	MouseManager* m_localMouse;
	DragAndDrop* m_DD1;
	DragAndDrop* m_DD2;
	DragAndDrop* m_DD3;
	DragAndDrop* m_DD4;
	DragAndDrop* m_DD5;
	DragAndDrop* m_DD6;
	Shop* m_pShop;
	GameMenu* m_pGameMenu;
	SceneManager* m_localSceneManager;
	bool m_mouseClickOnce;
private:
	int m_curScene;
	string m_strCurScene;
public:
	bool m_isLocked;					//��� Ȱ��ȭ ����
private:
	float m_containerSrcX;			//�κ��丮 �׵θ� ��ǥ
	float m_containerSrcY;
	float m_containerDstX;
	float m_containerDstY;

	float m_boxSrcX;					//�κ��丮 ���� �ڽ� ��ǥ
	float m_boxSrcY;
	float m_boxDstX;
	float m_boxDstY;

	float m_boxIntervalX;				//�ڽ� ����
	float m_boxIntervalY;	

	int m_boxAmount;					//�ڽ� ����

	float m_leftButtonSrcX;			//���� ����¡ ��ư ��ǥ
	float m_leftButtonSrcY;
	float m_leftButtonDstX;
	float m_leftButtonDstY;

	float m_rightButtonSrcX;			//������ ����¡ ��ư ��ǥ
	float m_rightButtonSrcY;
	float m_rightButtonDstX;
	float m_rightButtonDstY;

private:
	vector<IWool*> m_itemList;		//�κ��丮�� ��ü ������ ���
	vector<IWool*> m_showItemList;	//ȭ�鿡 ǥ�õ� ������ ���
	IWool* m_sendIWool;				//���� �ڽ��� ������ ��ü
	IWool* m_sendIWool2;
	int m_curPage;					//���� ������	//1,2�� �ִµ� �߰��� ���� ������ �ϴ� ������ ��������
	int m_maxPage;					//�ִ� ������	//1,2�� �ִµ� �߰��� ���� ������ �ϴ� ������ ��������
};

