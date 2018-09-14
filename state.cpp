//
//  state.cpp
//  statemachine
//
//  Created by coderyi on 2018/9/14.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#include "state.hpp"
#include "event.hpp"

struct StateImpl
{
    State::OnEnterCallback onEntered;
    State::OnExitCallback onExited;
};



State::State()
: p_impl(new StateImpl)
{
}

State::~State()
{
    delete p_impl;
}

void State::setOnEnterCallback(const OnEnterCallback& onEntered)
{
    p_impl->onEntered = onEntered;
}

void State::setOnExitCallback(const OnExitCallback& onExited)
{
    p_impl->onExited = onExited;
}

void State::onEntry(const Event* event)
{
    if (p_impl->onEntered) {
        p_impl->onEntered(event);
    }
}

void State::onExit(const Event* event)
{
    if (p_impl->onExited) {
        p_impl->onExited(event);
    }
}
