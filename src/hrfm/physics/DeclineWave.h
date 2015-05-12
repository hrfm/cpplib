#pragma once

#include <list>
#include <math.h>

using namespace std;

namespace hrfm { namespace physics{
    
    class DeclineWave{
        
    public:
        
        DeclineWave( float pow, float decline = 0.998, float t = 100.0 );
        ~DeclineWave();
        
        float getPower();
        
        float getPosition();
        
        bool update();
        
    private:
        
        float mPower;
        float m_t;
        float mA;
        float mT;
        float mDecline;
        
    };
    
}}