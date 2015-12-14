//Code description: This header lists all current sources components and
//standardize all current sources througth  method:
//num_type evaluate_current_nA(num_type membrane_voltage_mV, num_type time_ms)
//New current sources headers must be listed here. 
//If you want to implement a new kind of current source, remember that as any current source,
//your new current source class must implement:
//num_type eval_source_current_nA(num_type membrane_voltage_mV, num_type time_ms)

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!!  
//Good Work!

//Check if inclued before:
#ifndef CURRENT_SOURCES_H
#define CURRENT_SOURCES_H

//Includes:
#include "DEFAULT_DATA_TYPE.h"
#include <string>

class CURRENT_SOURCES
{
	public:
		//Elvaluate the current of the current source in nA when membrane_voltage_mV and time_ms
		//Positive currents contributes to increase compartment voltage
		virtual num_type eval_source_current_nA() =0;
		//Get name
		virtual std::string get_name(void) = 0;
};

//List of DC current sources:
#include "DC_CURRENT_SOURCE.h"

#endif  //CURRENT_SOURCES