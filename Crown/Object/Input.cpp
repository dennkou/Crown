#include "Input.h"
#include <windowsx.h>



Crown::Input* Crown::Input::m_me = nullptr;



Crown::Input::Mouse::Mouse()
	:
	m_center(false),
	m_oldCenter(false),
	m_r(false),
	m_oldR(false),
	m_l(false),
	m_oldL(false),
	m_wheel(0),
	m_x(0),
	m_y(0)
{
}

Crown::Input::Mouse::~Mouse()
{
}

DirectX::XMFLOAT2 Crown::Input::Mouse::GetMousePosint() const
{
	return DirectX::XMFLOAT2(static_cast<float>(m_x), static_cast<float>(m_y));
}

float Crown::Input::Mouse::GetWheel() const
{
	return m_wheel;
}

bool Crown::Input::Mouse::GetLButton() const
{
	return m_l;
}

bool Crown::Input::Mouse::GetLButtonUp() const
{
	return m_oldL && !m_l;
}

bool Crown::Input::Mouse::GetLButtonDown() const
{
	return !m_oldL && m_l;
}

int Crown::Input::Mouse::GetLButtonDownTime() const
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_lTimer).count());
}

bool Crown::Input::Mouse::GetRButton() const
{
	return m_r;
}

bool Crown::Input::Mouse::GetRButtonUp() const
{
	return m_oldR && !m_r;
}

bool Crown::Input::Mouse::GetRButtonDown() const
{
	return !m_oldR && m_r;
}

int Crown::Input::Mouse::GetRButtonDownTime() const
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_rTimer).count());
}

bool Crown::Input::Mouse::GetCenterButton() const
{
	return m_center;
}

bool Crown::Input::Mouse::GetCenterButtonUp() const
{
	return m_oldCenter && !m_center;
}

bool Crown::Input::Mouse::GetCenterButtonDown() const
{
	return !m_oldCenter && m_center;
}

int Crown::Input::Mouse::GetCenterButtonDownTime() const
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_centerTimer).count());
}

void Crown::Input::Mouse::Update()
{
}

void Crown::Input::Mouse::LButtonUpMessage()
{
	m_l = false;
}

void Crown::Input::Mouse::LButtonDownMessage()
{
	m_l = true;
	m_lTimer = std::chrono::system_clock::now();
}

void Crown::Input::Mouse::RButtonUpMessage()
{
	m_r = false;
}

void Crown::Input::Mouse::RButtonDownMessage()
{
	m_r = true;
	m_lTimer = std::chrono::system_clock::now();
}

void Crown::Input::Mouse::MButtonUpMessage()
{
	m_center = false;
}

void Crown::Input::Mouse::MButtonDownMessage()
{
	m_center = true;
	m_centerTimer = std::chrono::system_clock::now();
}

void Crown::Input::Mouse::MoveMessage(LPARAM lparam)
{
	m_x = GET_X_LPARAM(lparam);
	m_y = GET_Y_LPARAM(lparam);
}

void Crown::Input::Mouse::WheelMessage(WPARAM wparam)
{
	m_wheel = GET_WHEEL_DELTA_WPARAM(wparam);
}





//-------------------------------------------------------------------------------------------------------------------------------------------------
//	ここからキーボード系の処理だよ☆





Crown::Input::Keyboard::Keyboard()
	:
	m_keyInput{},
	m_oldKeyInput{}
{
}

Crown::Input::Keyboard::~Keyboard()
{
}

bool Crown::Input::Keyboard::key(KeyCode keyCode) const
{
	return m_keyInput[static_cast<int>(keyCode)];
}

bool Crown::Input::Keyboard::keyUp(KeyCode keyCode) const
{
	return m_oldKeyInput[static_cast<int>(keyCode)] && !m_keyInput[static_cast<int>(keyCode)];
}

bool Crown::Input::Keyboard::keyDown(KeyCode keyCode) const
{
	return !m_oldKeyInput[static_cast<int>(keyCode)] && m_keyInput[static_cast<int>(keyCode)];
}

int Crown::Input::Keyboard::keyDownTime(KeyCode keyCode) const
{
	return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_keyTimer[static_cast<int>(keyCode)]).count());
}

void Crown::Input::Keyboard::Update()
{
	//	キー入力の更新だよ☆
	for (int i = 0; i < static_cast<int>(KeyCode::keyNum); ++i)
	{
		m_oldKeyInput[i] = m_keyInput[i];
	}
}

void Crown::Input::Keyboard::UpMessage(WPARAM wparam)
{
	int keyCode = static_cast<int>(GetKeyCode(wparam));						//	キーコードを取得するよ☆
	if (keyCode == static_cast<int>(KeyCode::keyNum))
	{
		return;
	}
	m_keyInput[keyCode] = false;
}

void Crown::Input::Keyboard::DownMessage(WPARAM wparam)
{
	int keyCode = static_cast<int>(GetKeyCode(wparam));						//	キーコードを取得するよ☆
	if (keyCode == static_cast<int>(KeyCode::keyNum))
	{
		return;
	}
	if (!m_keyInput[keyCode])
	{
		m_keyInput[keyCode] = true;
		m_keyTimer[keyCode] = std::chrono::system_clock::now();				//	現在時間の取得するよ☆
	}
}

Crown::KeyCode Crown::Input::Keyboard::GetKeyCode(WPARAM wparam)
{
	KeyCode returnCode = KeyCode::keyNum;	//	エラー識別用に存在しない値を入れておくよ☆
	switch (wparam)
	{
		case VK_LBUTTON: break;
		case VK_RBUTTON: break;
		case VK_CANCEL: break;
		case VK_MBUTTON: break;
		case VK_XBUTTON1: break;
		case VK_XBUTTON2: break;
		case 0x07: break;
		case VK_BACK:
			returnCode = KeyCode::BACKSPACE;
			break;
		case VK_TAB:
			returnCode = KeyCode::Tab;
			break;
		case 0x0A: break;
		case 0x0B: break;
		case VK_CLEAR: break;
		case VK_RETURN:
			returnCode = KeyCode::Enter;
			break;
		case 0x0E: break;
		case 0x0F: break;
		case VK_SHIFT:
			returnCode = KeyCode::Shift;
			break;
		case VK_CONTROL:
			returnCode = KeyCode::Ctrl;
			break;
		case VK_MENU:
			returnCode = KeyCode::ALT;
			break;
		case VK_PAUSE: break;
		case VK_CAPITAL:
			returnCode = KeyCode::CAPS_LOCK;
			break;
		case VK_KANA: break;
		case VK_IME_ON: break;
		case VK_JUNJA: break;
		case VK_FINAL: break;
		case VK_HANJA: break;
		case VK_IME_OFF: break;
		case VK_ESCAPE:
			returnCode = KeyCode::ESC;
			break;
		case VK_CONVERT: break;
		case VK_NONCONVERT: break;
		case VK_ACCEPT: break;
		case VK_MODECHANGE: break;
		case VK_SPACE:
			returnCode = KeyCode::Space;
			break;
		case VK_PRIOR:
			returnCode = KeyCode::PAGE_UP;
			break;
		case VK_NEXT:
			returnCode = KeyCode::PAGE_DOWN;
			break;
		case VK_END:
			returnCode = KeyCode::END;
			break;
		case VK_HOME:
			returnCode = KeyCode::HOME;
			break;
		case VK_LEFT:
			returnCode = KeyCode::LEFT;
			break;
		case VK_UP:
			returnCode = KeyCode::UP;
			break;
		case VK_RIGHT:
			returnCode = KeyCode::RIGHT;
			break;
		case VK_DOWN:
			returnCode = KeyCode::DOWN;
			break;
		case VK_SELECT: break;
		case VK_PRINT: break;
		case VK_EXECUTE: break;
		case VK_SNAPSHOT: break;
		case VK_INSERT: break;
		case VK_DELETE: break;
		case VK_HELP: break;
		case 0x30:
			returnCode = KeyCode::key0;
			break;
		case 0x31:
			returnCode = KeyCode::key1;
			break;
		case 0x32:
			returnCode = KeyCode::key2;
			break;
		case 0x33:
			returnCode = KeyCode::key3;
			break;
		case 0x34:
			returnCode = KeyCode::key4;
			break;
		case 0x35:
			returnCode = KeyCode::key5;
			break;
		case 0x36:
			returnCode = KeyCode::key6;
			break;
		case 0x37:
			returnCode = KeyCode::key7;
			break;
		case 0x38:
			returnCode = KeyCode::key8;
			break;
		case 0x39:
			returnCode = KeyCode::key9;
			break;
		case 0x3A: break;
		case 0x3B: break;
		case 0x3C: break;
		case 0x3D: break;
		case 0x3E: break;
		case 0x3F: break;
		case 0x40: break;
		case 0x41:
			returnCode = KeyCode::A;
			break;
		case 0x42:
			returnCode = KeyCode::B;
			break;
		case 0x43:
			returnCode = KeyCode::C;
			break;
		case 0x44:
			returnCode = KeyCode::D;
			break;
		case 0x45:
			returnCode = KeyCode::E;
			break;
		case 0x46:
			returnCode = KeyCode::F;
			break;
		case 0x47:
			returnCode = KeyCode::G;
			break;
		case 0x48:
			returnCode = KeyCode::H;
			break;
		case 0x49:
			returnCode = KeyCode::I;
			break;
		case 0x4A:
			returnCode = KeyCode::J;
			break;
		case 0x4B:
			returnCode = KeyCode::K;
			break;
		case 0x4C:
			returnCode = KeyCode::L;
			break;
		case 0x4D:
			returnCode = KeyCode::M;
			break;
		case 0x4E:
			returnCode = KeyCode::N;
			break;
		case 0x4F:
			returnCode = KeyCode::O;
			break;
		case 0x50:
			returnCode = KeyCode::P;
			break;
		case 0x51:
			returnCode = KeyCode::Q;
			break;
		case 0x52:
			returnCode = KeyCode::R;
			break;
		case 0x53:
			returnCode = KeyCode::S;
			break;
		case 0x54:
			returnCode = KeyCode::T;
			break;
		case 0x55:
			returnCode = KeyCode::U;
			break;
		case 0x56:
			returnCode = KeyCode::V;
			break;
		case 0x57:
			returnCode = KeyCode::W;
			break;
		case 0x58:
			returnCode = KeyCode::X;
			break;
		case 0x59:
			returnCode = KeyCode::Y;
			break;
		case 0x5A:
			returnCode = KeyCode::Z;
			break;
		case VK_LWIN: break;
		case VK_RWIN: break;
		case VK_APPS: break;
		case 0x5E: break;
		case VK_SLEEP: break;
		case VK_NUMPAD0: break;
		case VK_NUMPAD1: break;
		case VK_NUMPAD2: break;
		case VK_NUMPAD3: break;
		case VK_NUMPAD4: break;
		case VK_NUMPAD5: break;
		case VK_NUMPAD6: break;
		case VK_NUMPAD7: break;
		case VK_NUMPAD8: break;
		case VK_NUMPAD9: break;
		case VK_MULTIPLY: break;
		case VK_ADD: break;
		case VK_SEPARATOR: break;
		case VK_SUBTRACT: break;
		case VK_DECIMAL: break;
		case VK_DIVIDE: break;
		case VK_F1: break;
		case VK_F2: break;
		case VK_F3: break;
		case VK_F4: break;
		case VK_F5: break;
		case VK_F6: break;
		case VK_F7: break;
		case VK_F8: break;
		case VK_F9: break;
		case VK_F10: break;
		case VK_F11: break;
		case VK_F12: break;
		case VK_F13: break;
		case VK_F14: break;
		case VK_F15: break;
		case VK_F16: break;
		case VK_F17: break;
		case VK_F18: break;
		case VK_F19: break;
		case VK_F20: break;
		case VK_F21: break;
		case VK_F22: break;
		case VK_F23: break;
		case VK_F24: break;
		case 0x88: break;
		case 0x89: break;
		case 0x8A: break;
		case 0x8B: break;
		case 0x8C: break;
		case 0x8D: break;
		case 0x8E: break;
		case 0x8F: break;
		case VK_NUMLOCK: break;
		case VK_SCROLL: break;
		case 0x92: break;
		case 0x93: break;
		case 0x94: break;
		case 0x95: break;
		case 0x96: break;
		case 0x97: break;
		case 0x98: break;
		case 0x99: break;
		case 0x9A: break;
		case 0x9B: break;
		case 0x9C: break;
		case 0x9D: break;
		case 0x9E: break;
		case 0x9F: break;
		case VK_LSHIFT:
			returnCode = KeyCode::Shift;
			break;
		case VK_RSHIFT:
			returnCode = KeyCode::Shift;
			break;
		case VK_LCONTROL:
			returnCode = KeyCode::Ctrl;
			break;
		case VK_RCONTROL:
			returnCode = KeyCode::Ctrl;
			break;
		case VK_LMENU:
			returnCode = KeyCode::ALT;
			break;
		case VK_RMENU:
			returnCode = KeyCode::ALT;
			break;
		case VK_BROWSER_BACK: break;
		case VK_BROWSER_FORWARD: break;
		case VK_BROWSER_REFRESH: break;
		case VK_BROWSER_STOP: break;
		case VK_BROWSER_SEARCH: break;
		case VK_BROWSER_FAVORITES: break;
		case VK_BROWSER_HOME: break;
		case VK_VOLUME_MUTE: break;
		case VK_VOLUME_DOWN: break;
		case VK_VOLUME_UP: break;
		case VK_MEDIA_NEXT_TRACK: break;
		case VK_MEDIA_PREV_TRACK: break;
		case VK_MEDIA_STOP: break;
		case VK_MEDIA_PLAY_PAUSE: break;
		case VK_LAUNCH_MAIL: break;
		case VK_LAUNCH_MEDIA_SELECT: break;
		case VK_LAUNCH_APP1: break;
		case VK_LAUNCH_APP2: break;
		case 0xB8: break;
		case 0xB9: break;
		case VK_OEM_1:
			returnCode = KeyCode::OEM_1;
			break;
		case VK_OEM_PLUS:
			returnCode = KeyCode::PLUS;
			break;
		case VK_OEM_COMMA:
			returnCode = KeyCode::COMMA;
			break;
		case VK_OEM_MINUS:
			returnCode = KeyCode::MINUS;
			break;
		case VK_OEM_PERIOD:
			returnCode = KeyCode::PERIOD;
			break;
		case VK_OEM_2:
			returnCode = KeyCode::OEM_2;
			break;
		case VK_OEM_3:
			returnCode = KeyCode::OEM_3;
			break;
		case 0xC1: break;
		case 0xC2: break;
		case 0xC3: break;
		case 0xC4: break;
		case 0xC5: break;
		case 0xC6: break;
		case 0xC7: break;
		case 0xC8: break;
		case 0xC9: break;
		case 0xCA: break;
		case 0xCB: break;
		case 0xCC: break;
		case 0xCD: break;
		case 0xCE: break;
		case 0xCF: break;
		case 0xD0: break;
		case 0xD1: break;
		case 0xD2: break;
		case 0xD3: break;
		case 0xD4: break;
		case 0xD5: break;
		case 0xD6: break;
		case 0xD7: break;
		case 0xD8: break;
		case 0xD9: break;
		case 0xDA: break;
		case VK_OEM_4:
			returnCode = KeyCode::OEM_4;
			break;
		case VK_OEM_5:
			returnCode = KeyCode::OEM_5;
			break;
		case VK_OEM_6:
			returnCode = KeyCode::OEM_6;
			break;
		case VK_OEM_7:
			returnCode = KeyCode::OEM_7;
			break;
		case VK_OEM_8: break;
		case 0xE0: break;
		case 0xE1: break;
		case VK_OEM_102: break;
		case 0xE3: break;
		case 0xE4: break;
		case VK_PROCESSKEY: break;
		case 0xE6: break;
		case VK_PACKET: break;
		case 0xE8: break;
		case 0xE9: break;
		case 0xEA: break;
		case 0xEB: break;
		case 0xEC: break;
		case 0xED: break;
		case 0xEE: break;
		case 0xEF: break;
		case 0xF0: break;
		case 0xF1: break;
		case 0xF2: break;
		case 0xF3: break;
		case 0xF4: break;
		case 0xF5: break;
		case VK_ATTN: break;
		case VK_CRSEL: break;
		case VK_EXSEL: break;
		case VK_EREOF: break;
		case VK_PLAY: break;
		case VK_ZOOM: break;
		case VK_NONAME: break;
		case VK_PA1: break;
		case VK_OEM_CLEAR: break;
		default:
			__assume(0);
			break;
	}
	return returnCode;
}





//-------------------------------------------------------------------------------------------------------------------------------------------------
//	Inputクラスの処理だよ☆





Crown::Input::Input()
{
}

Crown::Input::~Input()
{

}

const Crown::Input::IMouse* const Crown::Input::GetMouse()
{
	if (m_me == nullptr)
	{
		m_me = new Input();
	}
	return &m_me->m_mouse;
}

const Crown::Input::IKeyboard* const Crown::Input::GetKeyboard()
{
	if (m_me == nullptr)
	{
		m_me = new Input();
	}
	return &m_me->m_keyboard;
}

Crown::Input::IMouseMessage* const Crown::Input::GetMouseMessage()
{
	if (m_me == nullptr)
	{
		m_me = new Input();
	}
	return &m_me->m_mouse;
}

Crown::Input::IKeyboardMessage* const Crown::Input::GetKeyboardMessage()
{
	if (m_me == nullptr)
	{
		m_me = new Input();
	}
	return &m_me->m_keyboard;
}

void Crown::Input::Update()
{
	if (m_me != nullptr)
	{
		m_me->m_mouse.Update();
		m_me->m_keyboard.Update();
	}
}

void Crown::Input::Deleteinstance()
{
	if (m_me != nullptr)
	{
		delete m_me;
		m_me = nullptr;
	}
}