//
//  event.cpp
//  statemachine
//
//  Created by coderyi on 2018/9/14.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#include "event.hpp"

Event::Event(uint32_t type)
: m_type(type)
{
}

Event::~Event()
{
}

uint32_t Event::type() const
{
    return m_type;
}


StartEvent::StartEvent()
: Event(EVENT_TYPE)
{
}

StartEvent::~StartEvent()
{
}

const uint32_t StartEvent::EVENT_TYPE(1);
