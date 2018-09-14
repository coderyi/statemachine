//
//  event.hpp
//  statemachine
//
//  Created by coderyi on 2018/9/14.
//  Copyright © 2018年 coderyi. All rights reserved.
//

#ifndef event_hpp
#define event_hpp

#include <cstdint>

class Event
{
public:
    Event(uint32_t type);
    virtual ~Event();
    
    uint32_t type() const;
    
private:
    Event(const Event&);
    Event& operator=(const Event&);
    
    uint32_t m_type;
};


class StartEvent : public Event
{
public:
    StartEvent();
    ~StartEvent();
    
    static const uint32_t EVENT_TYPE;
};

#endif /* event_hpp */
