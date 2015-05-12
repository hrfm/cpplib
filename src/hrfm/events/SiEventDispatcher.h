#pragma once

#include "EventDispatcher.h"
#include "Singleton.h"

namespace hrfm { namespace events{
    
    class SiEventDispatcher : public hrfm::utils::Singleton<SiEventDispatcher>, public hrfm::events::EventDispatcher{
        
    public:
        
    private:
        
        friend class hrfm::utils::Singleton<SiEventDispatcher>;
        
        SiEventDispatcher(){}
        
    };
    
}}