//Code description: This code implements a action potencial (AP) monitor component. 
//An action potencial (AP) monitor is used to monitor ocurrences of APs in compartments
//Everytime the on treshold voltage (mV) of the monitor is reached, the ocurrence time 
//is saved in memory, after the compartment voltage goes below the off treshold voltage,
//a new AP can be catched. At the end of the neuron this data can be used
//As monitor , it implements:
//num_type atualize_monitor(num_type current_nA, num_type membrane_voltage_mV, num_type time_ms);


//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!! 
//Good Work!

//Check if inclued before:
#ifndef ACTION_POTENCIAL_MONITOR_H
#define ACTION_POTENCIAL_MONITOR_H

//Includes
#include "DEFAULT_DATA_TYPE.h"
#include "MONITORS.h"
#include <vector>
#include <string>

//Definitions
#ifndef AP_MONITOR_STATE_ON
#define AP_MONITOR_STATE_ON   true
#endif AP_MONITOR_STATE_ON
#ifndef AP_MONITOR_STATE_OFF
#define AP_MONITOR_STATE_OFF   false
#endif // AP_MONITOR_STATE_OFF




//Structs and Classes
typedef struct ACTION_POTENCIAL_MONITOR_CONSTRUCTOR_STRUCT
{
	//Monitor name
	std::string name;
	//treshold Voltage in mV that determines the ocurrence of a AP
	num_type on_treshold_voltage_mV;
	//treshold Voltage in mV to catch a new AP 
	//(a new AP will be catched, just after the membrane voltage goes below this value)
	num_type off_treshold_voltage_mV;
	//Pointer to the current neuron time ms
	num_type* pointer_2_neuron_time_ms;
	//This compartment membrane voltage pointer mV
	num_type* pointer_2_compartment_membrane_voltage_mV;
}ACTION_POTENCIAL_MONITOR_CONSTRUCTOR;

typedef struct NEW_ACTION_POTENCIAL_MONITOR_STRUCT
{
	//Monitor name
	std::string name;
	//treshold Voltage in mV that determines the ocurrence of a AP
	num_type on_treshold_voltage_mV;
	//treshold Voltage in mV to catch a new AP 
	//(a new AP will be catched, just after the membrane voltage goes below this value)
	num_type off_treshold_voltage_mV;
}NEW_ACTION_POTENCIAL_MONITOR;

class ACTION_POTENCIAL_MONITOR : public MONITORS
{
public:

	//Public Methods
	ACTION_POTENCIAL_MONITOR(ACTION_POTENCIAL_MONITOR_CONSTRUCTOR constructor);
	//Method responsible to atualize the monitor 
	void atualize_monitor();
	//Get data from monitor
	std::vector<std::vector<num_type>>* get_p_monitor_data();
	//Get name
	std::string get_name(void);
	//Get type
	std::string get_type(void);
	//Get Dimensions
	std::vector<std::string> get_dimensions(void);
private:
	//Private Vars
	//Data
	std::vector<std::vector<num_type>> Data;
	//treshold Voltage in mV that determines the ocurrence of a AP
	num_type on_voltage_treshold_mV;
	//treshold Voltage in mV to catch a new AP 
	//(a new AP will be catched, just after the membrane voltage goes below this value)
	num_type off_voltage_treshold_mV;
	//State of the monitor, ON represents that an ON treshold have been reached.
	//OFF represents that a new AP can be catched
	//Pointer to the current neuron time ms
	num_type* pointer_2_neuron_time_ms;
	//This compartment membrane voltage pointer mV
	num_type* pointer_2_compartment_membrane_voltage_mV;
	//Monitor state
	bool state;
	//Name
	std::string name;
	//Type = ACTION_POTENCIAL_MONITOR
	std::string type;
};

#endif //ACTION_POTENCIAL_MONITOR
