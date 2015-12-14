#include "DEFAULT_DATA_TYPE.h"

namespace RANGE
{
	//Return a linear range value 
	//Output exampe : min = 10 , max = 100 , percent = 0.5 , return 55
	num_type linear(num_type min, num_type max , num_type percent)
	{
		return min + ((max - min) * percent);
	}
}
