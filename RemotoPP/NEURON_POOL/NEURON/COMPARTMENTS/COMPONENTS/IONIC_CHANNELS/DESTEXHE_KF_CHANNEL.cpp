#include "DESTEXHE_KF_CHANNEL.h"
#include <limits>
#include <math.h>

DESTEXHE_KF_CHANNEL::DESTEXHE_KF_CHANNEL(DESTEXHE_KF_CHANNEL_CONSTRUCTOR constructor)
{
	this->name = "DESTEXHE_KF_CHANNEL";
	this->n0 = 0;
	this->gKf_bar_uS = 1e3 * (constructor.region_area_um2 * 1e-8) * constructor.gKf_bar_mS_cm2;
    this->alpha_n_ms = constructor.alpha_n_ms;
    this->beta_n_ms = constructor.beta_n_ms;
    this->treshold_voltage_mV = constructor.treshold_voltage_mV;
	this->n_time_to_peak_ms = constructor.n_time_to_peak_ms;
    this->refractory_period_ms = constructor.refractory_period_ms;
    this->state = DESTEXHE_STATE_OFF;
    this->time_last_pulse_ms = -std::numeric_limits<num_type>::max();
	this->k_ion_nernst_potencial_mV = constructor.k_ion_nernst_potencial_mV;
	this->pointer_2_neuron_time_ms = constructor.pointer_2_neuron_time_ms;
	this->pointer_2_compartment_membrane_voltage_mV = constructor.pointer_2_compartment_membrane_voltage_mV;
}

num_type DESTEXHE_KF_CHANNEL::eval_ionic_current_nA()
{
    num_type current_nA;
    num_type n;
    //Evaluate current
    if(this->state == DESTEXHE_STATE_OFF)
		n = this->n0 * FAST::exp(-this->beta_n_ms*(*this->pointer_2_neuron_time_ms -this->time_last_pulse_ms));
    else 
		n = 1.0 + (this->n0 - 1.0) * FAST::exp(-this->alpha_n_ms*(*this->pointer_2_neuron_time_ms -this->time_last_pulse_ms));
	//Positive currents contributes to increase compartment voltage
	current_nA = gKf_bar_uS * (n*n*n*n) * (this->k_ion_nernst_potencial_mV - *this->pointer_2_compartment_membrane_voltage_mV);
	//Check state transition (check Destexhe paper for more information)
	if (this->state == DESTEXHE_STATE_ON)
	{
		if ((*this->pointer_2_neuron_time_ms - this->time_last_pulse_ms) > this->n_time_to_peak_ms)
		{
			this->state = DESTEXHE_STATE_OFF;
			this->time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->n0 = n;
		}
	}
	else
	{
		if (((*this->pointer_2_neuron_time_ms - this->time_last_pulse_ms) > this->refractory_period_ms) &&
			(*this->pointer_2_compartment_membrane_voltage_mV > this->treshold_voltage_mV))
		{
			this->state = DESTEXHE_STATE_ON;
			this->time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->n0 = n;
		}
	}
    return current_nA;
}

std::string DESTEXHE_KF_CHANNEL::get_name()
{
	return this->name;
}

