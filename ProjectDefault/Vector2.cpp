#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
	: m_PosX(0), m_PosY(0)
{

}

Vector2::~Vector2()
{

}

Vector2 Vector2::AddVector2(Vector2 vectorX, Vector2 vectorY)
{
	Vector2 vectorSum;
	vectorSum.m_PosX = vectorX.m_PosX + vectorY.m_PosX;
	vectorSum.m_PosY = vectorX.m_PosY + vectorY.m_PosY;

	return vectorSum;
}

Vector2 Vector2::SubVector2(Vector2 vectorX, Vector2 vectorY)
{
	Vector2 vectorSub;
	vectorSub.m_PosX = vectorX.m_PosX - vectorY.m_PosX;
	vectorSub.m_PosY = vectorX.m_PosY - vectorY.m_PosY;

	return vectorSub;
}

float Vector2::InnerProductVector2(Vector2 const vectorX, Vector2 const vectorY)
{
	float innerProduct = (vectorX.m_PosX * vectorY.m_PosX) + (vectorX.m_PosY * vectorY.m_PosY);

	return innerProduct;
}

float Vector2::NormVector2(const Vector2* vector)
{
	return sqrtf(vector->m_PosX * vector->m_PosX + vector->m_PosY * vector->m_PosY);
}

void Vector2::NormalizationVector2(Vector2* pVector)
{
	float norm = NormVector2(pVector);

	if (norm < 1.0E-38)
	{
		return;
	}
	pVector->m_PosX *= 1 / norm;
	pVector->m_PosY *= 1 / norm;
}

void Vector2::SetVector2X(float x)
{
	m_PosX = x;
}

void Vector2::SetVector2Y(float y)
{
	m_PosY = y;
}

float Vector2::GetVector2X()
{
	return m_PosX;
}

float Vector2::GetVector2Y()
{
	return m_PosY;
}
