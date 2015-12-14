#include "NEURON_POOL.h"

//METHODS:
NEURON_POOL::NEURON_POOL(NEURON_POOL_CONSTRUCTOR constructor)
{
	this->name = constructor.name;
	this->simulation_step_size = constructor.simulation_step_size;
}
//add a new neuron to pool
NEURON* NEURON_POOL::add_new_neuron(NEW_NEURON parameters)
{
	NEURON_CONSTRUCTOR constructor;
	constructor.name = parameters.name;
	constructor.simulation_step_size_ms = this->simulation_step_size;
	NEURON* neuron = new NEURON(constructor);
	this->neurons.push_back(neuron);
	return neuron;
}

//get neurons vector 
std::vector<NEURON*> NEURON_POOL::get_neurons_vector()
{
	return this->neurons;
}


