#include "Event.h"

namespace hrfm { namespace events{
    
    Event Event::clone(){
        Event evt(type());
        return evt;
    }
    
    const std::string Event::type(){
        return _type;
    };
    
    const bool Event::cancelable(){
        return _cancelable;
    };
    
    void Event::cancel(){
        _canceled = true;
    }
    
    void *Event::target(){
        return _target;
    };
    
    void *Event::listener(){
        return _listener;
    }
    
    // --- Static Event Types.
    
    const string Event::COMPLETE = "complete";
    const string Event::DONE     = "done";
    const string Event::ERROR    = "error";
    
    const string Event::RESIZE = "resize";
    
    const string Event::ADDED   = "added";
    const string Event::REMOVED = "removed";
    const string Event::ADDED_TO_STAGE     = "added_to_stage";
    const string Event::REMOVED_FROM_STAGE = "removed_from_stage";
    
}}