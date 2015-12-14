#include "COMPARTMENT.h"

//Constructor
COMPARTMENT::COMPARTMENT(COMPARTMENT_CONSTRUCTOR constructor)
{
	this->name = constructor.name;
	this->parameters.length_um = constructor.length_um;
	this->parameters.diameter_um = constructor.diameter_um;
	this->parameters.area_um2 = constructor.length_um * constructor.diameter_um * PI;
	this->parameters.capacitance_uF = constructor.specific_membrane_capacitance_uF_cm2 * (this->parameters.area_um2 * 1e-8);
	this->parameters.cytoplasm_conductance_uS = 1e6/((constructor.length_um  / (PI*pow(constructor.diameter_um/2,2))) * 1e4 * constructor.specific_cytoplasm_resistance_Ohm_cm);
	this->parameters.leak_conductance_uS = 1e6/( constructor.specific_trasmembrane_resistance_Ohm_cm2 / (this->parameters.area_um2 * 1e-8));
	this->membrane_voltage_mV = 0;
	this->p_simulation_step_size_ms = constructor.p_simulation_step_size_ms;
	this->p_simulation_time_ms = constructor.p_simulation_time_ms;
	this->runge_kutta_vars.copy_of_compartment_voltage_mV = 0;
	this->runge_kutta_vars.k1 = 0;
	this->runge_kutta_vars.k2 = 0;
	this->runge_kutta_vars.k3 = 0;
	this->runge_kutta_vars.k4 = 0;
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

//Add Components 
//Ionic Channels
void COMPARTMENT::add_new_ionic_channel(NEW_DESTEXHE_KF_CHANNEL parameters)
{
	DESTEXHE_KF_CHANNEL_CONSTRUCTOR constructor;
	constructor.alpha_n_ms = parameters.alpha_n_ms;
	constructor.beta_n_ms = parameters.beta_n_ms;
	constructor.gKf_bar_mS_cm2 = parameters.gKf_bar_mS_cm2;
	constructor.k_ion_nernst_potencial_mV = parameters.k_ion_nernst_potencial_mV;
	constructor.n_time_to_peak_ms = parameters.n_time_to_peak_ms;
	constructor.refractory_period_ms = parameters.refractory_period_ms;
	constructor.region_area_um2 = this->parameters.area_um2;
	constructor.treshold_voltage_mV = parameters.treshold_voltage_mV;
	constructor.pointer_2_compartment_membrane_voltage_mV = &this->membrane_voltage_mV;
	constructor.pointer_2_neuron_time_ms = this->p_simulation_time_ms;
	this->ionic_channels.push_back((IONIC_CHANNELS*)new DESTEXHE_KF_CHANNEL(constructor));
}
void COMPARTMENT::add_new_ionic_channel(NEW_DESTEXHE_KS_CHANNEL parameters)
{
	DESTEXHE_KS_CHANNEL_CONSTRUCTOR constructor;
	constructor.alpha_q_ms = parameters.alpha_q_ms;
	constructor.beta_q_ms = parameters.beta_q_ms;
	constructor.gKs_bar_mS_cm2 = parameters.gKs_bar_mS_cm2;
	constructor.k_ion_nernst_potencial_mV = parameters.k_ion_nernst_potencial_mV;
	constructor.q_time_to_peak_ms = parameters.q_time_to_peak_ms;
	constructor.refractory_period_ms = parameters.refractory_period_ms;
	constructor.region_area_um2 = this->parameters.area_um2;
	constructor.treshold_voltage_mV = parameters.treshold_voltage_mV;
	constructor.pointer_2_compartment_membrane_voltage_mV = &this->membrane_voltage_mV;
	constructor.pointer_2_neuron_time_ms = this->p_simulation_time_ms;
	this->ionic_channels.push_back((IONIC_CHANNELS*)new DESTEXHE_KS_CHANNEL(constructor));
}
void COMPARTMENT::add_new_ionic_channel(NEW_DESTEXHE_NA_CHANNEL parameters)
{
	DESTEXHE_NA_CHANNEL_CONSTRUCTOR constructor;
	constructor.alpha_m_ms = parameters.alpha_m_ms;
	constructor.alpha_h_ms = parameters.alpha_h_ms;
	constructor.beta_m_ms = parameters.beta_m_ms;
	constructor.beta_h_ms = parameters.beta_h_ms;
	constructor.gNa_bar_mS_cm2 = parameters.gNa_bar_mS_cm2;
	constructor.Na_ion_nernst_potencial_mV = parameters.Na_ion_nernst_potencial_mV;
	constructor.m_time_to_peak_ms = parameters.m_time_to_peak_ms;
	constructor.h_time_to_peak_ms = parameters.h_time_to_peak_ms;
	constructor.refractory_period_ms = parameters.refractory_period_ms;
	constructor.region_area_um2 = this->parameters.area_um2;
	constructor.treshold_voltage_mV = parameters.treshold_voltage_mV;
	constructor.pointer_2_compartment_membrane_voltage_mV = &this->membrane_voltage_mV;
	constructor.pointer_2_neuron_time_ms = this->p_simulation_time_ms;
	this->ionic_channels.push_back((IONIC_CHANNELS*)new DESTEXHE_NA_CHANNEL(constructor));
}

//Current  Sources
void COMPARTMENT::add_new_current_source(NEW_DC_CURRENT_SOURCE parameters)
{
	DC_CURRENT_SOURCE_CONSTRUCTOR constructor;
	constructor.current_nA = parameters.current_nA;
	this->currrent_sources.push_back((CURRENT_SOURCES*) new DC_CURRENT_SOURCE(constructor));
}

//Monitors
MONITORS* COMPARTMENT::add_new_monitor(NEW_ACTION_POTENCIAL_MONITOR parameters)
{
	ACTION_POTENCIAL_MONITOR_CONSTRUCTOR constructor;
	constructor.name = parameters.name;
	constructor.off_treshold_voltage_mV = parameters.off_treshold_voltage_mV;
	constructor.on_treshold_voltage_mV = parameters.on_treshold_voltage_mV;
	constructor.pointer_2_compartment_membrane_voltage_mV = &this->membrane_voltage_mV;
	constructor.pointer_2_neuron_time_ms = this->p_simulation_time_ms;
	MONITORS* monitor = (MONITORS*) new ACTION_POTENCIAL_MONITOR(constructor);
	this->monitors.push_back(monitor);
	return monitor;
}

MONITORS* COMPARTMENT::add_new_monitor(NEW_VOLTAGE_MONITOR parameters)
{
	VOLTAGE_MONITOR_CONSTRUCTOR constructor;
	constructor.name = parameters.name;
	constructor.pointer_2_compartment_membrane_voltage_mV = &this->membrane_voltage_mV;
	constructor.pointer_2_neuron_time_ms = this->p_simulation_time_ms;
	MONITORS* monitor = (MONITORS*) new VOLTAGE_MONITOR(constructor);
	this->monitors.push_back(monitor);
	return monitor;
}

void COMPARTMENT::add_new_intercompartment_conductance(INTERCOMPARTMENT_CONDUCTANCE_CONSTRUCTOR constructor)
{
	this->intercompartment_conductances.push_back(new INTERCOMPARTMENT_CONDUCTANCE(constructor));
}

//Get compartment parameters
COMPARTMENT_PARAMETERS COMPARTMENT::get_parameters()
{
	return this->parameters;
}

//Get compartment name
std::string COMPARTMENT::get_name()
{
	return this->name;
}
