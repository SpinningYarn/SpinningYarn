#include "Matrix2.h"

Matrix2::Matrix2()
{
	m_elements[0] = 0;
	m_elements[1] = 0;
	m_elements[2] = 0;
	m_elements[3] = 0;
}

Matrix2::~Matrix2()
{

}

void Matrix2::InitMatrix2(float i, float j, float k, float l)
{
	m_elements[0] = i;
	m_elements[1] = j;
	m_elements[2] = k;
	m_elements[3] = l;
}

Matrix2 Matrix2::AddMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix)
{
	firstMatrix.m_elements[0] += secondMatrix.m_elements[0];
	firstMatrix.m_elements[1] += secondMatrix.m_elements[1];
	firstMatrix.m_elements[2] += secondMatrix.m_elements[2];
	firstMatrix.m_elements[3] += secondMatrix.m_elements[3];

	return firstMatrix;
}

Matrix2 Matrix2::SubMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix)
{
	firstMatrix.m_elements[0] -= secondMatrix.m_elements[0];
	firstMatrix.m_elements[1] -= secondMatrix.m_elements[1];
	firstMatrix.m_elements[2] -= secondMatrix.m_elements[2];
	firstMatrix.m_elements[3] -= secondMatrix.m_elements[3];

	return firstMatrix;
}

Matrix2 Matrix2::MulMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix)
{
	Matrix2 result;

	result.m_elements[0] = firstMatrix.m_elements[0] * secondMatrix.m_elements[0] + firstMatrix.m_elements[1] * secondMatrix.m_elements[2];
	result.m_elements[1] = firstMatrix.m_elements[0] * secondMatrix.m_elements[1] + firstMatrix.m_elements[1] * secondMatrix.m_elements[3];
	result.m_elements[2] = firstMatrix.m_elements[2] * secondMatrix.m_elements[0] + firstMatrix.m_elements[3] * secondMatrix.m_elements[2];
	result.m_elements[3] = firstMatrix.m_elements[2] * secondMatrix.m_elements[1] + firstMatrix.m_elements[3] * secondMatrix.m_elements[3];

	return result;
}

Vector2 Matrix2::MulMatVec2(Vector2 vector, Matrix2 matrix)
{
	Vector2 result;

	result.SetVector2X(vector.GetVector2X() * matrix.m_elements[0] + vector.GetVector2Y() * matrix.m_elements[2]);
	result.SetVector2Y(vector.GetVector2X() * matrix.m_elements[1] + vector.GetVector2Y() * matrix.m_elements[3]);
	
	return result;
}
