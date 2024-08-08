#pragma once
#include "Object.h"

/// �뷱�� ���� �� ���� ����
const double DATUM_START_TIMER = 3;			// ���� ��� �ð����� ���� ���۱����� Ÿ�̸�
const double DATUM_END_TIMER = 0.5;			// ���� ������ ī��Ʈ �Ǳ��� �����ð�
const double DATUM_REPLAY_TIMER = 3;		// ����۽� Ÿ�̸�
const double DATUM_GAME_SPEED = 100;		// ���� ���� �ӵ�
const double SPEED_INCREASE_PERCENT = 10;	// �������� �þ�� ���� ���̵� ��� %
const int INTERVAL = 20;

class AnswerBoard;							// ������ ���漱��
class Scene_Knitting;						// �� ���漱��
class DrawBoard;

/// <summary>
/// 
/// ���� �ý��� �̴ϰ��ӿ��� �������� �Ǵ� Ŭ����
/// ������������ ������ �ӵ��� ��ǥ�������� �����̸�
/// ��ǥ������ �����ϸ� �ٽ� ������������ ���ƿ��� ����
/// �߰��� ���� ������ ���� �ݺ�Ƚ���� �޶���
/// 
/// 2022.02.11 YJH
/// </summary>

class DatumPoint : public Object
{
public:
	DatumPoint(const int objectNum, std::string objectName);
	DatumPoint(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~DatumPoint();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�	
	int GetSize();								// ������ ��������
	void SetDrawX(double move);					// ��� X��ǥ ����
	double GetDrawX();							// ��� X��ǥ ��������
	double GetDrawY();							// ��� y��ǥ ��������
	void UpdateDrawPosition();					// ��� ��ǥ ������Ʈ
	int GetCount();								// ���� ī��Ʈ ��������
	int GetGoalCount();							// ��ǥġ ��������
	void SetGoalCount(int goal);				// ��ǥġ ����
	void BasicMove();							// ������ �����̴� ����
	void InitialzieGame(Scene_Knitting* p_Knitting, AnswerBoard* p_AnswerBoard, AnswerBoard* p_FirstBoard, DrawBoard* p_DrawBoard);	// �ٽ��ϱ� ������ �ʱ�ȭ
	double GetDatumX();							// ������ x��ǥ ��������
	void SetDatumX(double num);					// X��ǥ ����
	void SetStartX(double num);				// ������ ����
	void SetReverseX(double move);				// ������ ����
	bool GetWaitState();						// ��⿩�� ������
	void Initialize();
	void SetStartTimer(double time);
	void SetStartFlag(bool OX);
	bool GetStartFlag();
	void SetOriginX();
	void SetClearFlag(bool OX);

private:
	double m_DatumSpeed;						// ������ �ӵ�
	double m_DatumX;							// ������ ���� ��ġ (X ��ǥ)
	double m_DatumY;							// ������ ���� ��ġ (Y ��ǥ)
	double m_PrintXposition;					// �׸��� ���� x��ǥ
	double m_PrintYposition;					// �׸��� ���� y��ǥ
	double m_Size;									// ũ��
	double m_StartTimer;						// ���� ��� �ð��� �궧 ����� Ÿ�̸� -> ���� �� ���� ���۶������� �ð�
	double m_EndTimer;							// ������ ��� �ð��� �궧 ����� Ÿ�̸� -> ���� ���� �� �� ���Ӱ��� ������ �ð�
	int m_StartX;								// ������ �����
	int m_ReverseX;								// ������ �����	

	bool m_OnDraw;								// True�� ��쿡�� �׷���
	int m_Count;								// ���� Ƚ��
	int m_GoalCount;							// ��ǥ ���� Ƚ�� (�������� 4~7�߿� ������)
	bool m_Retry;								// �絵�� ����
	bool m_Wait;								// ���� ������ ���� �ܰ� ����� ����
	bool m_StartFlag;							// ���� ����
	bool m_ClearFlag;
};

