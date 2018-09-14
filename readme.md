一个有限状态机的C++实现

状态机有几个特征

- 状态（state）总数是有限的
- 任意时刻，只处在一种状态之中
- 某种条件下，会从一种状态转变（transition）到另一种状态


状态机能够很好的管理复杂业务。适用于有一个明确 且复杂的状态流的场景。状态机能够很好的提高代码的可维护性和可测试性。


示例

```
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

```
