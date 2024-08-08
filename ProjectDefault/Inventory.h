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
/// 인벤토리
/// 상점에서 구매한 오브젝트들은 여기 표시될 예정
/// 방직기 돌리는 Scene에서만 보임 확정버튼 이후 lock기능 필요
/// 마지막 업데이트 : 2023.02.18 LKH
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

	//함수 주석은 CPP 참조
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
	D2DEngine* m_localD2D;			//멤버변수로 넣는게 맞는진 모르겠다.. 근데 GetInstance 매번하는거보단 나을듯
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
	bool m_isLocked;					//기능 활성화 여부
private:
	float m_containerSrcX;			//인벤토리 테두리 좌표
	float m_containerSrcY;
	float m_containerDstX;
	float m_containerDstY;

	float m_boxSrcX;					//인벤토리 내부 박스 좌표
	float m_boxSrcY;
	float m_boxDstX;
	float m_boxDstY;

	float m_boxIntervalX;				//박스 간격
	float m_boxIntervalY;	

	int m_boxAmount;					//박스 개수

	float m_leftButtonSrcX;			//왼쪽 페이징 버튼 좌표
	float m_leftButtonSrcY;
	float m_leftButtonDstX;
	float m_leftButtonDstY;

	float m_rightButtonSrcX;			//오른쪽 페이징 버튼 좌표
	float m_rightButtonSrcY;
	float m_rightButtonDstX;
	float m_rightButtonDstY;

private:
	vector<IWool*> m_itemList;		//인벤토리의 전체 아이템 목록
	vector<IWool*> m_showItemList;	//화면에 표시될 아이템 목록
	IWool* m_sendIWool;				//스탯 박스에 보내줄 객체
	IWool* m_sendIWool2;
	int m_curPage;					//현재 페이지	//1,2만 있는데 추가될 수도 있으니 일단 변수로 만들어놓음
	int m_maxPage;					//최대 페이지	//1,2만 있는데 추가될 수도 있으니 일단 변수로 만들어놓음
};

