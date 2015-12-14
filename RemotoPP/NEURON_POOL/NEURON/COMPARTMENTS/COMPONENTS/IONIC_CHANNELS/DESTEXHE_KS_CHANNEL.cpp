#include "DESTEXHE_KS_CHANNEL.h"
#include <limits>
#include <math.h>

DESTEXHE_KS_CHANNEL::DESTEXHE_KS_CHANNEL(DESTEXHE_KS_CHANNEL_CONSTRUCTOR constructor)
{
	this->name = "DESTEXHE_KS_CHANNEL";
	this->q0 = 0;
	this->gKs_bar_uS = 1e3 * (constructor.region_area_um2 * 1e-8) * constructor.gKs_bar_mS_cm2;
    this->alpha_q_ms = constructor.alpha_q_ms;
    this->beta_q_ms = constructor.beta_q_ms;
    this->treshold_voltage_mV = constructor.treshold_voltage_mV;
	this->q_time_to_peak_ms = constructor.q_time_to_peak_ms;
    this->refractory_period_ms = constructor.refractory_period_ms;
    this->state = DESTEXHE_STATE_OFF;
    this->time_last_pulse_ms = -std::numeric_limits<num_type>::max();
	this->k_ion_nernst_potencial_mV = constructor.k_ion_nernst_potencial_mV;
	this->pointer_2_neuron_time_ms = constructor.pointer_2_neuron_time_ms;
	this->pointer_2_compartment_membrane_voltage_mV = constructor.pointer_2_compartment_membrane_voltage_mV;
}


num_type DESTEXHE_KS_CHANNEL::eval_ionic_current_nA()
{
    num_type current_nA;
    num_type q;
    //Evaluate current
    if(this->state == DESTEXHE_STATE_OFF)
		q = this->q0 * FAST::exp(-this->beta_q_ms*(*this->pointer_2_neuron_time_ms -this->time_last_pulse_ms));
	else
		q = 1.0 + (this->q0 - 1.0) * FAST::exp(-this->alpha_q_ms*(*this->pointer_2_neuron_time_ms -this->time_last_pulse_ms));
	//Positive currents contributes to increase compartment voltage
	current_nA = gKs_bar_uS * (q*q) * (this->k_ion_nernst_potencial_mV - *this->pointer_2_compartment_membrane_voltage_mV);
	//Check state transition (check Destexhe paper for more information)
	if (this->state == DESTEXHE_STATE_ON)
	{
		if ((*this->pointer_2_neuron_time_ms - this->time_last_pulse_ms) > this->q_time_to_peak_ms)
		{
			this->state = DESTEXHE_STATE_OFF;
			this->time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->q0 = q;
		}
	}
	else
	{
		if (((*this->pointer_2_neuron_time_ms - this->time_last_pulse_ms) > this->refractory_period_ms) &&
			(*this->pointer_2_compartment_membrane_voltage_mV > this->treshold_voltage_mV))
		{
			this->state = DESTEXHE_STATE_ON;
			this->time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->q0 = q;
		}
	}
    return current_nA;
}

std::string DESTEXHE_KS_CHANNEL::get_name()
{
	return this->name;
}