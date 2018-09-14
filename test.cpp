//
//  main.cpp
//  statemachine
//
//  Created by coderyi on 2018/9/14.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#include "event.hpp"
#include "state.hpp"
#include "statemachine.hpp"

#include <functional>
#include <iostream>
int main()
{
    StateMachine stateMachine;
    
    stateMachine.setOnStartCallback([] () { std::cout << "state machine started" << std::endl; });
    stateMachine.setOnStopCallback([] () { std::cout << "state machine stopped" << std::endl; });
    
    State* state1 = new State();
    state1->setOnEnterCallback([] (const Event*) { std::cout << "entering state1" << std::endl; });
    state1->setOnExitCallback([] (const Event*) { std::cout << "exiting state1" << std::endl; });
    
    State* state2 = new State();
    state2->setOnEnterCallback([] (const Event*) { std::cout << "entering state2" << std::endl; });
    state2->setOnExitCallback([] (const Event*) { std::cout << "exiting state2" << std::endl; });
    
    State* state3 = new State();
    state3->setOnEnterCallback([] (const Event*) { std::cout << "entering state3" << std::endl; });
    state3->setOnExitCallback([] (const Event*) { std::cout << "exiting state3" << std::endl; });
    
    stateMachine.addTransition(12, state1, state2);
    stateMachine.addTransition(13, state1, state3);
    stateMachine.addTransition(23, state2, state3);
    stateMachine.addTransition(31, state3, state1);
    stateMachine.setInitialState(state1);
    
    stateMachine.start();
    
    stateMachine.postEvent(new Event(12));
    stateMachine.postEvent(new Event(23));
    stateMachine.postEvent(new Event(31));
    stateMachine.postEvent(new Event(13));
    
    return 0;
}
