#pragma once
#include "Object.h"

class AnswerBoard;
class DatumPoint;

/// <summary>
/// 
/// ��¹� ���� x�� ǥ���ϱ� ���� ��
/// 
/// 2022.02.21 YJH
/// </summary>

class DrawBoard : public Object
{
public:
	DrawBoard(const int objectNum, std::string objectName);
	DrawBoard(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~DrawBoard();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�	
	void Initialize(AnswerBoard* m_pBoard, DatumPoint* p_Datum);
	void SetXflagArray(int count);
	void InitializeFlagArray(int count, int index, bool OX, int Xpos, int Ypos);
	void MoveXflagPos(double move);
	void OriginXflagPos();
	
private:
	AnswerBoard* m_PBoard1st;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard2nd;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard3rd;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard4th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard5th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard6th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard7th;		// ���� ����ĭ ������ ���� ����
	AnswerBoard* m_pBoard8th;		// ���� ����ĭ ������ ���� ����
	DatumPoint* m_pDatum;

	// Flag �迭�� ���� ��ø Ŭ����

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

