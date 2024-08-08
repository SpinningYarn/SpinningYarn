#pragma once
#include "Object.h"

/// 밸런스 조절 시 변경 사항
const double DATUM_START_TIMER = 3;			// 게임 대기 시간부터 게임 시작까지의 타이머
const double DATUM_END_TIMER = 0.5;			// 게임 끝나고 카운트 되기전 유예시간
const double DATUM_REPLAY_TIMER = 3;		// 재시작시 타이머
const double DATUM_GAME_SPEED = 100;		// 게임 진행 속도
const double SPEED_INCREASE_PERCENT = 10;	// 스테이지 늘어날때 마다 난이도 상승 %
const int INTERVAL = 20;

class AnswerBoard;							// 기준점 전방선언
class Scene_Knitting;						// 씬 전방선언
class DrawBoard;

/// <summary>
/// 
/// 직조 시스템 미니게임에서 기준점이 되는 클래스
/// 시작지점에서 일정한 속도로 목표지점까지 움직이며
/// 목표지점에 도달하면 다시 시작지점으로 돌아오는 형태
/// 뜨개질 도안 종류에 따라 반복횟수가 달라짐
/// 
/// 2022.02.11 YJH
/// </summary>

class DatumPoint : public Object
{
public:
	DatumPoint(const int objectNum, std::string objectName);
	DatumPoint(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~DatumPoint();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩	
	int GetSize();								// 사이즈 가져오기
	void SetDrawX(double move);					// 출력 X좌표 설정
	double GetDrawX();							// 출력 X좌표 가져오기
	double GetDrawY();							// 출력 y좌표 가져오기
	void UpdateDrawPosition();					// 출력 좌표 업데이트
	int GetCount();								// 현재 카운트 가져오기
	int GetGoalCount();							// 목표치 가져오기
	void SetGoalCount(int goal);				// 목표치 설정
	void BasicMove();							// 기준점 움직이는 로직
	void InitialzieGame(Scene_Knitting* p_Knitting, AnswerBoard* p_AnswerBoard, AnswerBoard* p_FirstBoard, DrawBoard* p_DrawBoard);	// 다시하기 누를시 초기화
	double GetDatumX();							// 기준점 x좌표 가져오기
	void SetDatumX(double num);					// X좌표 설정
	void SetStartX(double num);				// 시작점 설정
	void SetReverseX(double move);				// 시작점 설정
	bool GetWaitState();						// 대기여부 가져옴
	void Initialize();
	void SetStartTimer(double time);
	void SetStartFlag(bool OX);
	bool GetStartFlag();
	void SetOriginX();
	void SetClearFlag(bool OX);

private:
	double m_DatumSpeed;						// 기준점 속도
	double m_DatumX;							// 기준점 시작 위치 (X 좌표)
	double m_DatumY;							// 기준점 시작 위치 (Y 좌표)
	double m_PrintXposition;					// 그리기 위한 x좌표
	double m_PrintYposition;					// 그리기 위한 y좌표
	double m_Size;									// 크기
	double m_StartTimer;						// 시작 대기 시간을 잴때 사용할 타이머 -> 입장 후 게임 시작때까지의 시간
	double m_EndTimer;							// 끝나고 대기 시간을 잴때 사용할 타이머 -> 게임 진행 중 간 게임간의 간격의 시간
	int m_StartX;								// 정방향 출발점
	int m_ReverseX;								// 역방향 출발점	

	bool m_OnDraw;								// True일 경우에만 그려줌
	int m_Count;								// 시행 횟수
	int m_GoalCount;							// 목표 시행 횟수 (랜덤으로 4~7중에 정해짐)
	bool m_Retry;								// 재도전 여부
	bool m_Wait;								// 게임 내에서 다음 단계 대기중 여부
	bool m_StartFlag;							// 시작 여부
	bool m_ClearFlag;
};

