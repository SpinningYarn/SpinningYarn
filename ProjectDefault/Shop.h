#pragma once
#include "Object.h"
using namespace std;

class StageManager;

/// <summary>
/// 상점
/// 여기서 물건을 사면 인벤토리에 물품들이 업데이트 될거임
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

	//함수 주석은 CPP 참조
	void UnlockItems(Credit* crd, vector<IWool*> iwools, Inventory* inven = nullptr);
	void UpdateCredits(Credit* crd);
	void OpenStore();
	void CloseStore();
	void RotateIcon();
	bool GetActivated();

	void ResetInfos();
private:
	StageManager* m_pStageManager;

	float m_iconSrcX;				//아이콘 좌표
	float m_iconSrcY;
	float m_iconDstX;
	float m_iconDstY;

	float m_containerSrcX;			//테두리 박스 좌표
	float m_containerSrcY;
	float m_containerDstX;
	float m_containerDstY;

	float m_imageBoxSrcX;			//상점 내 이미지 박스 좌표
	float m_imageBoxSrcY;
	float m_imageBoxDstX;
	float m_imageBoxDstY;

	float m_imageSrcX;				//상점 내 이미지 좌표
	float m_imageSrcY;
	float m_imageDstX;
	float m_imageDstY;

	float m_statBoxSrcX;			//상점 내 스탯표시 박스 좌표
	float m_statBoxSrcY;
	float m_statBoxDstX;
	float m_statBoxDstY;

	float m_statTextSrcX;			//상점 내 스탯이 표시되는 좌표
	float m_statTextSrcY;
	float m_statTextDstX;
	float m_statTextDstY;

	float m_unlockButtonSrcX;		//해금버튼 좌표
	float m_unlockButtonSrcY;
	float m_unlockButtonDstX;
	float m_unlockButtonDstY;

	float m_closeButtonSrcX;		//상점 닫기 버튼 좌표
	float m_closeButtonSrcY;
	float m_closeButtonDstX;
	float m_closeButtonDstY;

	float m_boxIntervalX;			//박스 간격
	float m_boxIntervalY;

private:
	int m_productAmount;			//상점 품목 개수
	int m_curCredit;				//소지금과 비교하기 위해
	int m_1stPrice;					//해금 가격들	//해금가랑 사용가가 다르다
	int m_2ndPrice;
	int m_3rdPrice;
	int m_4thPrice;

	float m_rot;					//회전량
	bool m_rotStatus;
	bool m_isActivated;
private:
	bool m_firstItemUnlocked;		//아이템들 해금 여부
	bool m_secondItemUnlocked;
	bool m_thirdItemUnlocked;
	bool m_fourthItemUnlocked;
private:
	D2DEngine* m_localD2D;
	MouseManager* m_localMouse;
	bool m_mouseClickOnce;
};

