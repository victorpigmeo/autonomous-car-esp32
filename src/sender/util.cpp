#include "util.h"
#include <cmath>

namespace Util{
    float precision( float f, int places ){
        float n = std::pow(10.0f, places ) ;
        return std::round(f * n) / n ;
    }
}
