#pragma once
#include "Object.h"

class AnswerBoard;
class DatumPoint;

/// <summary>
/// 
/// 출력물 위에 x를 표시하기 위한 판
/// 
/// 2022.02.21 YJH
/// </summary>

class DrawBoard : public Object
{
public:
	DrawBoard(const int objectNum, std::string objectName);
	DrawBoard(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~DrawBoard();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩	
	void Initialize(AnswerBoard* m_pBoard, DatumPoint* p_Datum);
	void SetXflagArray(int count);
	void InitializeFlagArray(int count, int index, bool OX, int Xpos, int Ypos);
	void MoveXflagPos(double move);
	void OriginXflagPos();
	
private:
	AnswerBoard* m_PBoard1st;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard2nd;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard3rd;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard4th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard5th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard6th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard7th;		// 이전 정답칸 저장을 위한 변수
	AnswerBoard* m_pBoard8th;		// 이전 정답칸 저장을 위한 변수
	DatumPoint* m_pDatum;

	// Flag 배열을 위한 중첩 클래스

	class XFlag
	{
	public:
		XFlag() : xFlag(false), Xpos(0), Ypos(0) {}
		bool xFlag;
		double Xpos;
		double Ypos;
	};

	XFlag m_FlagArray[7][8];
};

