#pragma once

#include <map>
#include <string>

using namespace std;

namespace hrfm { namespace utils{
    
    class DynamicMap{
        
    public:
        
        DynamicMap();
        
        bool hasValue( const string key );
        
        template <class T> void setValue( const string key, T value ){
            _values[key] = new MapValue<T>( value );
        };
        
        template <class T> T getValue( const string key ){
            if( hasValue( key ) ){
                if( MapValue<T> * v = dynamic_cast<MapValue<T>*>( _values[key] ) ){
                    return v->value;
                }
            }
            return T();
        };
        
        template <class T> T * getValuePtr( const string key ){
            if( hasValue( key ) ){
                if( MapValue<T> * v = dynamic_cast<MapValue<T>*>( _values[key] ) ){
                    return &(v->value);
                }
            }
            return NULL;
        };
        
    private:
        
        class IMapValue{
        public:
            IMapValue(){ init(); };
            ~IMapValue(){};
            virtual void init(){}
        };
        
        template <class T> class MapValue : public IMapValue{
        public:
            MapValue( T v ):value(v){
                IMapValue();
            }
            T value;
        };
        
        map<const string,IMapValue*> _values;
        
    };
    
}}