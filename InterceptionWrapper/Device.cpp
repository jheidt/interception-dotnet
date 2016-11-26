#include "Stdafx.h"
#include "Device.h"

using namespace System;

namespace InterceptionWrapper {
    
    Device::Device(int index, Context^ context)
    {   
        _deviceIndex = index;
        _context = context;
    }
}