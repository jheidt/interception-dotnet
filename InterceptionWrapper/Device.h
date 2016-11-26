#pragma once

namespace InterceptionWrapper {

    using namespace System;

    ref class Context;

    public ref class Device
    {
    private:
        InterceptionDevice _deviceIndex = 0;
        Context^ _context;
        
    public:
        property int Index {
            int get() { return _deviceIndex; }
        }
        property bool IsMouse {
            bool get() { return interception_is_mouse(_deviceIndex) != 0; }
        }
        property bool IsKeyBoard {
            bool get() { return interception_is_keyboard(_deviceIndex) != 0; }
        }
        property bool IsValid {
            bool get() { return _deviceIndex > 0 && !(interception_is_invalid(_deviceIndex) != 0); }
        }

    internal:
        Device(int index, Context^ context);
    };
}
