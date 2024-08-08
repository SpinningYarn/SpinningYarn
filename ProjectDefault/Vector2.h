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
	/// ���� ��
	/// </summary>
	/// <param name="vectorX"></param>
	/// <param name="vectorY"></param>
	/// <returns>���� ���� ��</returns>
	Vector2 AddVector2(Vector2 vectorX, Vector2 vectorY);

	/// <summary>
	/// ���� ��
	/// </summary>
	/// <param name="vectorX"></param>
	/// <param name="vectorY"></param>
	/// <returns>�� ���� ��</returns>
	Vector2 SubVector2(Vector2 vectorX, Vector2 vectorY);

	/// <summary>
	/// ������ ����
	/// </summary>
	/// <param name="vectorX"></param>
	/// <param name="vectorY"></param>
	/// <returns>������ ���� ��</returns>
	float InnerProductVector2(Vector2 const vectorX, Vector2 const vectorY);

	/// <summary>
	/// ������ ũ�� ���ϱ�
	/// </summary>
	/// <param name="vector">ũ�⸦ ���� ����</param>
	/// <returns>������ ũ��</returns>
	float NormVector2(const Vector2* vector);

	/// <summary>
	/// ������ ũ�⸦ 1�� ����
	/// </summary>
	/// <param name="pVector">������ ����</param>
	void NormalizationVector2(Vector2* pVector);

public:
	void SetVector2X(float x);
	void SetVector2Y(float y);

	float GetVector2X();
	float GetVector2Y();
};
