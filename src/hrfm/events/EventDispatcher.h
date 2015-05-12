#pragma once

#include "Event.h"
#include <map>
#include <list>
#include <iostream>

using namespace std;

namespace hrfm { namespace events{
    
    /* ---------------------------------------------------------------------------------------------------
     
     リスナの参照等はこのクラスを継承した EventListener クラスにて実行時に解決する.
     このクラスは EventDispatcher 内でリスナを std::list で保存するための基底となるクラス.
     
     */
    class IEventListener{
    public:
        IEventListener(){};
        ~IEventListener(){};
        virtual bool operator==( IEventListener * listener ){
            cout << "IEventListener::==()" << endl;
            return this == listener;
        }
        virtual void exec( Event * event ){
            cout << "IEventListener::exec()" << endl;
        }
    };
    
    /* ---------------------------------------------------------------------------------------------------
     
     リスナであるメンバ関数の this 参照と関数ポインタを保持しイベント発生時に関数の実行を行うためのクラス.
     
     */
    template <class T, class E> class EventListener : public IEventListener{
    public:
        EventListener( T * listener, void (T::*handler)(E*) ){
            IEventListener();
            _listener = listener;
            _handler  = handler;
        }
        bool operator==( IEventListener * listener ){
            if( EventListener<T,E> * l = dynamic_cast<EventListener<T,E>*>(listener) ){
                return (*this) == l;
            }else{
                return false;
            }
        }
        bool operator==( EventListener<T,E> * listener ){
            return ( this == listener || ( listener->_listener == this->_listener && listener->_handler == this->_handler ) );
        }
        void exec( Event * event ){
            if( E * evt = dynamic_cast<E*>(event) ){
                (_listener->*_handler)(evt);
            }
        }
    private:
        T * _listener;
        void (T::*_handler)(E*);
    };
    
    
    /* ---------------------------------------------------------------------------------------------------
     
     イベントリスナの登録とイベントの通知を行う Observer クラス.
     
     */
    class EventDispatcher{
	public:
        
        EventDispatcher();
        ~EventDispatcher();
        
        //! Event を発行し該当するリスナを実行します.
        void dispatchEvent(Event * event);
        
        /*
         
         リスナを追加します.
         既に登録済みの場合は登録し直します.
         
         */
        template <class T, class E>
        void addEventListener( const std::string &type, T * listener, void (T::*handler)(E*), int priority = 0, bool useWeakReference = false ){
            removeEventListener( type, listener, handler );
            _listenerList[type][priority].push_back( new EventListener<T,E>(listener,handler) );
        }
        
        //! 登録されたリスナを解除します.
        template <class T, class E>
        void removeEventListener( const std::string &type, T * listener, void (T::*handler)(E*) ){
            // Leave if no event registered
            if(!hasEventListener(type)){
                return;
            }
            // --- Remove. ---
            removeEventListener( type, new EventListener<T,E>(listener,handler) );
        }
        
        //! 登録されたリスナを解除します.
        void removeEventListener( const std::string &type, IEventListener * listener ){
            
            // Leave if no event registered
            if(!hasEventListener(type)){
                return;
            }
            
            if( !_runningDispatch ){
                
                // A reference to keep code clean
                map<int,list<IEventListener*>> &allListeners = _listenerList[type];
                map<int,list<IEventListener*>>::iterator it  = allListeners.begin();
                map<int,list<IEventListener*>>::iterator end = allListeners.end();
                
                // Iterate through all functions in the event, from high proproty to low
                while( it != end ){
                    
                    list<IEventListener*> &funcList = it->second;
                    list<IEventListener*>::iterator it_f  = funcList.begin();
                    list<IEventListener*>::iterator end_f = funcList.end();
                    
                    // Check Callbacks.
                    while( it_f!=end_f ){
                        if( (*listener) == (*it_f) ){
                            it_f = funcList.erase(it_f);
                        }else{
                            ++it_f;
                        }
                    }
                    
                    if( funcList.empty() ){
                        it = allListeners.erase(it);
                    }else{
                        ++it;
                    }
                    
                }
                
                if( allListeners.empty() ){
                    _listenerList.erase(type);
                }
                
            }else{
                
                _removeList.push_back(listener);
                
            }
            
        };
        
        //! 指定した type のイベントリスナが登録されているかを調べます.
        bool hasEventListener( const std::string &type );
        
	protected:
        
        void * _target;
        
    private:
        
        bool _runningDispatch;
        std::list<IEventListener*> _removeList;
        std::map<const std::string, std::map<int, std::list<IEventListener*> > > _listenerList;
        
    };
    
}}