#pragma once
#include "Object.h"

/// 밸런스 조절 시 변경 사항
const int ATTACK = 15;
const int WARNING = 12;
const double MOVESPEED = 400;		// 속도
const int MOVESIZE = 80;			// 이동 거리
const double MOVEGOAL = 8;			// 총 이동 횟수 -> 짝수로 해야함
const double INCREASE_PERCENT = 10;	// 스테이지 늘어날때 마다 난이도 상승 %
const double ENTERTIME = 2.8;		// 애니메이션 소요 시간 (상황봐서 조금 더 줄여야 될 수도)

/// <summary>
/// 
/// 고양이
/// 두가지 애니메이션이 존재하는데 
/// 1. 그냥 첫번째 씬에서 등장함
/// 2. 뜨개질 씬에서 15초마다 게임을 방해할 예정
/// 15초에서 2~3초 전에 전조증상을 줄 예정
/// 전조증상이 다가오면 true가 되는 플래그와
/// 공격시기가 되면 true가 되는 플래그를 리턴할 예정
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

	void Initialize(Needle* p_Needle, AnswerBoard* p_Board, DatumPoint* p_Datum, ResultProduct* P_Result, DrawBoard* p_DrawBoard);	// 초기화

	bool GetWarningFlag();
	void SetWarningFlag(bool OX);

	bool GetAttackFlag();
	void SetAttackFlag(bool OX);

	void Warning();					// 전조 증상, 공격 조건
	void Attack();					// 공격
	void Attack2();

	bool GetEnterFlag();

private:
	bool m_1stScene;				// 씬 1인지 아닌지 
	bool m_WarningFlag;				// 전조증상 알려줄 예정
	bool m_AttackFlag;				// 실제 공격
	double m_Timer;					// 시간 측정용 타이머
	double m_AttackTimer;			// 공격 중 타이머
	double m_AttackMove;			// 공격 시 움직임
	bool m_MoveLeft;				// 왼쪽으로 이동하는지 여부
	bool m_MoveStop;				// 멈추는지 여부
	double m_MoveCount;				// 현재 움직인 횟수
	double m_MoveDistance;			// 움직일 거리
	bool m_ClickMiss;				// 클릭 연타 방지용
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