//
//  statemachine.hpp
//  statemachine
//
//  Created by coderyi on 2018/9/14.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#ifndef statemachine_hpp
#define statemachine_hpp

#include <cstdint>
#include <functional>

class Event;
class State;
class StateMachineImpl;

class StateMachine
{
public:
    typedef std::function<void(void)> OnStartCallback;
    typedef std::function<void(void)> OnStopCallback;
    
    StateMachine();
    virtual ~StateMachine();
    
    void addTransition(uint32_t eventType, State* from, State* to);
    void setInitialState(State* state);
    
    void setOnStartCallback(const OnStartCallback& onStarted);
    void setOnStopCallback(const OnStopCallback& onStopped);
    
    void start();
    void stop();
    
    void postEvent(Event* event);
    
private:
    StateMachine(const StateMachine&);
    StateMachine& operator=(const StateMachine&);
    
    StateMachineImpl* const p_impl;
};
#endif /* statemachine_hpp */
