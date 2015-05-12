#include "TriggerEvent.h"

namespace hrfm { namespace events{
    
    const std::string TriggerEvent::triggerName(){
        return _triggerName;
    };
    
    // --- Static Event Types.
    
    const string TriggerEvent::TRIGGER = "trigger";
    
}}