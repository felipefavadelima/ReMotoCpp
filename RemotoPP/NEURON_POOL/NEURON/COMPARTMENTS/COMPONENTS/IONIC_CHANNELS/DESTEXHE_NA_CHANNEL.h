//Code description: This code implements an Na(Sodium) ionic channel using Destexhe aproximation.
//Reference Paper: Destexhe, A.; Mainen ,Z. F.; Sejnowski, T.J. - An efficient method for computing
//synaptic Conductances based on a kinetic-model of receptor-binding - 1994a
//As any ionic channel , it implements:
//num_type eval_ionic_current_nA(num_type membrane_voltage_mV, num_type time_ms)

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others understand!!! 
//Good Work!

//Check if inclued before:
#ifndef DESTEXHE_NA_CHANNEL_H
#define DESTEXHE_NA_CHANNEL_H

//Includes:
#include "DEFAULT_DATA_TYPE.h"
#include "IONIC_CHANNELS.h"
#include "FAST_MATH.h"

//Definitions
#ifndef DESTEXHE_STATE_ON
#define DESTEXHE_STATE_ON   true
#endif // DESTEXHE_STATE_ON
#ifndef DESTEXHE_STATE_OFF
#define DESTEXHE_STATE_OFF   false
#endif // DESTEXHE_STATE_OFF

//Structs and Classes
typedef struct DESTEXHE_NA_CHANNEL_CONSTRUCTOR_STRUCT
{
	//Channel specific maximum conductance mS/cm2
	num_type gNa_bar_mS_cm2;
	//Channel region area um2
	num_type region_area_um2;
	//Parameter alpha_m of Destexhe state equation (1/ms)
	num_type alpha_m_ms;
	//Parameter beta_m of Destexhe state equation (1/ms)
	num_type beta_m_ms;
	//Parameter alpha_h of Destexhe state equation (1/ms)
	num_type alpha_h_ms;
	//Parameter beta_h of Destexhe state equation (1/ms)
	num_type beta_h_ms;
	//Treshold voltage (mv) to change state 
	num_type treshold_voltage_mV;
	//Pulse duration(ms) to change state from ON to OFF after a upper treshold condition
	num_type m_time_to_peak_ms;
	num_type h_time_to_peak_ms;
	//Refractory period (ms), avoiding a state change
	num_type refractory_period_ms;
	//Na ion nernst potencial in mV
	num_type Na_ion_nernst_potencial_mV;
	//Pointer to the current neuron time ms
	num_type* pointer_2_neuron_time_ms;
	//This compartment membrane voltage pointer mV
	num_type* pointer_2_compartment_membrane_voltage_mV;
}DESTEXHE_NA_CHANNEL_CONSTRUCTOR;

typedef struct NEW_DESTEXHE_NA_CHANNEL_STRUCT
{
	//Channel specific maximum conductance mS/cm2
	num_type gNa_bar_mS_cm2;
	//Parameter alpha_m of Destexhe state equation (1/ms)
	num_type alpha_m_ms;
	//Parameter beta_m of Destexhe state equation (1/ms)
	num_type beta_m_ms;
	//Parameter alpha_h of Destexhe state equation (1/ms)
	num_type alpha_h_ms;
	//Parameter beta_h of Destexhe state equation (1/ms)
	num_type beta_h_ms;
	//Treshold voltage (mv) to change state 
	num_type treshold_voltage_mV;
	//Pulse duration(ms) to change state from ON to OFF after a upper treshold condition
	num_type m_time_to_peak_ms;
	num_type h_time_to_peak_ms;
	//Refractory period (ms), avoiding a state change
	num_type refractory_period_ms;
	//Na ion nernst potencial in mV
	num_type Na_ion_nernst_potencial_mV;
}NEW_DESTEXHE_NA_CHANNEL;

//Class of DESTEXHE_NA_CHANNEL
class DESTEXHE_NA_CHANNEL: public IONIC_CHANNELS
{
public:
	//Public Methods
	DESTEXHE_NA_CHANNEL(DESTEXHE_NA_CHANNEL_CONSTRUCTOR constructor);
	//Method responsible for calculate the channel current(nA) at membrane voltage (mV) and time (ms)
	//Positive currents contributes to increase compartment voltage
	num_type eval_ionic_current_nA();
	//Get channel name
	std::string get_name(void);
protected:
private:
	//Private Vars
	//Name
	std::string name;
	//Maximum channel conductance (uS)
	num_type gNa_bar_uS;
	//Parameter m0 of Destexhe state equation
	num_type m0;
	//Parameter alpha_m of Destexhe state equation (1/ms)
	num_type alpha_m_ms;
	//Parameter beta_m of Destexhe state equation (1/ms)
	num_type beta_m_ms;
	//Parameter h0 of Destexhe state equation
	num_type h0;
	//Parameter alpha_h of Destexhe state equation (1/ms)
	num_type alpha_h_ms;
	//Parameter beta_h of Destexhe state equation (1/ms)
	num_type beta_h_ms;
	//Current state of Desxtehe Channel (o = OFF , 1 = ON)
	bool state_m;
	bool state_h;
	//Time of the last state transition (ms) 
	num_type m_time_last_pulse_ms;
	//Time of the last state transition (ms) 
	num_type h_time_last_pulse_ms;
	//Treshold voltage (mv) to change state 
	num_type treshold_voltage_mV;
	//Pulse duration(ms) to change state from ON to OFF after a upper treshold condition
	num_type m_time_to_peak_ms;
	num_type h_time_to_peak_ms;
	//Refractory period (ms), avoiding a state change
	num_type refractory_period_ms;
	//Na ion nernst potencial in mV
	num_type Na_ion_nernst_potencial_mV;
	//Pointer to the current neuron time ms
	num_type* pointer_2_neuron_time_ms;
	//This compartment membrane voltage pointer mV
	num_type* pointer_2_compartment_membrane_voltage_mV;
};

#endif // DESTEXHE_NA_CHANNEL_H
