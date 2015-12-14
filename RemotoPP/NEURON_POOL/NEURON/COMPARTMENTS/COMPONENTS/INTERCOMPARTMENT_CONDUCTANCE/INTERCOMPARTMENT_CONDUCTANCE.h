//Code description: This code implements the intercompartment conductance class
//A intercompartment conductance is the connection between two compartments

//CHANGE LOG:

//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!!  
//Good Work!

//Check if inclued before:
#ifndef INTERCOMPARTMENT_CONDUCTANCE_H
#define INTERCOMPARTMENT_CONDUCTANCE_H

//Includes:
#include "DEFAULT_DATA_TYPE.h"
#include <string>

//Structs ans class
typedef struct INTERCOMPARTMENT_CONDUCTANCE_CONSTRUCTOR_STRUCT
{
	//Name
	std::string name;
	//Pointer to the this compartment voltage mV
	num_type* pointer_2_compartment_voltage_mV;
	//Pointer to the connected compartment voltage mV
	num_type* pointer_2_connected_compartment_voltage_mV;
	//Connected compartment Cytoplasm conductance uS
	num_type connected_compartment_cytoplasm_conductance_uS;
	//This compartment Cytoplasm conductance uS
	num_type this_compartment_cytoplasm_conductance_uS;
}INTERCOMPARTMENT_CONDUCTANCE_CONSTRUCTOR;


class INTERCOMPARTMENT_CONDUCTANCE
{
	public:
		INTERCOMPARTMENT_CONDUCTANCE(INTERCOMPARTMENT_CONDUCTANCE_CONSTRUCTOR constructor);
		//Evaluate the intercompartment current nA
		//Positive currents contributes to increase compartment voltage
		num_type eval_intercompartment_current_nA();
		//Get name
		std::string get_name(void);
	private:
		//Pointer to the this compartment voltage mV
		num_type* pointer_2_compartment_voltage_mV;
		//Pointer to the connected compartment voltage mV
		num_type* pointer_2_connected_compartment_voltage_mV;
		//Intercompartment conductance uS
		num_type intercompartment_conductance_uS;
		//Name
		std::string name;
};


#endif  //INTERCOMPARTMENT_CONDUCTANCE