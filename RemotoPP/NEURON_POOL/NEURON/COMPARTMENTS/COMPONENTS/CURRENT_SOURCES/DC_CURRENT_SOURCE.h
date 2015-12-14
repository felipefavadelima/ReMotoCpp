//Code description: This code implements a DC current source components. 
//A DC current source is a component that injects the same amount of current inside the compartment
//durring all simulation time.
//As any current source , it implements:
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
#ifndef DC_CURRENT_SOURCE_H
#define DC_CURRENT_SOURCE_H

//Includes
#include "DEFAULT_DATA_TYPE.h"
#include "CURRENT_SOURCES.h"
#include <string>


//Structs and classes
typedef struct DC_CURRENT_SOURCE_CONSTRUCTOR_STRUCT
{
	//Current intesity nA
	num_type current_nA;
}DC_CURRENT_SOURCE_CONSTRUCTOR;

typedef struct NEW_DC_CURRENT_SOURCE_STRUCT
{
	//Current intesity nA
	num_type current_nA;
	//Name
	std::string name;
}NEW_DC_CURRENT_SOURCE;

class DC_CURRENT_SOURCE : public CURRENT_SOURCES
{
public:
	//Public Methods
	DC_CURRENT_SOURCE(DC_CURRENT_SOURCE_CONSTRUCTOR constructor);
	//Method responsible for calculate the current of the current source (nA) at time (ms)
	//Positive currents contributes to increase compartment voltage
	num_type eval_source_current_nA();
	//Get name
	std::string get_name(void);
protected:
private:
	//Current of current source in (nA)
	num_type current_nA;
	//Name
	std::string name;
};

#endif // DC_CURRENT_SOURCE
