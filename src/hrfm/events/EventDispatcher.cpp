#include "EventDispatcher.h"

using namespace std;

namespace hrfm { namespace events {
    
    EventDispatcher::EventDispatcher(){
        _target = this;
    };
    
    EventDispatcher::~EventDispatcher(){
        _target = NULL;
        _listenerList.clear();
    };
    
    void EventDispatcher::dispatchEvent(Event * event){
        
        string type = event->type();
        
        // Leave if no event registered
        if( !hasEventListener(type) ){
            return;
        }
        
        event->_target = this;
        
        _runningDispatch = true;
        {
            
            // A reference to keep code clean
            std::map<int, std::list<IEventListener*> > &list = _listenerList[event->type()];

            // Iterate through all functions in the event, from high proproty to low
            for( std::map<int, std::list<IEventListener*> >::reverse_iterator it=list.rbegin(); it!=list.rend(); ++it ){
                
                std::list<IEventListener*> &funcList = it->second;
                std::list<IEventListener*>::iterator it_f=funcList.begin();
                std::list<IEventListener*>::iterator end_f=funcList.end();
                
                // Execute callbacks
                while( it_f != end_f ){
                    (*it_f++)->exec(event);
                    // return immediately if cancel() called.
                    if( event->_canceled == true ){
                        _runningDispatch = false;
                        return;
                    }
                }
                
            }
            
        }
        _runningDispatch = false;
        
        // If call removeEventListener during dispatchEvent. Remove listener after dispatch.
        
        if( 0 < _removeList.size() ){
            // Iterate through all functions in the event, from high proproty to low
            for( std::list<IEventListener*>::iterator it=_removeList.begin(); it!=_removeList.end(); ++it ){
                removeEventListener( type, (*it) );
            }
            _removeList.clear();
        }
        
    };
    
    bool EventDispatcher::hasEventListener(const std::string &type){
        return ( _listenerList.find(type) != _listenerList.end() );
    };
    
}}
