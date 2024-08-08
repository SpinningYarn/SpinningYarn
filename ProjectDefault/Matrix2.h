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
	/// 행렬 값 세팅
	/// </summary>
	/// <param name="matrix">세팅할 행렬</param>
	/// <param name="i">1, 1</param>
	/// <param name="j">1, 2</param>
	/// <param name="k">2, 1</param>
	/// <param name="l">2, 2</param>
	void InitMatrix2(float i, float j, float k, float l);

	/// <summary>
	/// 행렬 합
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns>더한 행렬 값</returns>
	Matrix2 AddMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

	/// <summary>
	/// 행렬 차
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns>뺀 행렬 값</returns>
	Matrix2 SubMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

	/// <summary>
	/// 행렬 곱
	/// </summary>
	/// <param name="firstMatrix"></param>
	/// <param name="secondMatrix"></param>
	/// <returns>곱한 행렬 값</returns>
	Matrix2 MulMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

	/// <summary>
	/// 벡터 * 행렬
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns>벡터와 행렬을 곱한 값</returns>
	Vector2 MulMatVec2(Vector2 vector, Matrix2 matrix);
};

