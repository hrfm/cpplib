#include "DynamicMap.h"

using namespace std;

namespace hrfm { namespace utils{
    
    DynamicMap::DynamicMap(){};
    
    bool DynamicMap::hasValue( const string key ){
        return _values.find(key) != _values.end();
    };
    
}}