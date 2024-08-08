#pragma once
#include "Vector2.h"

class Matrix2
{
public:
	Matrix2();
	~Matrix2();

private:
	float m_elements[4];

public:
	
	/// <summary>
	/// ��� �� ����
	/// </summary>
	/// <param name="matrix">������ ���</param>
	/// <param name="i">1, 1</param>
	/// <param name="j">1, 2</param>
	/// <param name="k">2, 1</param>
	/// <param name="l">2, 2</param>
	void InitMatrix2(float i, float j, float k, float l);

	/// <summary>
	/// ��� ��
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns>���� ��� ��</returns>
	Matrix2 AddMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

	/// <summary>
	/// ��� ��
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns>�� ��� ��</returns>
	Matrix2 SubMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

	/// <summary>
	/// ��� ��
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns>���� ��� ��</returns>
	Matrix2 MulMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

	/// <summary>
	/// ���� * ���
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns>���Ϳ� ����� ���� ��</returns>
	Vector2 MulMatVec2(Vector2 vector, Matrix2 matrix);
};

