#include "SiTimeUtil.h"

using namespace std;
using namespace hrfm::events;

namespace hrfm{ namespace utils{
    
    // ======================================================================
    // TimingData class.
    
    TimingData::TimingData( int minutes, int hour ){
        init( minutes, hour );
    }
    
    void TimingData::init( int minutes, int hour ){
        
        if( hour < 0 ){
            _hour = -1;
        }else{
            _hour = hour % 24;
        }
        
        _minutes = minutes % 60;
        
        _beforeHour    = SiTimeUtil::getInstance().getHour();
        _beforeMinutes = SiTimeUtil::getInstance().getMinutes();
        
    }
    
    //! 引数に指定した時刻と比較しタイミングと合致した場合 true を返します.
    bool TimingData::check( int hour, int minutes ){
        
        bool flag = false;
        
        if( _beforeMinutes != minutes && _minutes == minutes ){
            if( _hour < 0 || _hour == hour ){
                flag = true;
            }
        }
        
        _beforeHour    = hour;
        _beforeMinutes = minutes;
        
        return flag;
        
    }
    
    // ======================================================================
    // SiTimeUtil class.
    
    void SiTimeUtil::update(){
        
        // --- Update Timeinfo. ---
        
        int beforeHour = getHour();
        int beforeMin  = getMinutes();
        
        time_t rawtime = time(NULL);
        time(&rawtime);
        _timeinfo = localtime(&rawtime);
        
        // --- Check Timings. ---
        
        int hour    = getHour();
        int minutes = getMinutes();
        
        if( beforeHour != hour ){
            dispatchEvent( new TimeUtilEvent( TimeUtilEvent::CHANGE_HOUR, _timeinfo ) );
        }
        
        if( beforeMin != minutes ){
            dispatchEvent( new TimeUtilEvent( TimeUtilEvent::CHANGE_MINUTES, _timeinfo ) );
        }
        
        map<const string,list<TimingData*>>::iterator it,end;
        
        for( it = _timingList.begin(), end = _timingList.end(); it!=end; it++ ){
            
            const string type            = it->first;
            list<TimingData*> & dataList = it->second;
            list<TimingData*>::iterator it_t, end_t;
            
            for( it_t = dataList.begin(), end_t = dataList.end(); it_t!=end_t; ++it_t){
                if( (*it_t)->check( hour, minutes ) ){
                    cout << "dispatch!!" << endl;
                    dispatchEvent( new TimeUtilEvent( type, _timeinfo ) );
                }
            }
            
        }
        
        // --- Timer.
        
        float elapsedTime = ci::app::getElapsedSeconds();
        for( auto itr=_timerList.begin(),end=_timerList.end(); itr!=end; ++itr ){
            (*itr)->update(elapsedTime);
        }
        
    }
    
    tm * SiTimeUtil::getTimeinfo(){
        return _timeinfo;
    }
    
    int SiTimeUtil::getWeekDay(){
        return _timeinfo->tm_wday;
    }
    
    string SiTimeUtil::getWeekDayString(){
        return _days[_timeinfo->tm_wday];
    }
    
    int SiTimeUtil::getDay(){
        return _timeinfo->tm_yday;
    }
    
    int SiTimeUtil::getHour(){
        return _timeinfo->tm_hour;
    }
    
    int SiTimeUtil::getMinutes(){
        return _timeinfo->tm_min;
    }
    
    int SiTimeUtil::getSeconds(){
        return _timeinfo->tm_sec;
    }
    
    string SiTimeUtil::getTimeString(const char *format){
        char str[256];
        strftime( str, 255, format, _timeinfo );
        string s = str;
        return s;
    }
    
    void SiTimeUtil::addTiming( const string type, TimingData * timing ){
        _timingList[type].push_back( timing );
    }
    
    void SiTimeUtil::removeTiming( const string type ){
        _timingList.erase(type);
    }
    
    void SiTimeUtil::removeTiming( const string type, TimingData * timing ){
        _timingList[type].remove(timing);
    }
    
    // --- Timer
    
    void SiTimeUtil::addTimer( Timer * timer ){
        eraseFromTimerList(timer);
        _timerList.push_back(timer);
    }
    
    void SiTimeUtil::removeTimer( Timer * timer ){
        eraseFromTimerList(timer);
    }
    
    inline bool SiTimeUtil::eraseFromTimerList( Timer * timer ){
        auto itr = std::remove_if(_timerList.begin(),_timerList.end(),[timer](Timer* t)->bool{
            return t == timer;
        });
        if( itr == _timerList.end() ){
            return false;
        }
        _timerList.erase( itr, _timerList.end() );
        return true;
    }
    
}}