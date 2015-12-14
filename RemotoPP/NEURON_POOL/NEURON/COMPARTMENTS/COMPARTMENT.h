//Code description: This code implements the compartment behaviour

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others !!!  
//Good Work!

//check if inclued before
#ifndef COMPARTMENT_H
#define COMPARTMENT_H

//includes
#include "DEFAULT_DATA_TYPE.h"
#include "IONIC_CHANNELS.h"
#include "CURRENT_SOURCES.h"
#include "MONITORS.h"
#include "SYNAPSES.h"
#include "INTERCOMPARTMENT_CONDUCTANCE.h"
#include "MISCELLANEOUS.h"
#include <vector>
#include <string>


#ifndef PI
#define PI 3.141592653589793238463
#endif

//Classes and structs

//Variables to calculate membrane voltage with runge kutta 
typedef struct COMPARTMENT_PARAMETERS_STRUCT
{
	//compartment capacitance  uF
	num_type capacitance_uF;
	//Cytoplasm conductance
	num_type cytoplasm_conductance_uS;
	//length  um
	num_type length_um;
	//diameter_um
	num_type diameter_um;
	//area_um2
	num_type area_um2;
	//Compartment leak conductance  uS
	num_type leak_conductance_uS;
}COMPARTMENT_PARAMETERS;

//Variables to calculate membrane voltage with runge kutta 
typedef struct COMPARTMENT_RUNGE_KUTTA_VARIABLES_STRUCT
{
	num_type copy_of_compartment_voltage_mV;
	num_type k1;
	num_type k2;
	num_type k3;
	num_type k4;
}COMPARTMENT_RUNGE_KUTTA_VARIABLES;

typedef struct COMPARTMENT_CONSTRUCTOR_STRUCT
{
	//compartment name
	std::string name;
	//Compartment length um (micro meter)
	num_type length_um;
	//Compartment diameter um (micro meter)
	num_type diameter_um;
	//comparment specific transmenbrane resistance  Ohm cm2
	num_type specific_trasmembrane_resistance_Ohm_cm2;
	//compartment specific membrane capacitance  uF/cm2
	num_type specific_membrane_capacitance_uF_cm2;
	//cytoplasm specific resistence  Ohm cm
	num_type specific_cytoplasm_resistance_Ohm_cm;
	//Neuron simulation_time pointer
	num_type* p_simulation_time_ms;
	//Simulation step_size pointer
	num_type* p_simulation_step_size_ms;
}COMPARTMENT_CONSTRUCTOR;

typedef struct NEW_COMPARTMENT_STRUCT
{
	//compartment name
	std::string name;
	//Compartment length um (micro meter)
	num_type length_um;
	//Compartment diameter um (micro meter)
	num_type diameter_um;
	//comparment specific transmenbrane resistance  Ohm cm2
	num_type specific_trasmembrane_resistance_Ohm_cm2;
	//compartment specific membrane capacitance  uF/cm2
	num_type specific_membrane_capacitance_uF_cm2;
	//cytoplasm specific resistence  Ohm cm
	num_type specific_cytoplasm_resistance_Ohm_cm;
}NEW_COMPARTMENT;


class COMPARTMENT
{
	public:
		//Vars:
		//Runge Kutta parameters, used by neuron
		COMPARTMENT_RUNGE_KUTTA_VARIABLES runge_kutta_vars;
		//membrane voltage mV, used by neuron
		num_type membrane_voltage_mV;
		//METHODS:
		//Constructor
		COMPARTMENT(COMPARTMENT_CONSTRUCTOR constructor);
		//method responsible for evaluate dV/dt of the membrane voltage (Sum of all currents (Leak + Synapse
		//+ Intercompartment + Miscellaneous + current_sources + ionic channels) / Membrane capacitor)
		num_type eval_dV_dt_membrane_voltage_mV_ms();
		//method responsible for atualize monitors if any
		void atualize_monitors();

		//Get compartment parameters
		COMPARTMENT_PARAMETERS get_parameters();

		//Get compartment name
		std::string get_name();

		//Add Components 
		//Ionic Channels
		void add_new_ionic_channel(NEW_DESTEXHE_KF_CHANNEL parameters);
		void add_new_ionic_channel(NEW_DESTEXHE_KS_CHANNEL parameters);
		void add_new_ionic_channel(NEW_DESTEXHE_NA_CHANNEL parameters);

		//Current  Source
		void add_new_current_source(NEW_DC_CURRENT_SOURCE parameters);

		//Monitors
		MONITORS* add_new_monitor(NEW_ACTION_POTENCIAL_MONITOR parameters);
		MONITORS* add_new_monitor(NEW_VOLTAGE_MONITOR parameters);

		//intercompartment conductance
		void add_new_intercompartment_conductance(INTERCOMPARTMENT_CONDUCTANCE_CONSTRUCTOR constructor);


	protected:
	private:
		//VARS:
		//compartment name
		std::string name;
		//Parameters 
		COMPARTMENT_PARAMETERS parameters;
		//Neuron simulation_time pointer
		num_type* p_simulation_time_ms;
		//Simulation step_size pointer
		num_type* p_simulation_step_size_ms;
		//Current sources
		std::vector<CURRENT_SOURCES*> currrent_sources;
		//Ionic channels 
		std::vector<IONIC_CHANNELS*> ionic_channels;
		//Monitors
		std::vector<MONITORS*> monitors;
		//Synapses
		std::vector<SYNAPSES*> synapses;
		//Miscellaneous
		std::vector<MISCELLANEOUS*> miscellaneous;
		//Intercompartment conductance
		std::vector<INTERCOMPARTMENT_CONDUCTANCE*> intercompartment_conductances;
};

#endif