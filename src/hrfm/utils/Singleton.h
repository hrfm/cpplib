#pragma once

#include <memory>

namespace hrfm{ namespace utils{
    
    template <class T>
    class Singleton{
        
    public:
        
        static T& getInstance(){
            static typename T::singleton_ptr s_singleton(T::createInstance());
            return getReference(s_singleton);
        }
        
    private:
        
        typedef std::unique_ptr<T> singleton_ptr;
        
        inline static T *createInstance(){
            return new T();
        }
        
        inline static T &getReference( const singleton_ptr &ptr ){
            return *ptr;
        }
        
    protected:
        
        Singleton(){}
        
    private:
        
        Singleton(const Singleton &) = delete;
        Singleton& operator=(const Singleton &) = delete;
        Singleton(Singleton &&) = delete;
        Singleton& operator=(Singleton &&) = delete;
        
    };
    
}}
