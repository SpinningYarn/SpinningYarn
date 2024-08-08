#pragma once
#include <windows.h>
#include <functional>

/// <summary>
/// 마우스 상태에 관련된 모든 처리 함수
/// 
/// 2023.02.07 KDW
/// </summary>
class MouseManager
{
public:
	static MouseManager* GetInstance();
	
private:
	static MouseManager* m_pInstance;

private:
	MouseManager();
	~MouseManager();

protected:
	// 마우스 좌표
	float m_PosX;
	float m_PosY;

	// 마우스 전? 후? 좌표 (확정되면 주석 수정)
	int m_PevPosX;
	int m_PevPosY;

	// 마우스 이동 속도에 필요한 변수
	double m_Speed;					// 마우스 속도
	double m_DeltaTime;				// DeltaTime	// 필요없는 변수임 실험용으로 놔둠
	const double m_DPI = 0.001f;	// 마우스 감도 값 (Dot Per Inch)
	int m_Distance;					// 거리
	int m_EveX;						// 직전 거리 x 좌표
	int m_EveY;						// 직전 거리 y 좌표
	int m_InputTimeCount;

	// 마우스 클릭 상태
	bool m_LeftUpClick;				// 왼쪽 마우스를 땠을 때
	bool m_LeftDownClick;			// 왼쪽 마우스를 눌렀을 때
	bool m_LeftDownDoubleClick;		// 왼쪽 마우스를 더블클릭 했을 때
	bool m_RightUpClick;			// 오른쪽 마우스를 땠을 때
	bool m_RightDownClick;			// 오른쪽 마우스를 눌렀을 때
	bool m_RightDownDoubleClick;	// 오른쪽 마우스를 더블클릭 했을 때
	
	// 마우스 클릭 시 특수 상태
	bool m_OneClickOn;				// 클릭 시 한번만 작동할 수 있게 판단
	bool m_ObjectTouchState;		// 오브젝트를 마우스로 클릭하여 발생하는 이벤트 판정
	bool m_ObjectMisTouchState;		// 오브젝트를 다른 곳에 클릭하여 발생하는 이벤트 판정
	bool m_ObjectNextPosIsState;	// 다음(두번째) 좌표에 있을 경우 상태
	
	int m_oneClickCount;			// 클릭 시 한번만 작동하는 기능이 여러개일때 카운트
	bool m_IsOneClickUp;			// 마우스를 땠을 때 한번만 작동하는 기능 판단 변수

	// 실시간 마우스 좌표를 구하는 함수 (x, y좌표)
	LPARAM m_LParam;
	
public:
	// 현재 마우스 좌표값을 Mouse class에 저장한다.
	void Initialize(LPARAM lParam);
	
	// 이전 마우스 좌표값을 세팅할 때 사용하자.
	void SetPevMousePos();

	// 마우스의 x,y 좌표를 업데이트한다.
	void Update();
	
	/// 마우스 상태 변경
	void GetLeftButtonUpChangeState(bool state);		// 좌클릭 Up State Change
	void GetLeftButtonDownChangeState(bool state);		// 좌클릭 Down State Change 
	void GetRightButtonUpChangeState(bool state);		// 우클릭 Up State Change
	void GetRightButtonDownChangeState(bool state);		// 우클릭 Down State Change

	// 마우스 상태 반환
	bool GetLeftButtonUpState();			// 좌클릭 Up
	bool GetLeftButtonDownState();			// 좌클릭 Down
	bool GetLeftDoubleButtonState();		// 좌클릭 Double
	bool GetRightButtonUpState();			// 우클릭 Up
	bool GetRightButtonDownState();			// 우클릭 Down
	bool GetRightDoubleButtonState();		// 우클릭 Double

	// 마우스 좌표 반환
	float GetXPos();
	float GetYPos();

	// 마우스 이전 좌표 반환
	int GetPevXpos();
	int GetPevYpos();

	// 마우스 속도 반환
	double GetSpeed();

	// 마우스 입력 시간 반환
	int GetInputTime();

private:
	// 마우스 직전 시간 최신화
	void EvePosUpdate();

	// 마우스 속도 계산
	void SpeedCalc();

	// 마우스 클릭 시 시간당 카운팅
	void InputCount();

	void ClickSound();
	//SoundManager* m_pSoundManager;

public:
	/// <summary>
	/// 클릭 시 한번만 기능
	/// 클릭 시 이 함수를 호출하고 단 한번만 true(을) 리턴한다.
	/// 
	/// 현재 이 함수를 사용하기 위해선 여기 안으로 한데 묶어줘야 하는 문제점이 있다.
	/// 개선 필요, 우선순위 낮음
	/// 
	/// 2023.02.10 Kimdowoo
	/// </summary>
	/// <returns></returns>
	bool GetLeftOneDownClickState();	// 좌클릭 시 한번만 실행 (bool 반환)
	bool GetLeftOneUpClickState();		// 좌클릭 땠을 시 한번만 실행 (bool 반환)
	bool GetRightOneDownClickState();	// 우클릭 시 한번만 실행 (bool 반환)
	bool GetRightOneUpClickState();		// 우클릭 시 한번만 실행 (bool 반환)

	void OneClickEnd();					// 한번만 실행하기 초기화

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
	/// <param name="localPosX">void() 마우스 좌표 X</param>
	/// <param name="localPosY">void() 마우스 좌표 Y</param>
	/// <param name="firstStratPosX">int 첫 Event Object Start Pos X</param>
	/// <param name="firstStartPosY">int 첫 Event Object Start Pos Y</param>
	/// <param name="firstEndPosX">int 첫 Event Object End Pos X</param>
	/// <param name="firstEndPosY">int 첫 Event Object End Pos Y</param>
	/// <param name="secondStratPosX">int 다음 Event Object Start Pos X</param>
	/// <param name="secondStartPosY">int 다음 Event Object Start Pos Y</param>
	/// <param name="secondEndPosX">int 다음 Event Object End Pos X</param>
	/// <param name="secondEndPosY">int 다음 Event Object End Pos Y</param>
	void DragAndDrop(
		std::function<void()> objectFirstEvent,
		std::function<void()> objectSecondEvent,
		std::function<void()> startEvent,
		std::function<void()> endEvent,
		std::function<void()> exceptionEvent,
		int localPosX, int localPosY,
		int firstStratPosX, int firstStartPosY, int firstEndPosX, int firstEndPosY,
		int secondStratPosX, int secondStartPosY, int secondEndPosX, int secondEndPosY);

public:
	void ResetMousePoint();

};


