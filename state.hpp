//
//  state.hpp
//  statemachine
//
//  Created by coderyi on 2018/9/14.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#ifndef state_hpp
#define state_hpp

#include <functional>
class Event;
class StateImpl;

class State {
public:
    typedef std::function<void(const Event*)> OnEnterCallback;
    typedef std::function<void(const Event*)> OnExitCallback;
    
    State();
    virtual ~State();
    
    void setOnEnterCallback(const OnEnterCallback& onEntered);
    void setOnExitCallback(const OnExitCallback& onExited);
    
private:
    // disable copy
    State(const State&);
    State& operator=(const State&);
    
    friend class StateMachineImpl;
    void onEntry(const Event*);
    void onExit(const Event*);
    
    StateImpl* const p_impl;
};
#endif /* state_hpp */
