#pragma once
#include "Object.h"

/// <summary>
/// 
/// ���� �ý��� �̴ϰ��ӿ��� �������� �Ǵ� Ŭ����
/// �߰��� ���ȿ� ���� Ű����,��,�Ʒ�,��,������ Ű�� �����Ǹ� 
/// �����ǿ� �������� ��ġ�� �� ������ Ű���带 Ÿ�ֿ̹� ���� ����
/// ���� �� ���� ī��Ʈ �ö� (�� ĭ�� �ִ� �� ��)
/// ���� �� ���� ī��Ʈ ������ (�� ĭ�� �ִ� �� ��)
/// 
/// 2022.02.14 YJH
/// </summary>

class AnswerBoard : public Object
{
public:
	AnswerBoard(const int objectNum, std::string objectName);
	AnswerBoard(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~AnswerBoard();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ �ϴ� ���� �������̵�
	virtual void RenderObject() override;		// ��ü���� �׸��� ���� �������̵�	
	void DrawAnswer(int answer);
	double GetXpos();							// ��ü�� x�� ������
	void SetXpos(double Xposition);				// ��ü�� x�� ����
	double GetXposPlusSize();					// ��ü�� x��+size�� ������

	void SetAnswer(int AnswerBoxNum, int book[7][8]);// ���䰪 ����
	int GetAnswerCount();						// ���䰪 ����
	void PlusAnswerCount();						// ���䰪 �÷���
	void SetAnswerGoal(int goal);				// ���䰪 ����
	int GetAnswerGoal();						// ���䰪 ����
	bool GetQuestionActivate();					// ���� Ȱ��ȭ ���� ����
	void SetQuestionActivate(bool OX);			// ���� Ȱ��ȭ ����
	bool GetCountFlag();						// ���� üũ���� ��������
	void SetCountFlag(bool OX);					// ���� üũ���� ����
	bool GetWrongCountFlag();					// ���� üũ���� ��������
	void SetWrongCountFlag(bool OX);			// ���� üũ���� ����
	bool GetSkipFlag();							// ��ŵ ���俩�� ��������
	void SetSkipFlag(bool OX);					// ��ŵ ���俩�� ����
	int GetOX();								// ���俩�� ��������
	void SetOX(int num);						// ���俩�� ����
	bool GetXdrawFlag();						// X ����� ���� �÷��� ��������
	void SetXdrawFlag(int index, bool OX);		// X ����� ���� �÷��� ����
	void SetNextBoard(AnswerBoard* p_NextBoard);// ���� ��� ����
	void FinishGame();
	AnswerBoard* GetNextBoard();				// ���� ��� ��������
	void GetDatumPoint(int NowCount);
	int GetIndex();
	void SetIndex(int num);


private:
	int m_BoardSize;
	int m_Answer[7];
	int m_AnswerCount;							// ���� ���� Ƚ��
	int m_AnswerGoal;							// ��ǥ ���� Ƚ��
	bool m_QuesitonActivate;					// ���� Ȱ��ȭ
	bool m_CountFlag;							// ���� �ѹ��� üũ �����ϵ���
	bool m_WrongFlag;							// ���� �ѹ��� �ǵ���
	bool m_SkipFlag;							// ��ŵ ĭ ����ó��
	int m_OX;									// ���� ����
	bool m_XdrawFlag[7];						// Ʋ���� �� �ϼ�ǰ ���� X����� ����
	AnswerBoard* m_pNextBoard;					// ������ ����Ű�� ���
	int m_NowCount;
	int m_Index;
};


