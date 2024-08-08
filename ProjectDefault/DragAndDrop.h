#pragma once
#include "MouseManager.h"

class MouseManager;

/// <summary>
/// Drag and drop ����� ó���ϱ� ���� Ŭ����
/// ���� MouseManager class�� ���������� ���� ���� �� �������� �ű� ����
/// 
/// 2023.02.13 KDW
/// </summary>
class DragAndDrop
{
public:
	DragAndDrop();
	~DragAndDrop();
private:
	MouseManager* m_pMouseManager;

	bool m_ObjectMisTouchState;
	bool m_ObjectTouchState;
	bool m_ObjectNextPosIsState;

public:

	/// <summary>
	/// Drag and Drop ��� 
	/// �� ����� ����ϱ� ���ؼ� std::functional �̿��� �ʿ��մϴ�.
	/// �⺻������ �ܹ��� �߻� �̺�Ʈ�Դϴ�. (��ȣ �߻� �̺�Ʈ�� �Ұ������� �ʽ��ϴ�.)
	/// 2023.02.10 Kimdowoo
	/// </summary>
	/// <param name="ojbectEvent">void() �̺�Ʈ�� �߻����� ��� (������ ��)</param>
	/// <param name="startEvent">void() ó�� �߻��ϴ� �̺�Ʈ object ���� �ȿ� ���� ���</param>
	/// <param name="endEvent">void() ���� �߻��ϴ� �̺�Ʈ object ���� �ȿ� ���� ���</param>
	/// <param name="exceptionEvent">void() Drag ���� �̺�Ʈ ���� �ۿ� ���� ���</param>
	/// <param name="localPosX">void() ��� ��ǥ X</param>
	/// <param name="localPosY">void() ��� ��ǥ Y</param>
	/// <param name="firstStratPosX">int ù Event Object Start Pos X</param>
	/// <param name="firstStartPosY">int ù Event Object Start Pos Y</param>
	/// <param name="firstEndPosX">int ù Event Object End Pos X</param>
	/// <param name="firstEndPosY">int ù Event Object End Pos Y</param>
	/// <param name="secondStratPosX">int ���� Event Object Start Pos X</param>
	/// <param name="secondStartPosY">int ���� Event Object Start Pos Y</param>
	/// <param name="secondEndPosX">int ���� Event Object End Pos X</param>
	/// <param name="secondEndPosY">int ���� Event Object End Pos Y</param>
	void SetDragAndDrop(
		std::function<void()> objectFirstEvent,
		std::function<void()> objectSecondEvent,
		std::function<void()> startEvent,
		std::function<void()> endEvent,
		std::function<void()> exceptionEvent,
		int localPosX, int localPosY,
		int firstStratPosX, int firstStartPosY, int firstEndPosX, int firstEndPosY,
		int secondStratPosX, int secondStartPosY, int secondEndPosX, int secondEndPosY);
};