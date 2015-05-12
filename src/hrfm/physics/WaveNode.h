#pragma once

#include <vector>
#include <math.h>
#include "DeclineWave.h"

using namespace std;

namespace hrfm { namespace physics{
    
    class WaveNode {
        
    public:
        
        WaveNode();
        
        float getLeft();
        
        float getRight();
        
        void addWave( float pow, float decline, float t );
        
        void prepare();
        
        float update( float left, float right );
        
    private:
        
        float mDecline = 0.992;
        vector<DeclineWave*> mWaves;
        
        float mCurrent;
        float mBeforeLeft;
        float mBeforeRight;
        float mSumLeft;
        float mSumRight;
        
    };
    
}}