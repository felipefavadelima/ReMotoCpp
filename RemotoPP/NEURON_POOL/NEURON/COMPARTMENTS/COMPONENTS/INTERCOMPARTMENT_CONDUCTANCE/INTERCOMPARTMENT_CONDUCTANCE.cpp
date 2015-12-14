#include "INTERCOMPARTMENT_CONDUCTANCE.h"

INTERCOMPARTMENT_CONDUCTANCE::INTERCOMPARTMENT_CONDUCTANCE(INTERCOMPARTMENT_CONDUCTANCE_CONSTRUCTOR constructor)
{
	this->name = constructor.name;
	this->pointer_2_compartment_voltage_mV = constructor.pointer_2_compartment_voltage_mV;
	this->pointer_2_connected_compartment_voltage_mV = constructor.pointer_2_compartment_voltage_mV;
	num_type this_compartment_resistance_MOhm = 1 / constructor.this_compartment_cytoplasm_conductance_uS;
	num_type connected_compartment_resistance_MOhm = 1 / constructor.connected_compartment_cytoplasm_conductance_uS;	
	num_type intercompartment_resistance_MOhm = (this_compartment_resistance_MOhm + connected_compartment_resistance_MOhm) / 2;
	this->intercompartment_conductance_uS = 1/ intercompartment_resistance_MOhm;
}

num_type INTERCOMPARTMENT_CONDUCTANCE::eval_intercompartment_current_nA()
{
	//Positive currents contributes to increase compartment voltage
	return (*this->pointer_2_connected_compartment_voltage_mV - *this->pointer_2_compartment_voltage_mV) * this->intercompartment_conductance_uS;
}


std::string INTERCOMPARTMENT_CONDUCTANCE::get_name()
{
	return this->name;
}