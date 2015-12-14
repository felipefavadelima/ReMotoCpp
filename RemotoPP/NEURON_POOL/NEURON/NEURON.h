
//Code description: This code implements the neuron behaviour

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others !!!  
//Good Work!

//check if inclued before
#ifndef NEURON_H
#define NEURON_H

//includes
#include "DEFAULT_DATA_TYPE.h"
#include "COMPARTMENT.h"
#include "SIMULATOR_THREAD.h"
#include <vector>
#include <string>


//Structs and classes:
typedef struct NEURON_CONSTRUCTOR_STRUCT
{
	//Neuron name
	std::string name;
	//Simulation step_size
	num_type simulation_step_size_ms;
}NEURON_CONSTRUCTOR;

typedef struct NEW_NEURON_STRUCT
{
	//Neuron name
	std::string name;
}NEW_NEURON;

class NEURON: public SIMULATOR_THREAD_ITENS_2_SIMULATE
{
public:
	//METHODS:
	//Constructor
	NEURON(NEURON_CONSTRUCTOR constructor);
	//Method responsible to atualize the neuron compartments voltages
	void atualize(void);
	//Add new a new intercompartment conductance
	void add_new_intercompartment_conductance(COMPARTMENT* compartment1, COMPARTMENT* compartment2);
	//Add a new compartment
	COMPARTMENT* add_new_compartment(NEW_COMPARTMENT parameters);
	//Get compartment name
	std::string get_name();
protected:
private:
	//Current simulation_time
	num_type simulation_time_ms;
	//Simulation step_size
	num_type simulation_step_size_ms;
	//Compartments list
	std::vector<COMPARTMENT*> compartments;
	//VARS:
	std::string name;
};

#endif