#pragma once

#include <time.h>
#include "TimerEvent.h"

using namespace std;

namespace hrfm{ namespace utils{
    
    class Timer : public hrfm::events::EventDispatcher{
        
    public:
        
        Timer( float time = 1.0, int count = 0 );
        
        virtual void start();
        virtual void stop();
        virtual void update();
        virtual void setTime( float time, bool reset = false );
        
        float time;
        int   count;
        int   currentCount;
        clock_t startTime;
        
    private:
        
        bool _count(){
            dispatchEvent( new hrfm::events::TimerEvent( hrfm::events::TimerEvent::TIMER ) );
            if( 0 < count && count <= ++currentCount ){
                dispatchEvent( new hrfm::events::TimerEvent( hrfm::events::TimerEvent::TIMER_COMPLETE ) );
                stop();
                return true;
            }
            startTime+=time;
            return false;
        }
        
    };
    
}}