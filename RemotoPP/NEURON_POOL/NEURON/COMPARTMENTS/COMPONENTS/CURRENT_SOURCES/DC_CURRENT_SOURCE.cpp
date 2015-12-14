#include "DC_CURRENT_SOURCE.h"

DC_CURRENT_SOURCE::DC_CURRENT_SOURCE(DC_CURRENT_SOURCE_CONSTRUCTOR constructor)
{
	this->current_nA = constructor.current_nA;
	this->name = "DC_CURRENT_SOURCE";
}

num_type DC_CURRENT_SOURCE::eval_source_current_nA()
{
	//Positive currents contributes to increase compartment voltage
	return this->current_nA;
}

std::string DC_CURRENT_SOURCE::get_name(void)
{
	//Return name
	return this->name;
}