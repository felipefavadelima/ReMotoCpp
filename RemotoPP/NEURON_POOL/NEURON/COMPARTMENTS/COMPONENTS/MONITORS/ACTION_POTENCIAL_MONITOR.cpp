#include "ACTION_POTENCIAL_MONITOR.h"

ACTION_POTENCIAL_MONITOR::ACTION_POTENCIAL_MONITOR(ACTION_POTENCIAL_MONITOR_CONSTRUCTOR constructor)
{
	this->name = constructor.name;
	this->type = "AP_MONITORS";
	this->on_voltage_treshold_mV = constructor.on_treshold_voltage_mV;
	this->off_voltage_treshold_mV = constructor.off_treshold_voltage_mV;
	this->state = AP_MONITOR_STATE_OFF;
	this->pointer_2_neuron_time_ms = constructor.pointer_2_neuron_time_ms;
	this->pointer_2_compartment_membrane_voltage_mV = constructor.pointer_2_compartment_membrane_voltage_mV;
	//Initialize Data
	auto Data1 = new std::vector<num_type>;
	this->Data.push_back(*Data1);
}

void ACTION_POTENCIAL_MONITOR::atualize_monitor()
{
	if (this->state == AP_MONITOR_STATE_OFF)
	{
		if (*this->pointer_2_compartment_membrane_voltage_mV > this->on_voltage_treshold_mV)
		{
			this->state = AP_MONITOR_STATE_ON;
			this->Data[0].push_back(*this->pointer_2_neuron_time_ms);
		}
	}
	else
	{
		if (*this->pointer_2_compartment_membrane_voltage_mV < this->off_voltage_treshold_mV)
		{
			this->state = AP_MONITOR_STATE_OFF;
		}
	}
}

std::vector<std::vector<num_type>>* ACTION_POTENCIAL_MONITOR::get_p_monitor_data()
{
	return &this->Data;
}

std::string ACTION_POTENCIAL_MONITOR::get_name()
{
	return this->name;
}

std::string ACTION_POTENCIAL_MONITOR::get_type()
{
	return this->type;
}

std::vector<std::string> ACTION_POTENCIAL_MONITOR::get_dimensions(void)
{
	std::vector<std::string> dimensions_list;
	dimensions_list.push_back("AP_time_ms");
	return dimensions_list;
}
