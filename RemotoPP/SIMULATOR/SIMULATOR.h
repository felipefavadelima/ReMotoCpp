
//Code description: This code implements the simulator behaviour

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others !!!  
//Good Work!

//check if inclued before
#ifndef SIMULATOR_H
#define SIMULATOR_H

//includes
#include "DEFAULT_DATA_TYPE.h"
#include "NEURON_POOL.h"
#include "SIMULATOR_THREAD.h"
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include "MATLAB.h"


typedef struct SIMULATOR_CONSTRUCTOR_STRUCT
{
	//Total simulation time
	num_type total_simulation_time_ms;
	//Simulation time step
	num_type simulation_step_time_ms;
	//Simulator name
	std::string name;
}SIMULATOR_CONSTRUCTOR;

class SIMULATOR
{
public:
	//Vars
	//Methods
	SIMULATOR(SIMULATOR_CONSTRUCTOR constructor);
	//Start threads
	void simulate(void);
	//Add new neuron pool
	NEURON_POOL* add_new_neuron_pool(NEW_NEURON_POOL parameters);
	//Get name
	std::string get_name(void);
	//Add a monitor
	void add_new_monitor(MONITORS* monitor);
	//Save monitors
	void save_monitors(std::string file_name);
	//Sendo monitors to matlab
	void send_monitors_2_matlab();
private:
	//Objects to simulate
	std::vector<NEURON_POOL*> NEURON_POOLS;
	//Add others objects to simulate here:
	//
	//list of monitors
	std::vector<MONITORS*> monitors;
	//Vector of Threads
	std::vector<SIMULATOR_THREAD*> threads;
	//Total simulation time
	num_type total_simulation_time_ms;
	//Simulation time step
	num_type simulation_step_time_ms;
	//Simulator name
	std::string name;
	//Matlab interfase
	MATLAB matlab_console;
};
#endif