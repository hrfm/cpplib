#include "DeclineWave.h"

namespace hrfm { namespace physics{
    
    DeclineWave::DeclineWave( float pow, float decline, float t ){
        mPower = pow;
        m_t = 0;
        mA = 2;
        mT = t;
        mDecline = decline;
    }
    DeclineWave::~DeclineWave(){}
    
    float DeclineWave::getPower(){
        return mPower;
    }
        
    float DeclineWave::getPosition(){
        return mPower * mA * sin( (M_PI*2.0) * (m_t/mT) );
    }
    
    bool DeclineWave::update(){
        m_t += 1;
        mPower *= mDecline;
        if( fabs(mPower) < 0.008 ){
            mPower = 0;
            return false;
        }
        return true;
    }
    
}}