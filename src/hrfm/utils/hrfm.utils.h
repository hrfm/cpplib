#pragma once

#include <map>
#include <string>
#include <iostream>
#include <regex>

using namespace std;
using namespace boost;

namespace hrfm { namespace utils{

    // --------

    template <typename Of, typename What>
    static bool instanceof(const What &w){
        return dynamic_cast<const Of*>(&w) != 0;
    }
    
    // ----------
    
    static int GCD( int a, int b ){
        int c;
        if (a < b) {
            a += b;
            b =  a-b;
            a -= b;
        }
        while (b != 0) {
            c = a % b;
            a = b;
            b = c;
        }
        return a;
    }
    
    static float sigmoid( float value, float gain ){
        return 1.0 / ( 1.0 + pow( M_E, - gain * value ) );
    }
    
}};