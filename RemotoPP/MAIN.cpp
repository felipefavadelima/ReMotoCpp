// RemotoPP.cpp : Defines the entry point for the console application.
//Code description: This is the main code.... Here is the start point !!!
//Welcome

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!!  
//Good Work!


//includes
#include "stdafx.h"
#include "NEURON_POOL.h"
#include <iostream>
#include <chrono>
#include "RANGE.h"
#include <vector>
#include "SIMULATOR.h"


int main()
{

	//Create simulator
	SIMULATOR_CONSTRUCTOR constructor;
	constructor.name = "REMOTO";
	constructor.simulation_step_time_ms = 0.05;
	constructor.total_simulation_time_ms = 10000;
	SIMULATOR simulator(constructor);

	//Create SO Neuron pool
	NEW_NEURON_POOL SO_parameters;
	SO_parameters.name = "SO";
	NEURON_POOL* SO_POOL = simulator.add_new_neuron_pool(SO_parameters);


	//Create SO_S_TYPE neurons
	#define  SO_S_TYPE_n_neurons  800

	NEW_NEURON SO_S_type_parameters;
	SO_S_type_parameters.name = "SO_S_type";

	num_type percent;
	for (unsigned long int neuron_index = 0; neuron_index < SO_S_TYPE_n_neurons; neuron_index++)
	{
		percent = neuron_index / (SO_S_TYPE_n_neurons - 1);
		//Add neuron to pool
		NEURON* SO_S_TYPE = SO_POOL->add_new_neuron(SO_S_type_parameters);
		//Create SO_S_type SOMA
		NEW_COMPARTMENT SO_S_type_SOMA_parameters;
		SO_S_type_SOMA_parameters.name = "SO_S_SOMA";
		SO_S_type_SOMA_parameters.diameter_um = RANGE::linear(77.5, 82.5, percent);
		SO_S_type_SOMA_parameters.length_um = RANGE::linear(77.5, 82.5, percent);
		SO_S_type_SOMA_parameters.specific_cytoplasm_resistance_Ohm_cm = 70.0;
		SO_S_type_SOMA_parameters.specific_membrane_capacitance_uF_cm2 = 1.0;
		SO_S_type_SOMA_parameters.specific_trasmembrane_resistance_Ohm_cm2 = RANGE::linear(1150.0, 1050.0, percent);
		COMPARTMENT* SO_S_type_SOMA = SO_S_TYPE->add_new_compartment(SO_S_type_SOMA_parameters);
		//Add Na ionic channel to SOMA 
		NEW_DESTEXHE_NA_CHANNEL SO_S_type_SOMA_Na_channel_parameters;
		SO_S_type_SOMA_Na_channel_parameters.gNa_bar_mS_cm2 = 30.0;
		SO_S_type_SOMA_Na_channel_parameters.alpha_m_ms = 22.0;
		SO_S_type_SOMA_Na_channel_parameters.beta_m_ms = 13.0;
		SO_S_type_SOMA_Na_channel_parameters.alpha_h_ms = 0.5;
		SO_S_type_SOMA_Na_channel_parameters.beta_h_ms = 4.0;
		SO_S_type_SOMA_Na_channel_parameters.Na_ion_nernst_potencial_mV = 120.0;
		SO_S_type_SOMA_Na_channel_parameters.treshold_voltage_mV = RANGE::linear(12.35, 16.45, percent);
		SO_S_type_SOMA_Na_channel_parameters.h_time_to_peak_ms = 0.6;
		SO_S_type_SOMA_Na_channel_parameters.m_time_to_peak_ms = 0.6;
		SO_S_type_SOMA_Na_channel_parameters.refractory_period_ms = 5.0;
		SO_S_type_SOMA->add_new_ionic_channel(SO_S_type_SOMA_Na_channel_parameters);
		//Add Kf ionic channel
		NEW_DESTEXHE_KF_CHANNEL SO_S_type_SOMA_Kf_channel_parameters;
		SO_S_type_SOMA_Kf_channel_parameters.gKf_bar_mS_cm2 = 4.0;
		SO_S_type_SOMA_Kf_channel_parameters.alpha_n_ms = 1.5;
		SO_S_type_SOMA_Kf_channel_parameters.beta_n_ms = 0.1;
		SO_S_type_SOMA_Kf_channel_parameters.k_ion_nernst_potencial_mV = -10.0;
		SO_S_type_SOMA_Kf_channel_parameters.treshold_voltage_mV = RANGE::linear(12.35, 16.45, percent);
		SO_S_type_SOMA_Kf_channel_parameters.n_time_to_peak_ms = 0.6;
		SO_S_type_SOMA_Kf_channel_parameters.refractory_period_ms = 5.0;
		SO_S_type_SOMA->add_new_ionic_channel(SO_S_type_SOMA_Kf_channel_parameters);
		//Add Ks ionic channel
		NEW_DESTEXHE_KS_CHANNEL SO_S_type_SOMA_Ks_channel_parameters;
		SO_S_type_SOMA_Ks_channel_parameters.gKs_bar_mS_cm2 = 17.0;
		SO_S_type_SOMA_Ks_channel_parameters.alpha_q_ms = 1.5;
		SO_S_type_SOMA_Ks_channel_parameters.beta_q_ms = 0.025;
		SO_S_type_SOMA_Ks_channel_parameters.k_ion_nernst_potencial_mV = -10.0;
		SO_S_type_SOMA_Ks_channel_parameters.treshold_voltage_mV = RANGE::linear(12.35, 16.45, percent);
		SO_S_type_SOMA_Ks_channel_parameters.q_time_to_peak_ms = 0.6;
		SO_S_type_SOMA_Ks_channel_parameters.refractory_period_ms = 5.0;
		SO_S_type_SOMA->add_new_ionic_channel(SO_S_type_SOMA_Ks_channel_parameters);
		
		//Add DC current source to SOMA
		NEW_DC_CURRENT_SOURCE SO_S_type_SOMA_dc_current_source_parameters;
		SO_S_type_SOMA_dc_current_source_parameters.current_nA = 10.0;
		SO_S_type_SOMA->add_new_current_source(SO_S_type_SOMA_dc_current_source_parameters);

		//Add monitor to SOMA
		NEW_ACTION_POTENCIAL_MONITOR SO_S_type_AP_monitor_parameters;
		SO_S_type_AP_monitor_parameters.on_treshold_voltage_mV = RANGE::linear(12.35, 16.45, percent);
		SO_S_type_AP_monitor_parameters.off_treshold_voltage_mV = 10.0;
		SO_S_type_AP_monitor_parameters.name = "SO_S_SOMA";
		simulator.add_new_monitor(SO_S_type_SOMA->add_new_monitor(SO_S_type_AP_monitor_parameters));

		//Add Dendrite
		NEW_COMPARTMENT SO_S_type_DENDRITE_parameters;
		SO_S_type_DENDRITE_parameters.name = "SO_S_DENDRITE";
		SO_S_type_DENDRITE_parameters.diameter_um = RANGE::linear(41.5, 62.5, percent);
		SO_S_type_DENDRITE_parameters.length_um = RANGE::linear(5519.0, 6789.0, percent);
		SO_S_type_DENDRITE_parameters.specific_cytoplasm_resistance_Ohm_cm = 70.0;
		SO_S_type_DENDRITE_parameters.specific_membrane_capacitance_uF_cm2 = 1.0;
		SO_S_type_DENDRITE_parameters.specific_trasmembrane_resistance_Ohm_cm2 = RANGE::linear(14350.0, 10650.0, percent);
		COMPARTMENT* SO_S_type_DENDRITE = SO_S_TYPE->add_new_compartment(SO_S_type_DENDRITE_parameters);

		//Connect Soma and Dendrite
		SO_S_TYPE->add_new_intercompartment_conductance(SO_S_type_SOMA, SO_S_type_DENDRITE);
	}
	//Simulate
	std::cout << "Simulation started..... Please Wait !!!" << std::endl;
	auto t0 = std::chrono::high_resolution_clock::now();
	simulator.simulate();
	auto t1 = std::chrono::high_resolution_clock::now();
	auto dt = 1.e-9*std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
	std::cout << "Simulation time in seconds:" << dt << std::endl;
	simulator.send_monitors_2_matlab();
	std::cin.get();
    return 0;
	
}

