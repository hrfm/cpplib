#pragma once

#include "EventDispatcher.h"

namespace hrfm { namespace events{
    
    // --- Event for OSC. ---
    
    class VolumeDetectorEvent : public hrfm::events::Event{
        
    public:
        
        VolumeDetectorEvent( const std::string &type ):Event(type){}
        ~VolumeDetectorEvent(){}
        
        Event clone(){
            VolumeDetectorEvent evt( type() );
            return evt;
        }
        
        static const string DETECTED;
        static const string BEFORE_UNMOUNT;
        static const string UNMOUNTED;
        
    };
    
    
}}