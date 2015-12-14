//Code description: This header lists all synapses components and
//standardize all synapses througth  method:
//num_type eval_synapse_current_nA(num_type membrane_voltage_mV, num_type time_ms)
//New synapses headers must be listed here. 
//If you want to implement a new kind of synapse, remember that as any synapse,
//your new synapse class must implement:
//num_type eval_synapse_current_nA(num_type membrane_voltage_mV, num_type time_ms)

//CHANGE LOG:

//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!!  
//Good Work!

//Check if inclued before:
#ifndef SYNAPSES_H
#define SYNAPSES_H

//Includes:
#include "DEFAULT_DATA_TYPE.h"
#include <string>

//Structs ans class

class SYNAPSES
{
	public:
		//Evaluate synapse current nA
		virtual num_type eval_synapse_current_nA() = 0;
		//Get synapse name
		virtual std::string get_name(void) = 0;
	private:
};

//List of Synapses

#endif  //SYNAPSES