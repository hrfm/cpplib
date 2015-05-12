#include "WaveNode.h"

using namespace std;

namespace hrfm { namespace physics{
    
    WaveNode::WaveNode(){
        mCurrent = 0;
        mBeforeLeft  = 0;
        mBeforeRight = 0;
        mSumLeft  = 0;
        mSumRight = 0;
    }
    
    float WaveNode::getLeft(){
        return mBeforeLeft;
    }
    
    float WaveNode::getRight(){
        return mBeforeRight;
    }
    
    void WaveNode::addWave( float pow, float decline, float t ){
        mWaves.push_back( new DeclineWave( pow, decline, t ) );
    }
    
    void WaveNode::prepare(){
        mCurrent = 0;
        mBeforeLeft  = mSumLeft;
        mBeforeRight = mSumRight;
    }
    
    float WaveNode::update( float left, float right ){
        
        if( 0 < mWaves.size() ){
            mCurrent = 0;
            vector<DeclineWave*>::iterator it = mWaves.begin();  // イテレータのインスタンス化
            while( it != mWaves.end() ){
                if( !(*it)->update() ){
                    mWaves.erase(it);
                }else{
                    mCurrent += (*it)->getPosition();
                    ++it;
                }
            }
        }
        
        mSumLeft  = mCurrent + left * mDecline;
        mSumRight = mCurrent + right * mDecline;
        
        mCurrent += left + right;
        
        return mCurrent;
        
    }
    
}}