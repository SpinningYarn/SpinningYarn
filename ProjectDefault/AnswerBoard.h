#pragma once
#include "Object.h"

/// <summary>
/// 
/// 직조 시스템 미니게임에서 정답판이 되는 클래스
/// 뜨개질 도안에 따라 키보드,위,아래,왼,오른쪽 키가 배정되며 
/// 정답판에 기준점이 위치할 때 정해진 키보드를 타이밍에 맞춰 눌러
/// 정답 시 정답 카운트 올라감 (한 칸에 최대 한 번)
/// 실패 시 정답 카운트 떨어짐 (한 칸에 최대 한 번)
/// 
/// 2022.02.14 YJH
/// </summary>

class AnswerBoard : public Object
{
public:
	AnswerBoard(const int objectNum, std::string objectName);
	AnswerBoard(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~AnswerBoard();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩	
	void DrawAnswer(int answer);
	double GetXpos();							// 객체의 x값 가져옴
	void SetXpos(double Xposition);				// 객체의 x값 설정
	double GetXposPlusSize();					// 객체의 x값+size를 가져옴

	void SetAnswer(int AnswerBoxNum, int book[7][8]);// 정답값 설정
	int GetAnswerCount();						// 정답값 리턴
	void PlusAnswerCount();						// 정답값 올려줌
	void SetAnswerGoal(int goal);				// 정답값 설정
	int GetAnswerGoal();						// 정답값 리턴
	bool GetQuestionActivate();					// 문제 활성화 여부 리턴
	void SetQuestionActivate(bool OX);			// 문제 활성화 설정
	bool GetCountFlag();						// 정답 체크여부 가져오기
	void SetCountFlag(bool OX);					// 정답 체크여부 변경
	bool GetWrongCountFlag();					// 오답 체크여부 가져오기
	void SetWrongCountFlag(bool OX);			// 정답 체크여부 변경
	bool GetSkipFlag();							// 스킵 정답여부 가져오기
	void SetSkipFlag(bool OX);					// 스킵 정답여부 변경
	int GetOX();								// 정답여부 가져오기
	void SetOX(int num);						// 정답여부 설정
	bool GetXdrawFlag();						// X 출력을 위한 플래그 가져오기
	void SetXdrawFlag(int index, bool OX);		// X 출력을 위한 플래그 설정
	void SetNextBoard(AnswerBoard* p_NextBoard);// 다음 노드 설정
	void FinishGame();
	AnswerBoard* GetNextBoard();				// 다음 노드 가져오기
	void GetDatumPoint(int NowCount);
	int GetIndex();
	void SetIndex(int num);


private:
	int m_BoardSize;
	int m_Answer[7];
	int m_AnswerCount;							// 맞춘 정답 횟수
	int m_AnswerGoal;							// 목표 정답 횟수
	bool m_QuesitonActivate;					// 문제 활성화
	bool m_CountFlag;							// 정답 한번만 체크 가능하도록
	bool m_WrongFlag;							// 오답 한번만 되도록
	bool m_SkipFlag;							// 스킵 칸 정답처리
	int m_OX;									// 정답 여부
	bool m_XdrawFlag[7];						// 틀렸을 때 완성품 위에 X출력을 위함
	AnswerBoard* m_pNextBoard;					// 다음을 가르키는 노드
	int m_NowCount;
	int m_Index;
};


