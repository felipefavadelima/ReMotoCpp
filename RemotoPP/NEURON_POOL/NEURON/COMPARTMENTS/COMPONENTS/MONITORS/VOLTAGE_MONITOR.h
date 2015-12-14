//Code description: This code implements a compartment voltage monitor. 
//A compartment voltage monitor is used to monitor all voltage behavior of a compartment
// At the end of the neuron this data used
//As any component , it implements:
//void atualize_monitor(COMPARTMENT_STATUS status);
//As monitor , it implements:
//void atualize_monitor(COMPARTMENT_STATUS status);

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!! 
//Good Work!


//Check if inclued before:
#ifndef VOLTAGE_MONITOR_H
#define VOLTAGE_MONITOR_H

//Includes
#include <vector>
#include "MONITORS.h"
#include "DEFAULT_DATA_TYPE.h"
#include<string>

//DEFINITIONS


//Structs and Classes
typedef struct VOLTAGE_MONITOR_CONSTRUCTOR_STRUCT
{
	//Name
	std::string name;
	//Pointer to the current neuron time ms
	num_type* pointer_2_neuron_time_ms;
	//This compartment membrane voltage pointer mV
	num_type* pointer_2_compartment_membrane_voltage_mV;
}VOLTAGE_MONITOR_CONSTRUCTOR;

typedef struct NEW_VOLTAGE_MONITOR_STRUCT
{
	//Name
	std::string name;
}NEW_VOLTAGE_MONITOR;


class VOLTAGE_MONITOR :public MONITORS
{
	public:
		VOLTAGE_MONITOR(VOLTAGE_MONITOR_CONSTRUCTOR constructor);
		//Atualize monitor
		void atualize_monitor();
		//Get monitor data
		std::vector<std::vector<num_type>>* get_p_monitor_data();
		//Get name
		std::string get_name(void);
		//Get type
		std::string get_type(void);
		//Get Dimensions
		std::vector<std::string> get_dimensions(void);
	private:	
		//Data
		std::vector<std::vector<num_type>> Data;
		//Pointer to the current neuron time ms
		num_type* pointer_2_neuron_time_ms;
		//This compartment membrane voltage pointer mV
		num_type* pointer_2_compartment_membrane_voltage_mV;
		//Name
		std::string name;
		//Type = VOLTAGE_MONITOR
		std::string type;
};
#endif //VOLTAGE_MONITOR
