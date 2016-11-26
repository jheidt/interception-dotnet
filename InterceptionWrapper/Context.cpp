#include "Stdafx.h"
#include "Context.h"

using namespace System;
using namespace InterceptionWrapper;

IntPtr Context::Handle::get()
{
    return _handle;
}

void Context::Handle::set(IntPtr val)
{
    if( _handle != IntPtr::Zero )
    {
        throw gcnew ArgumentException("handle is already set");
    }
    
    _handle = IntPtr(val);
}

Context::Context()
{
    Handle = IntPtr(interception_create_context());
    _data = gcnew array<Byte>(Context::StrokeSize);
    _devices = gcnew System::Collections::Generic::Dictionary<Int32, Device^>();
}

Context::!Context()
{
    if( _handle != IntPtr::Zero )
    {
        interception_destroy_context(_handle.ToPointer());
        _handle = IntPtr::Zero;
    }    
}

Context::~Context()
{
    Context::!Context();
}

void Context::SetFilter(FilterKind kind, unsigned short filter)
{
    InterceptionPredicate pred = nullptr;
    
    switch( kind ) 
    {
    case Context::FilterKind::KeyBoard:
        pred = interception_is_keyboard;
        break;
    case Context::FilterKind::Mouse:
        pred = interception_is_mouse;
        break;
    }

    if( pred == nullptr )
    {
        throw gcnew ArgumentException("FilterKind was not one of the expected values");
    }

    interception_set_filter(_handle.ToPointer(), pred, filter);
}

unsigned short Context::GetFilter(Device ^ device)
{
    if( device == nullptr )
    {
        throw gcnew ArgumentNullException("device is null");
    }
    if( !device->IsValid )
    {
        throw gcnew ArgumentException("device is not valid");
    }
    return interception_get_filter(_handle.ToPointer(), device->Index);
}

Device ^ InterceptionWrapper::Context::Wait()
{
    InterceptionDevice devIndex = interception_wait(_handle.ToPointer());
    if( devIndex <= 0 )
    {
        return nullptr;
    }
    return GetOrCreateDevice(devIndex);
}

Device ^ InterceptionWrapper::Context::Wait(unsigned long msDuration)
{
    InterceptionDevice devIndex = interception_wait_with_timeout(_handle.ToPointer(), msDuration);
    if( devIndex <= 0 ) {
        return nullptr;
    }
    return GetOrCreateDevice(devIndex);
}

int InterceptionWrapper::Context::Receive(Device^ device, int nStroke)
{
    Array::Clear(_data, 0, _data->Length);
    pin_ptr<Byte> ptrStroke = &_data[0];
    InterceptionStroke* ptrIS = reinterpret_cast<InterceptionStroke*>(ptrStroke);
    int rv = interception_receive(_handle.ToPointer(), device->Index, ptrIS, nStroke);
    return rv;
}

int InterceptionWrapper::Context::Send(Device^ device, KeyStroke keyboardData)
{
    System::Runtime::InteropServices::Marshal::Copy(IntPtr(&keyboardData), _data, 0, KeyStrokeSize);
    pin_ptr<Byte> ptrStroke = &_data[0];
    const InterceptionStroke* ptrIS = reinterpret_cast<InterceptionStroke*>(ptrStroke);
    int rv = interception_send(_handle.ToPointer(), device->Index, ptrIS, 1);
    return rv;
}

int InterceptionWrapper::Context::Send(Device^ device, MouseStroke mouseData)
{
    System::Runtime::InteropServices::Marshal::Copy(IntPtr(&mouseData), _data, 0, MouseStrokeSize);
    pin_ptr<Byte> ptrStroke = &_data[0];
    InterceptionStroke* ptrIS = reinterpret_cast<InterceptionStroke*>(ptrStroke);
    int rv = interception_send(_handle.ToPointer(), device->Index, ptrIS, 1);
    return rv;
}

array<Byte>^ InterceptionWrapper::Context::GetData()
{
    return _data;
}

MouseStroke InterceptionWrapper::Context::GetDataAsMouseStroke()
{
    pin_ptr<Byte> ptrStroke = &_data[0];
    MouseStroke rv = (MouseStroke)Marshal::PtrToStructure(IntPtr(ptrStroke), MouseStroke::typeid);
    return rv;
}

KeyStroke InterceptionWrapper::Context::GetDataAsKeyStroke()
{
    pin_ptr<Byte> ptrStroke = &_data[0];
    KeyStroke rv = (KeyStroke)Marshal::PtrToStructure(IntPtr(ptrStroke), KeyStroke::typeid);
    return rv;
}

Device ^ InterceptionWrapper::Context::GetOrCreateDevice(int index)
{
    Device^ rv = nullptr;
    if(_devices->TryGetValue(index, rv))
    {
        return rv;
    }
    
    rv = gcnew Device(index, this);
    _devices->Add(index, rv);
    return rv;

}
