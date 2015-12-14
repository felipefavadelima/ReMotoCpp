#include "VOLTAGE_MONITOR.h"

VOLTAGE_MONITOR::VOLTAGE_MONITOR(VOLTAGE_MONITOR_CONSTRUCTOR constructor)
{
	this->name = constructor.name;
	this->type = "VOLTAGE_MONITORS";
	this->pointer_2_neuron_time_ms = constructor.pointer_2_neuron_time_ms;
	this->pointer_2_compartment_membrane_voltage_mV = constructor.pointer_2_compartment_membrane_voltage_mV;
	//Initialize Data
	auto Data1 = new std::vector<num_type>;
	auto Data2 = new std::vector<num_type>;
	this->Data.push_back(*Data1);
	this->Data.push_back(*Data2);
}

void VOLTAGE_MONITOR::atualize_monitor()
{
	this->Data[1].push_back(*this->pointer_2_compartment_membrane_voltage_mV);
	this->Data[0].push_back(*this->pointer_2_neuron_time_ms);
}

std::vector<std::vector<num_type>>* VOLTAGE_MONITOR::get_p_monitor_data()
{
	return &this->Data;
}

std::string VOLTAGE_MONITOR::get_name()
{
	return this->name;
}

std::string VOLTAGE_MONITOR::get_type()
{
	return this->type;
}

std::vector<std::string> VOLTAGE_MONITOR::get_dimensions(void)
{
	std::vector<std::string> dimensions_list;
	dimensions_list.push_back("time_ms");
	dimensions_list.push_back("voltage_mV");
	return dimensions_list;
}