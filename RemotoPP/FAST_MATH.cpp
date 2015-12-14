//Fast exponencial code
#include "FAST_MATH.h"


num_type FAST::exp(num_type x)
{
		if (x < -19.0) return 0;
		else return std::exp(x);
}
