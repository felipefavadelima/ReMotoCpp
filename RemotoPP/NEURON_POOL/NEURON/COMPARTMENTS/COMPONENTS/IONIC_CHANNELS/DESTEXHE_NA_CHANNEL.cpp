#include "DESTEXHE_NA_CHANNEL.h"
#include <limits>
#include <math.h>

DESTEXHE_NA_CHANNEL::DESTEXHE_NA_CHANNEL(DESTEXHE_NA_CHANNEL_CONSTRUCTOR constructor)
{
	this->name = "DESTEXHE_NA_CHANNEL";
	this->gNa_bar_uS = 1e3 * (constructor.region_area_um2 * 1e-8) * constructor.gNa_bar_mS_cm2;
    this->m0 = 0;
    this->alpha_m_ms = constructor.alpha_m_ms;
    this->beta_m_ms = constructor.beta_m_ms;
    this->h0 = 0;
    this->alpha_h_ms = constructor.alpha_h_ms;
    this->beta_h_ms = constructor.beta_h_ms;
    this->treshold_voltage_mV = constructor.treshold_voltage_mV;
	this->h_time_to_peak_ms = constructor.h_time_to_peak_ms;
	this->m_time_to_peak_ms = constructor.m_time_to_peak_ms;
    this->refractory_period_ms = constructor.refractory_period_ms;
    this->state_m = DESTEXHE_STATE_OFF;
	this->state_h = DESTEXHE_STATE_OFF;
    this->m_time_last_pulse_ms = -std::numeric_limits<num_type>::max();
	this->h_time_last_pulse_ms = -std::numeric_limits<num_type>::max();
	this->Na_ion_nernst_potencial_mV = constructor.Na_ion_nernst_potencial_mV;
	this->pointer_2_neuron_time_ms = constructor.pointer_2_neuron_time_ms;
	this->pointer_2_compartment_membrane_voltage_mV = constructor.pointer_2_compartment_membrane_voltage_mV;
}

num_type DESTEXHE_NA_CHANNEL::eval_ionic_current_nA()
{
    num_type current_nA;
    num_type m;
    num_type h;
    //Evaluate current
	if (this->state_m == DESTEXHE_STATE_OFF)
		m = this->m0 * FAST::exp(-this->beta_m_ms*(*this->pointer_2_neuron_time_ms - this->m_time_last_pulse_ms));
	else
		m = 1.0 + (this->m0 - 1.0) * FAST::exp(-this->alpha_m_ms*(*this->pointer_2_neuron_time_ms - this->m_time_last_pulse_ms));
	if (this->state_h == DESTEXHE_STATE_OFF)
		h = 1.0 + (this->h0 - 1.0) * FAST::exp(-this->alpha_h_ms*(*this->pointer_2_neuron_time_ms - this->h_time_last_pulse_ms));
	else
		h = this->h0 * FAST::exp(-this->beta_h_ms*(*this->pointer_2_neuron_time_ms - this->h_time_last_pulse_ms));
	//Positive currents contributes to increase compartment voltage
	current_nA = gNa_bar_uS * (m*m*m) * h * (this->Na_ion_nernst_potencial_mV - *this->pointer_2_compartment_membrane_voltage_mV);
	//Check state transition (check Destexhe paper for more information)
	if ((this->state_m == DESTEXHE_STATE_ON) || (this->state_h == DESTEXHE_STATE_ON))
	{
		if ((*this->pointer_2_neuron_time_ms - this->m_time_last_pulse_ms) > this->m_time_to_peak_ms)
		{
			this->state_m = DESTEXHE_STATE_OFF;
			this->m_time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->m0 = m;
		}
		if ((*this->pointer_2_neuron_time_ms - this->h_time_last_pulse_ms) > this->h_time_to_peak_ms)
		{
			this->state_h = DESTEXHE_STATE_OFF;
			this->h_time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->h0 = h;
		}
	}
	else
	{
		if (((*this->pointer_2_neuron_time_ms - this->m_time_last_pulse_ms) > this->refractory_period_ms) &&
			((*this->pointer_2_neuron_time_ms - this->h_time_last_pulse_ms) > this->refractory_period_ms) &&
			(*this->pointer_2_compartment_membrane_voltage_mV > this->treshold_voltage_mV))
		{
			this->state_m = DESTEXHE_STATE_ON;
			this->state_h = DESTEXHE_STATE_ON;
			this->m_time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->h_time_last_pulse_ms = *this->pointer_2_neuron_time_ms;
			this->m0 = m;
			this->h0 = h;
		}
	}
    return current_nA;
}

std::string DESTEXHE_NA_CHANNEL::get_name()
{
	return this->name;
}