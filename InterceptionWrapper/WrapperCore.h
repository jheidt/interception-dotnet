#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;


namespace InterceptionWrapper {

    #pragma region keyboard state / keyboard filter id enums
	[Flags]
	public enum class KeyState : unsigned short
	{
		Down            = INTERCEPTION_KEY_DOWN,
		Up              = INTERCEPTION_KEY_UP,
		E0              = INTERCEPTION_KEY_E0,
		E1              = INTERCEPTION_KEY_E1,
		TermSrvSetLed   = INTERCEPTION_KEY_TERMSRV_SET_LED,
		TermSrvShadow   = INTERCEPTION_KEY_TERMSRV_SHADOW,
		TermSrvVkPacket = INTERCEPTION_KEY_TERMSRV_VKPACKET
	};

	public enum class FilterKeyState : unsigned short
	{
		None = INTERCEPTION_FILTER_KEY_NONE,
		All = INTERCEPTION_FILTER_KEY_ALL,
		Down = INTERCEPTION_FILTER_KEY_DOWN,
		Up = INTERCEPTION_FILTER_KEY_UP,
		E0 = INTERCEPTION_FILTER_KEY_E0,
		E1 = INTERCEPTION_FILTER_KEY_E1,
		TermSrvSetLed = INTERCEPTION_FILTER_KEY_TERMSRV_SET_LED,
		TermSrvShadow = INTERCEPTION_FILTER_KEY_TERMSRV_SHADOW,
		TermSrvVkPacket = INTERCEPTION_FILTER_KEY_TERMSRV_VKPACKET
	};
    #pragma endregion

    #pragma region mouse state / filter id enums
	public enum class MouseState : unsigned short
	{
        LEFT_BUTTON_DOWN   = 0x001,
        LEFT_BUTTON_UP     = 0x002,
        RIGHT_BUTTON_DOWN  = 0x004,
        RIGHT_BUTTON_UP    = 0x008,
        MIDDLE_BUTTON_DOWN = 0x010,
        MIDDLE_BUTTON_UP   = 0x020,

        BUTTON_1_DOWN = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN,
        BUTTON_1_UP   = INTERCEPTION_MOUSE_LEFT_BUTTON_UP,
        BUTTON_2_DOWN = INTERCEPTION_MOUSE_RIGHT_BUTTON_DOWN,
        BUTTON_2_UP   = INTERCEPTION_MOUSE_RIGHT_BUTTON_UP,
        BUTTON_3_DOWN = INTERCEPTION_MOUSE_MIDDLE_BUTTON_DOWN,
        BUTTON_3_UP   = INTERCEPTION_MOUSE_MIDDLE_BUTTON_UP,

        BUTTON_4_DOWN = 0x040,
        BUTTON_4_UP   = 0x080,
        BUTTON_5_DOWN = 0x100,
        BUTTON_5_UP   = 0x200,

        WHEEL  = 0x400,
        HWHEEL = 0x800
	};

	public enum class FilterMouseState : unsigned short
	{
		NONE = 0x0000,
		ALL  = 0xFFFF,
        
		LEFT_BUTTON_DOWN   = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN,
		LEFT_BUTTON_UP     = INTERCEPTION_MOUSE_LEFT_BUTTON_UP,
		RIGHT_BUTTON_DOWN  = INTERCEPTION_MOUSE_RIGHT_BUTTON_DOWN,
		RIGHT_BUTTON_UP    = INTERCEPTION_MOUSE_RIGHT_BUTTON_UP,
		MIDDLE_BUTTON_DOWN = INTERCEPTION_MOUSE_MIDDLE_BUTTON_DOWN,
		MIDDLE_BUTTON_UP   = INTERCEPTION_MOUSE_MIDDLE_BUTTON_UP,

		BUTTON_1_DOWN = INTERCEPTION_MOUSE_BUTTON_1_DOWN,
		BUTTON_1_UP   = INTERCEPTION_MOUSE_BUTTON_1_UP,
		BUTTON_2_DOWN = INTERCEPTION_MOUSE_BUTTON_2_DOWN,
		BUTTON_2_UP   = INTERCEPTION_MOUSE_BUTTON_2_UP,
		BUTTON_3_DOWN = INTERCEPTION_MOUSE_BUTTON_3_DOWN,
		BUTTON_3_UP   = INTERCEPTION_MOUSE_BUTTON_3_UP,

		BUTTON_4_DOWN       = INTERCEPTION_MOUSE_BUTTON_4_DOWN,
		BUTTON_4_UP         = INTERCEPTION_MOUSE_BUTTON_4_UP,
		MOUSE_BUTTON_5_DOWN = INTERCEPTION_MOUSE_BUTTON_5_DOWN,
		MOUSE_BUTTON_5_UP   = INTERCEPTION_MOUSE_BUTTON_5_UP,

		MOUSE_WHEEL  = INTERCEPTION_MOUSE_WHEEL,
		MOUSE_HWHEEL = INTERCEPTION_MOUSE_HWHEEL,

		MOUSE_MOVE = 0x1000
	};

	public enum class MouseFlag : unsigned short
	{
		MOVE_RELATIVE      = 0x000,
		MOVE_ABSOLUTE      = 0x001,
		VIRTUAL_DESKTOP    = 0x002,
		ATTRIBUTES_CHANGED = 0x004,
		MOVE_NOCOALESCE    = 0x008,
		TERMSRV_SRC_SHADOW = 0x100
	};
    #pragma endregion

    #pragma region data packet structures
    [StructLayout(LayoutKind::Sequential)]
	public value struct MouseStroke
	{
		unsigned short state;
		unsigned short flags;
		short rolling;
		int x;
		int y;
		unsigned int information;
	};
    
    [StructLayout(LayoutKind::Sequential)]
    public value struct KeyStroke
	{
		unsigned short code;
		unsigned short state;
		unsigned int information;
	};
    #pragma endregion

    // interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);
    // interception_set_filter(context, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_MOVE);

}
