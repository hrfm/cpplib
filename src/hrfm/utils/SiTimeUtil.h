#pragma once

#include <time.h>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>

#include "Singleton.h"
#include "TimeUtilEvent.h"
#include "TimerEvent.h"

using namespace std;

namespace hrfm{ namespace utils{
    
    class Timer;
    
    struct TimingData{
    public:
        
        TimingData( int minutes, int hour = -1 );
        ~TimingData(){}
        
        void init( int minutes, int hour );
        
        //! 引数に指定した時刻と比較しタイミングと合致した場合 true を返します.
        bool check( int hour, int minutes );
        
    private:
        
        int _hour;
        int _minutes;
        int _beforeHour;
        int _beforeMinutes;
        
        
    };
    
    class SiTimeUtil : public Singleton<SiTimeUtil>, public hrfm::events::EventDispatcher{
        
    public:
        
        /*
         
         現在時刻の更新と TimingData を調べてのイベントの発行を行います.
         
         */
        virtual void update();
        
        //! 現在時刻の情報を取得します.
        virtual tm * getTimeinfo();
        
        //! 現在の曜日を 0-6 の数値で取得します.
        virtual int getWeekDay();
        
        //! 現在の曜日を sun|mon|tue|wed|thu|fri|sat の３文字の文字列で取得します.
        virtual string getWeekDayString();
        
        //! 現在の日を取得します.
        virtual int getDay();
        
        //! 現在の時刻(時)を取得します.
        virtual int getHour();
        
        //! 現在の時刻(分)を取得します.
        virtual int getMinutes();
        
        //! 現在の時刻(秒)を取得します.
        virtual int getSeconds();
        
        //! 現在時刻を引数で指定したフォーマットの文字列にして取得します.
        virtual string getTimeString(const char *format);
        
        //! イベントを発行するタイミングを追加します.
        virtual void addTiming( const string type, TimingData * timing );
        
        //! イベントを発行するタイミングを追加し,かつイベントリスナも同時に登録します.
        template<class T,class E>
        void addTiming( const string type, TimingData * timing, T * listener, void (T::*handler)(E*) ){
            addTiming( type, timing );
            addEventListener( type, listener, handler );
        }
        
        virtual void removeTiming( const string type );
        
        virtual void removeTiming( const string type, TimingData * timing );
        
        // --- Timer 管理用.
        
        void addTimer( Timer * timer );
        
        void removeTimer( Timer * timer );
        
        bool eraseFromTimerList( Timer * timer );
        
    private:
        
        friend class Singleton<SiTimeUtil>;
        
        SiTimeUtil(){
            
            hrfm::events::EventDispatcher();
            
            time_t rawtime = time(NULL);
            time(&rawtime);
            _timeinfo = localtime(&rawtime);
            
            update();
            
        }
        
        // --- Timer.
        
        vector<Timer*> _timerList;
        
        // --- TimeUtil.
        
        const string _days[7] = {"sun","mon","tue","wed","thu","fri","sat"};
        
        struct tm * _timeinfo;
        struct tm * _beforeTimeinfo;
        
        map<const string,list<TimingData*>> _timingList;
        
        
    };
    
    class Timer : public hrfm::events::EventDispatcher{
        
    public:
        
        Timer( float time = 1.0, int count = 0 ){
            hrfm::events::EventDispatcher();
            this->time  = time;
            this->count = count;
        }
        
        virtual void start(){
            this->startTime    = ci::app::getElapsedSeconds();
            this->currentCount = 0;
            SiTimeUtil::getInstance().addTimer( this );
        }
        
        virtual void stop(){
            SiTimeUtil::getInstance().removeTimer( this );
        }
        
        virtual void update( float elapsedTime ){
            
            while( time <= elapsedTime - startTime ){
                if( _count() ){
                    break;
                }
            }
            
        }
        
        virtual void setTime( float time, bool reset = false ){
            this->time      = time;
            if( reset ){
                _count();
                this->startTime = ci::app::getElapsedSeconds();
            }
        }
        
        float time;
        int   count;
        int   currentCount;
        float startTime;
        
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