#pragma once
#ifndef CROWN_INPUT
#define CROWN_INPUT
//================================================
// 作成日 : 2023/6/7
// 作成者 : 服部颯澄
// 
// 入力を司るクラスだよ☆
// 
//================================================
#include <DirectXMath.h>
#include <Windows.h>
#include <vector>
#include <chrono>
namespace Crown
{
	enum class KeyCode : int
	{
		BACKSPACE,	//	バックスペースキー☆
		Tab,		//	タブキー☆
		Enter,		//	エンターキー☆
		Shift,		//	シフトキー☆
		Ctrl,		//	コントロールキー☆
		ALT,		//	オルトキー☆
		CAPS_LOCK,	//	キャプスロックキー☆
		ESC,		//	エスケープキー☆
		Space,		//	スペースキー☆
		PAGE_UP,	//	
		PAGE_DOWN,	//	
		END,		//	
		HOME,		//	
		LEFT,		//	←キー☆
		UP,			//	↑キー☆
		RIGHT,		//	→キー☆
		DOWN,		//	↓キー☆
		key0,		//	0キー☆
		key1,		//	1キー☆
		key2,		//	2キー☆
		key3,		//	3キー☆
		key4,		//	4キー☆
		key5,		//	5キー☆
		key6,		//	6キー☆
		key7,		//	7キー☆
		key8,		//	8キー☆
		key9,		//	9キー☆
		A,			//
		B,			//
		C,			//
		D,			//
		E,			//
		F,			//
		G,			//
		H,			//
		I,			//
		J,			//
		K,			//
		L,			//
		M,			//
		N,			//
		O,			//
		P,			//
		Q,			//
		R,			//
		S,			//
		T,			//
		U,			//
		V,			//
		W,			//
		X,			//
		Y,			//
		Z,			//
		OEM_1,		//	:キー☆
		OEM_2,		//	?キー☆
		OEM_3,		//	@キー☆
		OEM_4,		//	[キー☆
		OEM_5,		//	|キー☆
		OEM_6,		//	]キー☆
		OEM_7,		//	~キー☆
		PLUS,		//	+キー☆
		COMMA,		//	,キー☆
		MINUS,		//	-キー☆
		PERIOD,		//	.キー☆

		keyNum		//	キーの数だよ☆
	};
	class Input
	{
	public:
		interface IMouse
		{
			virtual DirectX::XMFLOAT2 GetMousePosint() const = 0;
			virtual float GetWheel() const = 0;

			virtual bool GetLButton() const = 0;
			virtual bool GetLButtonUp() const = 0;
			virtual bool GetLButtonDown() const = 0;
			virtual int GetLButtonDownTime() const = 0;

			virtual bool GetRButton() const = 0;
			virtual bool GetRButtonUp() const = 0;
			virtual bool GetRButtonDown() const = 0;
			virtual int GetRButtonDownTime() const = 0;

			virtual bool GetCenterButton() const = 0;
			virtual bool GetCenterButtonUp() const = 0;
			virtual bool GetCenterButtonDown() const = 0;
			virtual int GetCenterButtonDownTime() const = 0;
		};
		interface IMouseMessage
		{
			virtual void LButtonUpMessage() = 0;
			virtual void LButtonDownMessage() = 0;
			virtual void RButtonUpMessage() = 0;
			virtual void RButtonDownMessage() = 0;
			virtual void MButtonUpMessage() = 0;
			virtual void MButtonDownMessage() = 0;
			virtual void MoveMessage(LPARAM lparam) = 0;
			virtual void WheelMessage(WPARAM wparam) = 0;
		};
		interface IKeyboard
		{
			virtual bool key(KeyCode keyCode) const = 0;			//	キーを押している☆
			virtual bool keyUp(KeyCode keyCode) const = 0;			//	キーを離した瞬間☆
			virtual bool keyDown(KeyCode keyCode) const = 0;		//	キーを押した瞬間☆
			virtual int keyDownTime(KeyCode keyCode) const = 0;	//	キーを押している時間を返すよ☆
		};
		interface IKeyboardMessage
		{
			virtual void UpMessage(WPARAM wparam) = 0;
			virtual void DownMessage(WPARAM wparam) = 0;
		};

		static const IMouse* const GetMouse();
		static const IKeyboard* const GetKeyboard();
		static IMouseMessage* const GetMouseMessage();
		static IKeyboardMessage* const GetKeyboardMessage();

		static void Update();
		static void Deleteinstance();
	private:
		class Mouse : public IMouse, public IMouseMessage
		{
		public:
			Mouse();
			virtual ~Mouse();

			virtual DirectX::XMFLOAT2 GetMousePosint() const;
			virtual float GetWheel() const;

			virtual bool GetLButton() const override;
			virtual bool GetLButtonUp() const override;
			virtual bool GetLButtonDown() const override;
			virtual int GetLButtonDownTime() const override;

			virtual bool GetRButton() const override;
			virtual bool GetRButtonUp() const override;
			virtual bool GetRButtonDown() const override;
			virtual int GetRButtonDownTime() const override;

			virtual bool GetCenterButton() const override;
			virtual bool GetCenterButtonUp() const override;
			virtual bool GetCenterButtonDown() const override;
			virtual int GetCenterButtonDownTime() const override;

			void Update();

			virtual void LButtonUpMessage() override;
			virtual void LButtonDownMessage() override;
			virtual void RButtonUpMessage() override;
			virtual void RButtonDownMessage() override;
			virtual void MButtonUpMessage() override;
			virtual void MButtonDownMessage() override;
			virtual void MoveMessage(LPARAM lparam) override;
			virtual void WheelMessage(WPARAM wparam) override;
		private:
			int m_x, m_y;
			float m_wheel;
			bool m_l, m_r, m_center;
			bool m_oldL, m_oldR, m_oldCenter;
			std::chrono::system_clock::time_point m_lTimer, m_rTimer, m_centerTimer;
		};
		class Keyboard : public IKeyboard, public IKeyboardMessage
		{
		public:
			Keyboard();
			virtual ~Keyboard();

			virtual bool key(KeyCode keyCode) const override;			//	キーを押している☆
			virtual bool keyUp(KeyCode keyCode) const override;			//	キーを離した瞬間☆
			virtual bool keyDown(KeyCode keyCode) const override;		//	キーを押した瞬間☆
			virtual int keyDownTime(KeyCode keyCode) const override;	//	キーを押している時間を返すよ☆

			void Update();

			virtual void UpMessage(WPARAM wparam) override;
			virtual void DownMessage(WPARAM wparam) override;
		private:
			KeyCode GetKeyCode(WPARAM wparam);

			bool m_keyInput[static_cast<int>(KeyCode::keyNum)];
			bool m_oldKeyInput[static_cast<int>(KeyCode::keyNum)];
			std::chrono::system_clock::time_point m_keyTimer[static_cast<int>(KeyCode::keyNum)];
			
		};
		Input();
		~Input();

		static Input* m_me;
		Mouse m_mouse;
		Keyboard m_keyboard;
	};
}
#endif // !CROWN_INPUT
