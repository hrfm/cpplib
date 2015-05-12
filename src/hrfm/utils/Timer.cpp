#include "Timer.h"
#include "SiTimeUtil.h"

using namespace std;
using namespace hrfm::events;

namespace hrfm{ namespace utils{
    
    Timer::Timer( float time, int count ){
        hrfm::events::EventDispatcher();
        this->time  = time;
        this->count = count;
    }
    
    void Timer::start(){
        this->startTime    = clock();
        this->currentCount = 0;
        SiTimeUtil::getInstance().addTimer( this );
    }
    
    void Timer::stop(){
        SiTimeUtil::getInstance().removeTimer( this );
    }
    
    void Timer::update(){
        while( time <= clock() - startTime ){
            if( _count() ){
                break;
            }
        }
        
    }
    
    void Timer::setTime( float time, bool reset ){
        this->time = time;
        if( reset ){
            _count();
            this->startTime = clock();
        }
    }
    
}}