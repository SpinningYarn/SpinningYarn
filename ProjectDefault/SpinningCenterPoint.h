#pragma once
#include "Object.h"
#include <functional>

class MouseManager;
class SpinningGaugeManager;
class DragAndDrop;
class StageManager;
class SpinningGaugBall;

/// <summary>
/// ���� ȸ�� �̴ϰ��ӿ��� ������ ���߾��� �Ǵ� Ŭ����
/// Mouse Button DOWN �� ���콺�� ȸ������
/// ��ǥ������ ���޽�Ű�� ����
/// 
/// ���� Object�� Render�� �ƴ� ���� Object�� �߽���ǥ�� ��� ó���� ����ϴ� Class
/// 
/// 2023.02.07 Kimdowoo
/// </summary>
class SpinningCenterPoint : public Object
{
public:
	SpinningCenterPoint(const int objectNum, std::string objectName);
	SpinningCenterPoint(const int objectNum, std::string objectName, const double posX, const double posY);
	~SpinningCenterPoint();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ
	virtual void RenderObject() override;		// ��ü���� �׸���

private:
	MouseManager* m_pMouseManager;
	StageManager* m_pStageManager;
	SpinningGaugeManager* m_pSpinningGaugeManager;

	DragAndDrop* m_pDragAndDrop1;
	DragAndDrop* m_pDragAndDrop2;
	DragAndDrop* m_pDragAndDrop3;

	/// ������ǥ
	double m_WorldPosX;
	double m_WorldPosY;

	/// �ǽð� ���콺 ��ǥ
	float m_MousePosX;
	float m_MousePosY;

	/// �����ǥ
	int m_LocalPosX;
	int m_LocalPosY;


	/// Test�� ���� ������ �ʿ�� ����
	// object ��ġ ����
	bool m_ObjectTouchState;		// object�� ��ġ�ߴ°�?
	bool m_ObjectMisTouchState;		// object�� �߸� �����°�?
	float m_ObjectAlphaValue;		// object �����ġ 0 ~ 1

	// object �ʴ� ��� ����ϴ����� ���
	float m_AccTime;
	int m_CurFrame;

	// ���ʰ� ���ư��� ������ �Ǵ�
	bool m_IsSpinningRotate;

private:
	/// ��ǥ
	// �׸� ũ��
	int m_ObjectSizeX;
	int m_ObjectSizeY;

	// object �߽� ��ġ
	double m_PosX;
	double m_PosY;

	// Mouse Pos
	int m_CurMousePosX;
	int m_CurMousePosY;
	int m_PevMousePosX;
	int m_PevMousePosY;
	bool m_MousePosState;

	// �߽ɿ��� �� ������ R��ŭ ȸ������ �� P' ��ǥ
	double m_NextPosX;
	double m_NextPosY;

	// Math�� ����� ����
	const double PI = 3.1415f;
	double m_Sin;
	double m_Cos;
	double m_Tan;
	double m_Radian;
	double m_Degree;	// ȸ������
	double m_Speed;		// ȸ�� �ӵ�

	// ȸ�� �� �ѹ��� �� ī����
	int m_CountRotate;

	// ù Ŭ�� �� ���� ����
	bool m_IsSpinningWheelRange;
	bool m_OneSpinningWheelRange; // �ѹ� Ŭ���� ���� �� ������ų ����

private:
	/// <summary>
	/// ȸ�� ��ǥ ����� ���� �Լ�
	/// </summary>
	void Rotate();
	void Radian();

public:
	/// �����ǥ ��ȯ
	double GetPosX();
	double GetPosY();

	// Ŭ�� �� �̺�Ʈ �߻� �Լ� (test �Լ�)
	void EventDraw();
	void StartEvent();
	void EndEvent();
	void ExceptionEvent();

	// ������ ȸ���ϴ����� ��ȯ�ϴ� �Լ�
	bool IsSpinningRotate();

	//ȸ������ ��ȯ�ϴ� �Լ�
	double GetDegree();
private:
	// �����ǥ ���
	int LocalPosX();
	int LocalPosY();
};