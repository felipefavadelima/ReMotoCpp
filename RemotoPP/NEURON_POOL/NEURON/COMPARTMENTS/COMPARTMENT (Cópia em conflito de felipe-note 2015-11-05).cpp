#include "COMPARTMENT.h"

//Constructor
COMPARTMENT::COMPARTMENT(COMPARTMENT_CONSTRUCTOR parameters)
{
	this->parameters.length_um = parameters.length_um;
	this->parameters.diameter_um = parameters.diameter_um;
	this->parameters.area_um2 = parameters.length_um * parameters.diameter_um;
	this->parameters.capacitance_uF = parameters.specific_membrane_capacitance_uF_cm2 * (this->parameters.area_um2 * 1e-8);
	this->parameters.cytoplasm_conductance_uS = 1e6/( ((parameters.length_um  / this->parameters.area_um2) * (1/1e-4)) * parameters.specific_cytoplasm_resistance_Ohm_cm);
	this->parameters.leak_conductance_uS = 1e6/( parameters.specific_trasmembrane_resistance_Ohm_cm2 / (this->parameters.area_um2 * 1e-8));
	this->membrane_voltage_mV = 0;
}
//method responsible for insert a new current source component
void COMPARTMENT::add_new_current_source(CURRENT_SOURCES* current_source)
{
	this->currrent_sources.push_back(current_source);
}
//method responsible for insert a new ionic channel component
void COMPARTMENT::add_new_ionic_channel(IONIC_CHANNELS* ionic_channel)
{
	this->ionic_channels.push_back(ionic_channel);
}
//method responsible for insert a new monitor component
void COMPARTMENT::add_new_monitor(MONITORS* monitor)
{
	this->monitors.push_back(monitor);
}
//method responsible for insert a new synapse component
void COMPARTMENT::add_new_synapse(SYNAPSES* synapse)
{
	this->synapses.push_back(synapse);
}
//method responsible for insert a new intercompartment conductance
void COMPARTMENT::add_new_intercompartment_conductance(INTERCOMPARTMENT_CONDUCTANCE* intercompartment_conductance)
{
	this->intercompartment_conductances.push_back(intercompartment_conductance);
}
//method responsible for insert a new miscellaneous component
void COMPARTMENT::add_new_miscellaneous(MISCELLANEOUS* miscellaneous)
{
	this->miscellaneous.push_back(miscellaneous);
}
//method responsible to get the compartment parameters
COMPARTMENT_PARAMETERS COMPARTMENT::get_compartment_parameters()
{
	return this->parameters;
}
//method responsible for evaluate dV/dt (mV / ms) of the membrane voltage (Sum of all currents (Leak + Synapse
//+ Intercompartment + Miscellaneous + current_sources + ionic channels) / Membrane capacitor)
num_type COMPARTMENT::eval_dV_dt_membrane_voltage_mV_ms()
{
	unsigned int i;
	num_type total_compartment_current_nA = 0;
	//Leak current nA
	total_compartment_current_nA += -this->membrane_voltage_mV * this->parameters.leak_conductance_uS;
	//Current Sources
	for (i = 0; i < this->currrent_sources.size(); i++)
		total_compartment_current_nA += this->currrent_sources.at(i)->eval_source_current_nA();
	//Intercompartment currents
	for (i = 0; i < this->intercompartment_conductances.size(); i++)
		total_compartment_current_nA += this->intercompartment_conductances.at(i)->eval_intercompartment_current_nA();
	//Ionic Channels
	for (i = 0; i < this->ionic_channels.size(); i++)
		total_compartment_current_nA += this->ionic_channels.at(i)->eval_ionic_current_nA();
	//Miscellaneous
	for (i = 0; i < this->miscellaneous.size(); i++)
		total_compartment_current_nA += this->miscellaneous.at(i)->eval_miscellaneous_current_nA();
	//Synapses
	for (i = 0; i < this->synapses.size(); i++)
		total_compartment_current_nA += this->synapses.at(i)->eval_synapse_current_nA();
	return 1e-3 * (total_compartment_current_nA / this->parameters.capacitance_uF);
}
//method responsible for atualize monitors if any
void COMPARTMENT::atualize_monitors()
{
	for (unsigned int i = 0; i < this->monitors.size(); i++)
		this->monitors.at(i)->atualize_monitor();
}

