#pragma once
#include "MouseManager.h"

class MouseManager;

/// <summary>
/// Drag and drop 기능을 처리하기 위한 클래스
/// 현재 MouseManager class에 존재하지만 여유 있을 때 이쪽으로 옮길 예정
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
	/// Drag and Drop 기능 
	/// 이 기능을 사용하기 위해선 std::functional 이용이 필요합니다.
	/// 기본적으로 단방향 발생 이벤트입니다. (상호 발생 이벤트가 불가능하진 않습니다.)
	/// 2023.02.10 Kimdowoo
	/// </summary>
	/// <param name="ojbectEvent">void() 이벤트가 발생했을 경우 (눌렀을 때)</param>
	/// <param name="startEvent">void() 처음 발생하는 이벤트 object 범위 안에 있을 경우</param>
	/// <param name="endEvent">void() 다음 발생하는 이벤트 object 범위 안에 있을 경우</param>
	/// <param name="exceptionEvent">void() Drag 도중 이벤트 범위 밖에 있을 경우</param>
	/// <param name="localPosX">void() 상대 좌표 X</param>
	/// <param name="localPosY">void() 상대 좌표 Y</param>
	/// <param name="firstStratPosX">int 첫 Event Object Start Pos X</param>
	/// <param name="firstStartPosY">int 첫 Event Object Start Pos Y</param>
	/// <param name="firstEndPosX">int 첫 Event Object End Pos X</param>
	/// <param name="firstEndPosY">int 첫 Event Object End Pos Y</param>
	/// <param name="secondStratPosX">int 다음 Event Object Start Pos X</param>
	/// <param name="secondStartPosY">int 다음 Event Object Start Pos Y</param>
	/// <param name="secondEndPosX">int 다음 Event Object End Pos X</param>
	/// <param name="secondEndPosY">int 다음 Event Object End Pos Y</param>
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