
//Code description: This code implements the neuron pool behaviour

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others !!!  
//Good Work!

//check if inclued before
#ifndef NEURON_POOL_H
#define NEURON_POOL_H

//includes
#include "DEFAULT_DATA_TYPE.h"
#include "NEURON.h"
#include <vector>
#include <string>

//Structs and classes:
typedef struct NEURON_POOL_CONSTRUCTOR_STRUCT
{
	//Pool name
	std::string name;
	//Simulation time step size
	num_type simulation_step_size;
}NEURON_POOL_CONSTRUCTOR;

typedef struct NEW_NEURON_POOL_STRUCT
{
	//Pool name
	std::string name;
}NEW_NEURON_POOL;

class NEURON_POOL
{
public:
	//METHODS:
	NEURON_POOL(NEURON_POOL_CONSTRUCTOR constructor);
	//add a new neuron to pool
	NEURON* add_new_neuron(NEW_NEURON parameters);
	//get neurons vector 
	std::vector<NEURON*> get_neurons_vector();
protected:
private:
	//simulation step size
	num_type simulation_step_size;
	//Neurons list
	std::vector<NEURON*> neurons;
	//Neuron pool name
	std::string name;

};
#endif