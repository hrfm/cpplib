#pragma once

#include <string>

using namespace std;

namespace hrfm { namespace events{
    
    class EventDispatcher;
    
    class Event{
        
        friend EventDispatcher;
        
	public:
    	
        Event(const std::string &type, bool cancelable = false):_type(type), _cancelable(cancelable){
            _canceled = false;
        };
        ~Event(){};
        
        //! イベントのタイプを取得します.
		const std::string type();
        
        //! このイベントがキャンセル可能かを調べます.
		const bool cancelable();
        
        virtual Event clone();
        
        virtual void cancel();
        
        void * target();
        void * listener();
        
        static const string COMPLETE;
        static const string DONE;
        static const string ERROR;
        
        static const string RESIZE;
        
        static const string ADDED;
        static const string REMOVED;
        static const string ADDED_TO_STAGE;
        static const string REMOVED_FROM_STAGE;
        
    protected:
        
        //! このイベントのタイプ.
        const std::string _type;
        
        //! このイベントがリスナ内でキャンセルが可能であるか.
		const bool _cancelable;
        
        //! cancel() によってキャンセルされていた場合 true になる.
        bool _canceled;
        
    protected:
        
        friend class EventDispatcher;
        
        void * _target;
        void * _listener;
        
    };
    
}}