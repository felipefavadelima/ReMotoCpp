//Code description: This header lists all monitors components and
//standardize all monitors througth  method:
//void atualize_monitor(COMPARTMENT_STATUS status);
//New monitors headers must be listed here. 
//If you want to implement a new kind of monitor, remember that as any monitor,
//your new monitor class must implement:
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
#ifndef MONITORS_H
#define MONITORS_H

//Includes:
#include "DEFAULT_DATA_TYPE.h"
#include <vector>
#include <string>

class MONITORS
{
	public:
		virtual void atualize_monitor() = 0;
		virtual std::vector<std::vector<num_type>>* get_p_monitor_data() = 0;
		virtual std::string get_name(void) = 0;
		virtual std::string get_type(void) = 0;
		virtual std::vector<std::string> get_dimensions(void) = 0;
	private:
};

//List of monitors:
#include "ACTION_POTENCIAL_MONITOR.h"
#include "VOLTAGE_MONITOR.h"
#endif  //MONITORS