//Code description: This header lists all ionic channels components and
//standardize all ionic channels througth  method:
//num_type evaluate_current_nA(num_type membrane_voltage_mV, num_type time_ms)
//New ionic channels headers must be listed here. 
//If you want to implement a new kind of ionic channel, remember that as any ionic channel,
//your new ionic_channel class must implement:
//num_type eval_ionic_current_nA(num_type membrane_voltage_mV, num_type time_ms)

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!!  
//Good Work!

//Check if inclued before:
#ifndef IONIC_CHANNELS_H
#define IONIC_CHANNELS_H

//Includes:
#include "DEFAULT_DATA_TYPE.h"
#include <string>

class IONIC_CHANNELS
{
	public:
		//Elvaluate the current of the ionic channel in nA when membrane_voltage_mV and time_ms
		//Positive currents contributes to increase compartment voltage
		virtual num_type eval_ionic_current_nA() = 0;
		//Get name
		virtual std::string get_name(void) = 0;
};


//List of ionic channels :
#include "DESTEXHE_KF_CHANNEL.h"
#include "DESTEXHE_KS_CHANNEL.h"
#include "DESTEXHE_NA_CHANNEL.h"

#endif  //IONIC_CHANNELS