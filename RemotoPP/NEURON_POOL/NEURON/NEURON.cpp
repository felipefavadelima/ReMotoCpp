#include "NEURON.h"

//Constructor 
NEURON::NEURON(NEURON_CONSTRUCTOR constructor)
{
	this->name = constructor.name;
	this->simulation_step_size_ms = constructor.simulation_step_size_ms;
	this->simulation_time_ms = 0;
}

//Method responsible to atualize the neuron, step time defined by step_size_ms of each neuron
void NEURON::atualize(void)
{
		unsigned int number_of_compartments = (unsigned int)this->compartments.size();
		//Save all current compartment voltages
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments[i]->runge_kutta_vars.copy_of_compartment_voltage_mV = this->compartments[i]->membrane_voltage_mV;
		//Use Runge Kutta to update compartments voltages
		//Calculate K1
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments[i]->runge_kutta_vars.k1 = this->compartments[i]->eval_dV_dt_membrane_voltage_mV_ms();
		//Update compartments voltages
		num_type step_size_by_2 = this->simulation_step_size_ms / 2;
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments.at(i)->membrane_voltage_mV = this->compartments[i]->runge_kutta_vars.copy_of_compartment_voltage_mV + (step_size_by_2*this->compartments[i]->runge_kutta_vars.k1);
		//Increment time to time_step/2
		this->simulation_time_ms += step_size_by_2;
		//Calculate K2
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments[i]->runge_kutta_vars.k2 = this->compartments.at(i)->eval_dV_dt_membrane_voltage_mV_ms();
		//Update compartments voltages
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments.at(i)->membrane_voltage_mV = this->compartments[i]->runge_kutta_vars.copy_of_compartment_voltage_mV + (step_size_by_2*this->compartments[i]->runge_kutta_vars.k2);
		//Calculate K3
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments[i]->runge_kutta_vars.k3 = this->compartments.at(i)->eval_dV_dt_membrane_voltage_mV_ms();
		//Update compartments voltages
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments.at(i)->membrane_voltage_mV = this->compartments[i]->runge_kutta_vars.copy_of_compartment_voltage_mV + ((this->simulation_step_size_ms)*this->compartments[i]->runge_kutta_vars.k3);
		//Increment time to time_step/2
		this->simulation_time_ms += step_size_by_2;
		//Calculate K4
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments[i]->runge_kutta_vars.k4 = this->compartments.at(i)->eval_dV_dt_membrane_voltage_mV_ms();
		//Calculate final voltages
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments.at(i)->membrane_voltage_mV = this->compartments[i]->runge_kutta_vars.copy_of_compartment_voltage_mV +
			((this->compartments[i]->runge_kutta_vars.k1 + 
				2 * this->compartments[i]->runge_kutta_vars.k2 + 
				2 * this->compartments[i]->runge_kutta_vars.k3 + 
				this->compartments[i]->runge_kutta_vars.k4)* (this->simulation_step_size_ms / 6));
		//Atualize compartments monitors
		for (unsigned int i = 0; i < number_of_compartments; i++)
			this->compartments.at(i)->atualize_monitors();
}

//Add new a new intercompartment conductance
void NEURON::add_new_intercompartment_conductance(COMPARTMENT* compartment1, COMPARTMENT* compartment2)
{
	INTERCOMPARTMENT_CONDUCTANCE_CONSTRUCTOR constructor;
	constructor.name = "INTERCOMPARTMENT_CONDUCTANCE_" + compartment1->get_name() + "_" + compartment2->get_name();
	constructor.pointer_2_compartment_voltage_mV = &compartment1->membrane_voltage_mV;
	constructor.pointer_2_connected_compartment_voltage_mV = &compartment2->membrane_voltage_mV;
	constructor.connected_compartment_cytoplasm_conductance_uS = compartment2->get_parameters().cytoplasm_conductance_uS;
	constructor.this_compartment_cytoplasm_conductance_uS = compartment1->get_parameters().cytoplasm_conductance_uS;
	compartment1->add_new_intercompartment_conductance(constructor);
	constructor.name = "INTERCOMPARTMENT_CONDUCTANCE_" + compartment2->get_name() + "_" + compartment1->get_name();
	constructor.pointer_2_compartment_voltage_mV = &compartment2->membrane_voltage_mV;
	constructor.pointer_2_connected_compartment_voltage_mV = &compartment1->membrane_voltage_mV;
	constructor.connected_compartment_cytoplasm_conductance_uS = compartment1->get_parameters().cytoplasm_conductance_uS;
	constructor.this_compartment_cytoplasm_conductance_uS = compartment2->get_parameters().cytoplasm_conductance_uS;
	compartment2->add_new_intercompartment_conductance(constructor);
}
//Add a new compartment
COMPARTMENT* NEURON::add_new_compartment(NEW_COMPARTMENT parameters)
{
	COMPARTMENT_CONSTRUCTOR constructor;
	constructor.diameter_um = parameters.diameter_um;
	constructor.length_um = parameters.length_um;
	constructor.name = parameters.name;
	constructor.p_simulation_step_size_ms = &this->simulation_step_size_ms;
	constructor.p_simulation_time_ms = &this->simulation_time_ms;
	constructor.specific_cytoplasm_resistance_Ohm_cm = parameters.specific_cytoplasm_resistance_Ohm_cm;
	constructor.specific_membrane_capacitance_uF_cm2 = parameters.specific_membrane_capacitance_uF_cm2;
	constructor.specific_trasmembrane_resistance_Ohm_cm2 = parameters.specific_trasmembrane_resistance_Ohm_cm2;
	COMPARTMENT* compartment = new COMPARTMENT(constructor);
	this->compartments.push_back(compartment);
	return compartment;
}


//Get compartment name
std::string NEURON::get_name()
{
	return this->name;
}