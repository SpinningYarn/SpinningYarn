#pragma once
#include "Object.h"

/// �뷱�� ���� �� ���� ����
const int ATTACK = 15;
const int WARNING = 12;
const double MOVESPEED = 400;		// �ӵ�
const int MOVESIZE = 80;			// �̵� �Ÿ�
const double MOVEGOAL = 8;			// �� �̵� Ƚ�� -> ¦���� �ؾ���
const double INCREASE_PERCENT = 10;	// �������� �þ�� ���� ���̵� ��� %
const double ENTERTIME = 2.8;		// �ִϸ��̼� �ҿ� �ð� (��Ȳ���� ���� �� �ٿ��� �� ����)

/// <summary>
/// 
/// �����
/// �ΰ��� �ִϸ��̼��� �����ϴµ� 
/// 1. �׳� ù��° ������ ������
/// 2. �߰��� ������ 15�ʸ��� ������ ������ ����
/// 15�ʿ��� 2~3�� ���� ���������� �� ����
/// ���������� �ٰ����� true�� �Ǵ� �÷��׿�
/// ���ݽñⰡ �Ǹ� true�� �Ǵ� �÷��׸� ������ ����
/// 
/// 2022.02.16 YJH
/// </summary>

class Needle;
class AnswerBoard;
class DatumPoint;
class ResultProduct;
class DrawBoard;

class Dantto : public Object
{
public:
	Dantto(const int objectNum, std::string objectName);
	Dantto(const int objectNum, const std::string & objectName, const double posX, const double posY);
	~Dantto();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

	void RenderDantto();

	void Initialize(Needle* p_Needle, AnswerBoard* p_Board, DatumPoint* p_Datum, ResultProduct* P_Result, DrawBoard* p_DrawBoard);	// �ʱ�ȭ

	bool GetWarningFlag();
	void SetWarningFlag(bool OX);

	bool GetAttackFlag();
	void SetAttackFlag(bool OX);

	void Warning();					// ���� ����, ���� ����
	void Attack();					// ����
	void Attack2();

	bool GetEnterFlag();

private:
	bool m_1stScene;				// �� 1���� �ƴ��� 
	bool m_WarningFlag;				// �������� �˷��� ����
	bool m_AttackFlag;				// ���� ����
	double m_Timer;					// �ð� ������ Ÿ�̸�
	double m_AttackTimer;			// ���� �� Ÿ�̸�
	double m_AttackMove;			// ���� �� ������
	bool m_MoveLeft;				// �������� �̵��ϴ��� ����
	bool m_MoveStop;				// ���ߴ��� ����
	double m_MoveCount;				// ���� ������ Ƚ��
	double m_MoveDistance;			// ������ �Ÿ�
	bool m_ClickMiss;				// Ŭ�� ��Ÿ ������
	double m_MoveSize;
	double m_PrevMove;
	double m_Size;
	bool m_PlayAnimation;
	double m_MoveSpeed;
	bool m_Enter;
	double m_EnterTimer;
	int m_AttackX;
	bool m_Attack1Enterflag;
	bool m_Attack2Enterflag;
	bool m_Attack3Enterflag;
	bool m_Attack4Enterflag;
	double m_OutTimer;
	double m_FinalTimer;
	bool m_Attack2Flag;
	bool m_StandOndraw;
	int m_Rcount;

	Needle* m_pNeedle;
	DatumPoint* m_pDatum;
	ResultProduct* m_pResult;
	DrawBoard* m_pDrawBaord;
	
	AnswerBoard* m_pBoard1;
	AnswerBoard* m_pBoard2;
	AnswerBoard* m_pBoard3;
	AnswerBoard* m_pBoard4;
	AnswerBoard* m_pBoard5;
	AnswerBoard* m_pBoard6;
	AnswerBoard* m_pBoard7;
	AnswerBoard* m_pBoard8;
};