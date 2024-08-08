#pragma once
#include "Object.h"
#include <functional>

class MouseManager;
class SpinningGaugeManager;
class DragAndDrop;
class StageManager;
class SpinningGaugBall;

/// <summary>
/// 물레 회전 미니게임에서 물레의 정중앙이 되는 클래스
/// Mouse Button DOWN 시 마우스로 회전시켜
/// 목표지점에 도달시키는 형태
/// 
/// 물레 Object의 Render가 아닌 물레 Object의 중심좌표와 계산 처리를 담당하는 Class
/// 
/// 2023.02.07 Kimdowoo
/// </summary>
class SpinningCenterPoint : public Object
{
public:
	SpinningCenterPoint(const int objectNum, std::string objectName);
	SpinningCenterPoint(const int objectNum, std::string objectName, const double posX, const double posY);
	~SpinningCenterPoint();

	virtual void UpdateObject() override;		// 객체에서 업데이트
	virtual void RenderObject() override;		// 객체에서 그리기

private:
	MouseManager* m_pMouseManager;
	StageManager* m_pStageManager;
	SpinningGaugeManager* m_pSpinningGaugeManager;

	DragAndDrop* m_pDragAndDrop1;
	DragAndDrop* m_pDragAndDrop2;
	DragAndDrop* m_pDragAndDrop3;

	/// 절대좌표
	double m_WorldPosX;
	double m_WorldPosY;

	/// 실시간 마우스 좌표
	float m_MousePosX;
	float m_MousePosY;

	/// 상대좌표
	int m_LocalPosX;
	int m_LocalPosY;


	/// Test를 위한 변수들 필요시 삭제
	// object 터치 상태
	bool m_ObjectTouchState;		// object를 터치했는가?
	bool m_ObjectMisTouchState;		// object를 잘못 눌렀는가?
	float m_ObjectAlphaValue;		// object 투명수치 0 ~ 1

	// object 초당 몇번 출력하는지를 당담
	float m_AccTime;
	int m_CurFrame;

	// 물례가 돌아가는 중인지 판단
	bool m_IsSpinningRotate;

private:
	/// 좌표
	// 그림 크기
	int m_ObjectSizeX;
	int m_ObjectSizeY;

	// object 중심 위치
	double m_PosX;
	double m_PosY;

	// Mouse Pos
	int m_CurMousePosX;
	int m_CurMousePosY;
	int m_PevMousePosX;
	int m_PevMousePosY;
	bool m_MousePosState;

	// 중심에서 끝 점에서 R만큼 회전했을 때 P' 좌표
	double m_NextPosX;
	double m_NextPosY;

	// Math에 사용할 변수
	const double PI = 3.1415f;
	double m_Sin;
	double m_Cos;
	double m_Tan;
	double m_Radian;
	double m_Degree;	// 회전각도
	double m_Speed;		// 회전 속도

	// 회전 시 한바퀴 당 카운팅
	int m_CountRotate;

	// 첫 클릭 전 범위 지정
	bool m_IsSpinningWheelRange;
	bool m_OneSpinningWheelRange; // 한번 클릭한 다음 쭉 유지시킬 변수

private:
	/// <summary>
	/// 회전 좌표 계산을 위한 함수
	/// </summary>
	void Rotate();
	void Radian();

public:
	/// 상대좌표 반환
	double GetPosX();
	double GetPosY();

	// 클릭 시 이벤트 발생 함수 (test 함수)
	void EventDraw();
	void StartEvent();
	void EndEvent();
	void ExceptionEvent();

	// 물레가 회전하는지를 반환하는 함수
	bool IsSpinningRotate();

	//회전값을 반환하는 함수
	double GetDegree();
private:
	// 상대좌표 계산
	int LocalPosX();
	int LocalPosY();
};