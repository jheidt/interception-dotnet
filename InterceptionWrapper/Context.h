#pragma once

#include "Device.h"
#include <stddef.h>

namespace InterceptionWrapper {

    using namespace System;

    public ref class Context
    {
    public:
        property IntPtr Handle
        {
        public:
            IntPtr get();
        protected: 
             void set(IntPtr value);
        }
        
        Context();
        !Context();
        ~Context();

        enum class FilterKind
        {
            KeyBoard,
            Mouse
        };

        void SetFilter(FilterKind kind, unsigned short filter);
        unsigned short GetFilter(Device^ device);

        Device^ Wait();
        Device^ Wait(unsigned long msDuration);

        int Receive(Device^ device, int nStroke);
        int Send(Device^ device, KeyStroke keyStroke);
        int Send(Device^ device, MouseStroke mouseStroke);

        array<Byte>^ GetData();
        MouseStroke GetDataAsMouseStroke();
        KeyStroke GetDataAsKeyStroke();

        static const size_t StrokeSize = sizeof(MouseStroke);
        static const size_t MouseStrokeSize = sizeof(MouseStroke);
        static const size_t KeyStrokeSize = sizeof(InterceptionKeyStroke);

        static void DebugDump()
        {
            
            System::Diagnostics::Debug::WriteLine("InterceptionMouseStroke:");
            System::Diagnostics::Debug::WriteLine("state: {0}", offsetof(InterceptionMouseStroke,state));
            System::Diagnostics::Debug::WriteLine("flags: {0}", offsetof(InterceptionMouseStroke, flags));
            System::Diagnostics::Debug::WriteLine("rolling: {0}", offsetof(InterceptionMouseStroke, rolling));
            System::Diagnostics::Debug::WriteLine("x: {0}", offsetof(InterceptionMouseStroke, x));
            System::Diagnostics::Debug::WriteLine("y: {0}", offsetof(InterceptionMouseStroke, y));
            System::Diagnostics::Debug::WriteLine("information: {0}", offsetof(InterceptionMouseStroke, information));
            
            System::Diagnostics::Debug::WriteLine("MouseStroke:");
            System::Diagnostics::Debug::WriteLine("state: {0}", Marshal::OffsetOf(MouseStroke::typeid,"state"));
            System::Diagnostics::Debug::WriteLine("flags: {0}", Marshal::OffsetOf(MouseStroke::typeid, "flags"));
            System::Diagnostics::Debug::WriteLine("rolling: {0}", Marshal::OffsetOf(MouseStroke::typeid, "rolling"));
            System::Diagnostics::Debug::WriteLine("x: {0}", Marshal::OffsetOf(MouseStroke::typeid, "x"));
            System::Diagnostics::Debug::WriteLine("y: {0}", Marshal::OffsetOf(MouseStroke::typeid, "y"));
            System::Diagnostics::Debug::WriteLine("information: {0}", Marshal::OffsetOf(MouseStroke::typeid, "information"));

            // Marshal::OffsetOf(MouseStroke::typeid, "state")
        }
        
    private:
        Device^ GetOrCreateDevice(int index);

        IntPtr _handle = IntPtr::Zero;
        bool _hasFilters = false;
        array<Byte>^ _data; // = gcnew array<Byte>(sizeof(InterceptionMouseStroke));
        System::Collections::Generic::Dictionary<int,Device^>^ _devices;
        
    };
}
