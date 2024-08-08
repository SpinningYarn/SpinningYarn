#pragma once
class Vector2
{
public:
	Vector2();
	~Vector2();

private:
	float m_PosX;
	float m_PosY;

public:

	/// <summary>
	/// 벡터 합
	/// </summary>
	/// <param name="vectorX"></param>
	/// <param name="vectorY"></param>
	/// <returns>더한 벡터 값</returns>
	Vector2 AddVector2(Vector2 vectorX, Vector2 vectorY);

	/// <summary>
	/// 벡터 차
	/// </summary>
	/// <param name="vectorX"></param>
	/// <param name="vectorY"></param>
	/// <returns>뺀 벡터 값</returns>
	Vector2 SubVector2(Vector2 vectorX, Vector2 vectorY);

	/// <summary>
	/// 벡터의 내적
	/// </summary>
	/// <param name="vectorX"></param>
	/// <param name="vectorY"></param>
	/// <returns>벡터의 내적 값</returns>
	float InnerProductVector2(Vector2 const vectorX, Vector2 const vectorY);

	/// <summary>
	/// 벡터의 크기 구하기
	/// </summary>
	/// <param name="vector">크기를 구할 벡터</param>
	/// <returns>벡터의 크기</returns>
	float NormVector2(const Vector2* vector);

	/// <summary>
	/// 벡터의 크기를 1로 만듬
	/// </summary>
	/// <param name="pVector">변경할 벡터</param>
	void NormalizationVector2(Vector2* pVector);

public:
	void SetVector2X(float x);
	void SetVector2Y(float y);

	float GetVector2X();
	float GetVector2Y();
};
