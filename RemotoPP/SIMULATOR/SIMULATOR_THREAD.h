
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
#ifndef SIMULATOR_THREAD_H
#define SIMULATOR_THREAD_H

//includes
#include "DEFAULT_DATA_TYPE.h"
#include <vector>
#include <thread>
#include <mutex>
#include <string>

class SIMULATOR_THREAD_ITENS_2_SIMULATE
{
public:
	virtual void atualize(void) = 0;
};

typedef struct SIMULATOR_THREAD_CONSTRUCTOR_STRUCT
{
	//Itens to simulate
	std::vector<SIMULATOR_THREAD_ITENS_2_SIMULATE*> itens_2_simulate;
}SIMULATOR_THREAD_CONSTRUCTOR;

class SIMULATOR_THREAD
{
	//Vars:
public:
	//Data locker 
	std::mutex thread_data_locker_mutex;
	//Conditional variables
	//Set if thread has finished one atualize step 
	std::condition_variable done_CV;
	bool done_flag;
	//Set if a new atualize step is required
	std::condition_variable start_CV;
	bool start_flag;
	//Flag to be seted at the end of the simulation
	bool finish_flag;
	//methods
	SIMULATOR_THREAD(SIMULATOR_THREAD_CONSTRUCTOR constructor);
	static void thread_function(SIMULATOR_THREAD& p_simulator_thread);
private:
	//Thread handle
	std::thread thread_handle;
	//Itens to simulate
	std::vector<SIMULATOR_THREAD_ITENS_2_SIMULATE*> itens_2_simulate;
};

#endif