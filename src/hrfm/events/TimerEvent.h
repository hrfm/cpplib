#pragma once

#include "EventDispatcher.h"

namespace hrfm { namespace events{
    
    // --- Event for OSC. ---
    
    class TimerEvent : public hrfm::events::Event{
        
    public:
        
        TimerEvent( const std::string &type ):Event(type){}
        ~TimerEvent(){}
        
        Event clone(){
            TimerEvent evt( type() );
            return evt;
        }
        
        static const string TIMER;
        static const string TIMER_COMPLETE;
        
    };
    
}}