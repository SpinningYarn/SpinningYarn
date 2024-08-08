#pragma once
#include <windows.h>
#include <functional>

/// <summary>
/// ���콺 ���¿� ���õ� ��� ó�� �Լ�
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
	// ���콺 ��ǥ
	float m_PosX;
	float m_PosY;

	// ���콺 ��? ��? ��ǥ (Ȯ���Ǹ� �ּ� ����)
	int m_PevPosX;
	int m_PevPosY;

	// ���콺 �̵� �ӵ��� �ʿ��� ����
	double m_Speed;					// ���콺 �ӵ�
	double m_DeltaTime;				// DeltaTime	// �ʿ���� ������ ��������� ����
	const double m_DPI = 0.001f;	// ���콺 ���� �� (Dot Per Inch)
	int m_Distance;					// �Ÿ�
	int m_EveX;						// ���� �Ÿ� x ��ǥ
	int m_EveY;						// ���� �Ÿ� y ��ǥ
	int m_InputTimeCount;

	// ���콺 Ŭ�� ����
	bool m_LeftUpClick;				// ���� ���콺�� ���� ��
	bool m_LeftDownClick;			// ���� ���콺�� ������ ��
	bool m_LeftDownDoubleClick;		// ���� ���콺�� ����Ŭ�� ���� ��
	bool m_RightUpClick;			// ������ ���콺�� ���� ��
	bool m_RightDownClick;			// ������ ���콺�� ������ ��
	bool m_RightDownDoubleClick;	// ������ ���콺�� ����Ŭ�� ���� ��
	
	// ���콺 Ŭ�� �� Ư�� ����
	bool m_OneClickOn;				// Ŭ�� �� �ѹ��� �۵��� �� �ְ� �Ǵ�
	bool m_ObjectTouchState;		// ������Ʈ�� ���콺�� Ŭ���Ͽ� �߻��ϴ� �̺�Ʈ ����
	bool m_ObjectMisTouchState;		// ������Ʈ�� �ٸ� ���� Ŭ���Ͽ� �߻��ϴ� �̺�Ʈ ����
	bool m_ObjectNextPosIsState;	// ����(�ι�°) ��ǥ�� ���� ��� ����
	
	int m_oneClickCount;			// Ŭ�� �� �ѹ��� �۵��ϴ� ����� �������϶� ī��Ʈ
	bool m_IsOneClickUp;			// ���콺�� ���� �� �ѹ��� �۵��ϴ� ��� �Ǵ� ����

	// �ǽð� ���콺 ��ǥ�� ���ϴ� �Լ� (x, y��ǥ)
	LPARAM m_LParam;
	
public:
	// ���� ���콺 ��ǥ���� Mouse class�� �����Ѵ�.
	void Initialize(LPARAM lParam);
	
	// ���� ���콺 ��ǥ���� ������ �� �������.
	void SetPevMousePos();

	// ���콺�� x,y ��ǥ�� ������Ʈ�Ѵ�.
	void Update();
	
	/// ���콺 ���� ����
	void GetLeftButtonUpChangeState(bool state);		// ��Ŭ�� Up State Change
	void GetLeftButtonDownChangeState(bool state);		// ��Ŭ�� Down State Change 
	void GetRightButtonUpChangeState(bool state);		// ��Ŭ�� Up State Change
	void GetRightButtonDownChangeState(bool state);		// ��Ŭ�� Down State Change

	// ���콺 ���� ��ȯ
	bool GetLeftButtonUpState();			// ��Ŭ�� Up
	bool GetLeftButtonDownState();			// ��Ŭ�� Down
	bool GetLeftDoubleButtonState();		// ��Ŭ�� Double
	bool GetRightButtonUpState();			// ��Ŭ�� Up
	bool GetRightButtonDownState();			// ��Ŭ�� Down
	bool GetRightDoubleButtonState();		// ��Ŭ�� Double

	// ���콺 ��ǥ ��ȯ
	float GetXPos();
	float GetYPos();

	// ���콺 ���� ��ǥ ��ȯ
	int GetPevXpos();
	int GetPevYpos();

	// ���콺 �ӵ� ��ȯ
	double GetSpeed();

	// ���콺 �Է� �ð� ��ȯ
	int GetInputTime();

private:
	// ���콺 ���� �ð� �ֽ�ȭ
	void EvePosUpdate();

	// ���콺 �ӵ� ���
	void SpeedCalc();

	// ���콺 Ŭ�� �� �ð��� ī����
	void InputCount();

	void ClickSound();
	//SoundManager* m_pSoundManager;

public:
	/// <summary>
	/// Ŭ�� �� �ѹ��� ���
	/// Ŭ�� �� �� �Լ��� ȣ���ϰ� �� �ѹ��� true(��) �����Ѵ�.
	/// 
	/// ���� �� �Լ��� ����ϱ� ���ؼ� ���� ������ �ѵ� ������� �ϴ� �������� �ִ�.
	/// ���� �ʿ�, �켱���� ����
	/// 
	/// 2023.02.10 Kimdowoo
	/// </summary>
	/// <returns></returns>
	bool GetLeftOneDownClickState();	// ��Ŭ�� �� �ѹ��� ���� (bool ��ȯ)
	bool GetLeftOneUpClickState();		// ��Ŭ�� ���� �� �ѹ��� ���� (bool ��ȯ)
	bool GetRightOneDownClickState();	// ��Ŭ�� �� �ѹ��� ���� (bool ��ȯ)
	bool GetRightOneUpClickState();		// ��Ŭ�� �� �ѹ��� ���� (bool ��ȯ)

	void OneClickEnd();					// �ѹ��� �����ϱ� �ʱ�ȭ

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
	/// <param name="localPosX">void() ���콺 ��ǥ X</param>
	/// <param name="localPosY">void() ���콺 ��ǥ Y</param>
	/// <param name="firstStratPosX">int ù Event Object Start Pos X</param>
	/// <param name="firstStartPosY">int ù Event Object Start Pos Y</param>
	/// <param name="firstEndPosX">int ù Event Object End Pos X</param>
	/// <param name="firstEndPosY">int ù Event Object End Pos Y</param>
	/// <param name="secondStratPosX">int ���� Event Object Start Pos X</param>
	/// <param name="secondStartPosY">int ���� Event Object Start Pos Y</param>
	/// <param name="secondEndPosX">int ���� Event Object End Pos X</param>
	/// <param name="secondEndPosY">int ���� Event Object End Pos Y</param>
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


