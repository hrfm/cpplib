#include "SiVolumeDetector.h"

using namespace std;
using namespace hrfm::events;

namespace hrfm{ namespace fs{
    
    // ======================================================================
    // SiVolumeDetector class.
    
    void SiVolumeDetector::init( vector<string> * ignoreVolumeList ){
        _ignoreVolumeList = ignoreVolumeList;
        if( _ignoreVolumeList->size() == 0 ){
            _ignoreVolumeList->push_back("Macintosh HD");
        }
    }
    
    void SiVolumeDetector::check( int throttle ){
        
        unsigned long int now = time(NULL);
        
        if( _ignoreVolumeList == NULL ){
            init();
        }
        
        if( throttle < now - _tick ){
            
            try{
                boost::filesystem::path dir("/Volumes");
                if( boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir) && !boost::filesystem::is_empty(dir) ){
                    string volume = "";
                    boost::filesystem::directory_iterator endItr;
                    for (boost::filesystem::directory_iterator p(dir); p != endItr; ++p) {
                        if (boost::filesystem::is_directory(*p)) {  //ディレクトリの時
                            string filename = p->path().filename().string();
                            // ignoreVolumeListに入っているかを調べる.
                            auto itr = std::find(_ignoreVolumeList->begin(),_ignoreVolumeList->end(),filename);
                            if( itr == _ignoreVolumeList->end() ){
                                volume = p->path().string();
                                break;
                            }
                        }
                    }
                    if( volume == "" && _path != "" ){
                        _path = volume;
                        dispatchEvent(new VolumeDetectorEvent(VolumeDetectorEvent::UNMOUNTED));
                    }else if( _path != volume ){
                        _path = volume;
                        dispatchEvent( new VolumeDetectorEvent( VolumeDetectorEvent::DETECTED ) );
                    }
                }else{
                    cout << "path is not correct" << endl;
                }
            }catch(...){
                cout << "SiVolumeDetector::check error!" << endl;
            }
            
            _tick = now;
            
        }
        
    }
    
    bool SiVolumeDetector::isDetected(){
        return _path != "";
    }
    
    string SiVolumeDetector::getPath(){
        return _path;
    }
    
    void SiVolumeDetector::unmount(){
        try{
            if( _path != "" ){
                dispatchEvent(new VolumeDetectorEvent(VolumeDetectorEvent::BEFORE_UNMOUNT));
                system( ("diskutil unmount \""+_path+"\"").c_str() );
            }
        }catch(...){}
    }
    
}}