//
//  statemachine.cpp
//  statemachine
//
//  Created by coderyi on 2018/9/14.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#include "statemachine.hpp"
#include "event.hpp"
#include "state.hpp"

#include <map>
#include <stdexcept>
#include <set>


class StateMachineImpl
{
public:
    StateMachineImpl();
    ~StateMachineImpl();
    
    void addTransition(uint32_t eventType, State* from, State* to);
    void setInitialState(State* state);
    
    void setOnStartCallback(const StateMachine::OnStartCallback& onStarted);
    void setOnStopCallback(const StateMachine::OnStopCallback& onStopped);
    
    void start();
    void stop();
    
    void postEvent(Event* event);
    
private:
    std::map<std::pair<State*, uint32_t>, State*> m_transitions;
    std::set<State*> m_states;
    StateMachine::OnStartCallback m_onStarted;
    StateMachine::OnStopCallback m_onStopped;
    State* m_currentState;
    State* m_initialState;
};

StateMachineImpl::StateMachineImpl()
: m_currentState(0), m_initialState(0)
{
}

StateMachineImpl::~StateMachineImpl()
{
    stop();
    
    for (auto i = m_states.begin(); i != m_states.end(); ++i)
        delete *i;
}

void StateMachineImpl::addTransition(uint32_t eventType, State* from, State* to)
{
    if (eventType == 0)
        throw std::invalid_argument("StateMachine::addTransition(): Invalid 'event' argument.");
    if (from == 0)
        throw std::invalid_argument("StateMachine::addTransition(): Invalid 'from' argument.");
    if (to == 0)
        throw std::invalid_argument("StateMachine::addTransition(): Invalid 'to' argument.");
    
    std::pair<State*, uint32_t> source(from, eventType);
    if (m_transitions.find(source) != m_transitions.end())
        throw std::invalid_argument("StateMachine::addTransition(): Transition already exists.");
    
    m_transitions.insert(std::pair<std::pair<State*, uint32_t>, State*>(source, to));
    m_states.insert(from);
    m_states.insert(to);
}

void StateMachineImpl::setInitialState(State* state)
{
    if (state == 0 || m_states.find(state) == m_states.end())
        throw std::invalid_argument("StateMachine::setInitialState(): Invalid 'state' argument.");
    
    m_initialState = state;
}

void StateMachineImpl::setOnStartCallback(const StateMachine::OnStartCallback& onStarted)
{
    m_onStarted = onStarted;
}

void StateMachineImpl::setOnStopCallback(const StateMachine::OnStopCallback& onStopped)
{
    m_onStopped = onStopped;
}

void StateMachineImpl::start()
{
    if (m_states.size() == 0 || m_transitions.size() == 0)
        throw std::logic_error("StateMachine::start(): No state / transition set.");
    if (m_initialState == 0)
        throw std::logic_error("StateMachine::start(): Initial state not set.");
    if (m_currentState != 0)
        throw std::logic_error("StateMachine::start(): Already started.");
    
    if (m_onStarted)
        m_onStarted();
    
    postEvent(new StartEvent());
}

void StateMachineImpl::stop()
{
    if (m_currentState == 0)
        throw std::logic_error("StateMachine::stop(): Not started yet.");
    
    m_currentState = 0;
    
    if (m_onStopped)
        m_onStopped();
}

void StateMachineImpl::postEvent(Event* event)
{
    if (event == 0)
        throw std::invalid_argument("StateMachine::postEvent(): Invalid 'event' argument.");
    
    if (event->type() == 0)
        throw std::invalid_argument("StateMachine::postEvent(): Invalid 'event' argument.");
    
    State* nextState = 0;
    if (event->type() == StartEvent::EVENT_TYPE) {
        if (m_currentState != 0)
            throw std::logic_error("StateMachine::postEvent(): Can not post StartEvent to already started state machine.");
        
        nextState = m_initialState;
    } else {
        if (m_currentState == 0)
            throw std::logic_error("StateMachine::postEvent(): State machine not started yet.");
        
        auto i = m_transitions.find(std::pair<State*, uint32_t>(m_currentState, event->type()));
        if (i == m_transitions.end())
            throw std::logic_error("StateMachine::postEvent(): No known transition for the current state and given event.");
        
        nextState = i->second;
    }
    
    if (m_currentState != 0)
        m_currentState->onExit(event);
    nextState->onEntry(event);
    m_currentState = nextState;
}


// public implementation

StateMachine::StateMachine()
: p_impl(new StateMachineImpl)
{
}

StateMachine::~StateMachine()
{
    delete p_impl;
}

void StateMachine::addTransition(uint32_t eventType, State* from, State* to)
{
    p_impl->addTransition(eventType, from, to);
}

void StateMachine::setInitialState(State* state)
{
    p_impl->setInitialState(state);
}

void StateMachine::setOnStartCallback(const OnStartCallback& onStarted)
{
    p_impl->setOnStartCallback(onStarted);
}

void StateMachine::setOnStopCallback(const OnStopCallback& onStopped)
{
    p_impl->setOnStopCallback(onStopped);
}

void StateMachine::start()
{
    p_impl->start();
}

void StateMachine::stop()
{
    p_impl->stop();
}

void StateMachine::postEvent(Event* event)
{
    p_impl->postEvent(event);
}
