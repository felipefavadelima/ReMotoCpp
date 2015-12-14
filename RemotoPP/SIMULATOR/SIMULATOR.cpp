#include "SIMULATOR.h"

SIMULATOR::SIMULATOR(SIMULATOR_CONSTRUCTOR constructor)
{
	this->simulation_step_time_ms = constructor.simulation_step_time_ms;
	this->name = constructor.name;
	this->total_simulation_time_ms = constructor.total_simulation_time_ms;
}

//Run simulation
void SIMULATOR::simulate(void)
{
	unsigned long int i = 0;
	unsigned long int j = 0;
	//Check number of cores = number of threads
	unsigned int n_threads = std::thread::hardware_concurrency();
	//Get itens to simulate
	std::vector<SIMULATOR_THREAD_ITENS_2_SIMULATE*> itens_2_simulate;
	//Neurons
	std::vector<NEURON*> neurons;
	for (i = 0; i < this->NEURON_POOLS.size(); i++)
	{
		neurons = NEURON_POOLS[i]->get_neurons_vector();
		for (j = 0; j < neurons.size(); j++)
			itens_2_simulate.push_back((SIMULATOR_THREAD_ITENS_2_SIMULATE*)neurons[j]);
	}
	//Others itens to add go here
	//...

	//Number of itens in each thread
	unsigned long int n_itens_thread = (unsigned long int) round(itens_2_simulate.size() / n_threads);
	//Distribute simulation itens to threads
	for (i = 0; i < n_threads - 1; i++)
	{
		SIMULATOR_THREAD_CONSTRUCTOR constructor;
		for (j = 0; j < n_itens_thread; j++)
		{
			constructor.itens_2_simulate.push_back(itens_2_simulate.back());
			itens_2_simulate.pop_back();
		}
		this->threads.push_back(new SIMULATOR_THREAD(constructor));
	}
	SIMULATOR_THREAD_CONSTRUCTOR constructor;
	n_itens_thread = (unsigned long int) itens_2_simulate.size();
	for (j = 0; j < n_itens_thread; j++)
	{
		constructor.itens_2_simulate.push_back(itens_2_simulate.back());
		itens_2_simulate.pop_back();
	}
	this->threads.push_back(new SIMULATOR_THREAD(constructor));

	//Run simulation
	for (num_type time = 0; time < this->total_simulation_time_ms; time += this->simulation_step_time_ms)
	{
		//Wake up threads to run next step
		for (i = 0; i < this->threads.size(); i++)
		{
			std::unique_lock<std::mutex> locker(this->threads[i]->thread_data_locker_mutex);
			this->threads[i]->start_flag = true;
			this->threads[i]->start_CV.notify_one();
		}
		//Wait threads to finish their jobs
		for (i = 0; i < this->threads.size(); i++)
		{
			std::unique_lock<std::mutex> locker(this->threads[i]->thread_data_locker_mutex);
			while (this->threads[i]->done_flag == false) this->threads[i]->done_CV.wait(locker);
			this->threads[i]->done_flag = false;
		}
	}

	//Close threads
	//Wake up threads to run next step
	for (i = 0; i < this->threads.size(); i++)
	{
		std::unique_lock<std::mutex> locker(this->threads[i]->thread_data_locker_mutex);
		this->threads[i]->finish_flag = true;
		this->threads[i]->start_flag = true;
		this->threads[i]->start_CV.notify_one();
	}
	//Wait threads to finish their jobs
	for (i = 0; i < this->threads.size(); i++)
	{
		std::unique_lock<std::mutex> locker(this->threads[i]->thread_data_locker_mutex);
		while (this->threads[i]->done_flag == false) this->threads[i]->done_CV.wait(locker);
		this->threads[i]->done_flag = false;
	}
}
//Add new neuron pool
NEURON_POOL* SIMULATOR::add_new_neuron_pool(NEW_NEURON_POOL parameters)
{
	NEURON_POOL_CONSTRUCTOR constructor;
	constructor.name = parameters.name;
	constructor.simulation_step_size = this->simulation_step_time_ms;
	NEURON_POOL* neuron_pool = new NEURON_POOL(constructor);
	NEURON_POOLS.push_back(neuron_pool);
	return neuron_pool;
}
//Get name
std::string SIMULATOR::get_name(void)
{
	return this->name;
}

//Add a monitor
void SIMULATOR::add_new_monitor(MONITORS* monitor)
{
	this->monitors.push_back(monitor);
}
//Save monitors
void SIMULATOR::save_monitors(std::string file_name)
{

}
//Send monitors to matlab
void SIMULATOR::send_monitors_2_matlab()
{

	for (unsigned long int n_monitor = 0; n_monitor < this->monitors.size(); n_monitor++)
	{
		//get monitor dimension
		std::vector<std::string> dimensions = this->monitors[n_monitor]->get_dimensions();
		//get monitor type
		std::string type = this->monitors[n_monitor]->get_type();
		//get monitor name
		std::string name = this->monitors[n_monitor]->get_name();
		//get p_2_data
		std::vector<std::vector<num_type>>* p_2_data = this->monitors[n_monitor]->get_p_monitor_data();
		for (unsigned long int n_dimension = 0; n_dimension < dimensions.size(); n_dimension++)
		{
			//send dimension to matlab
			std::vector<num_type>* p_dimension;
			p_dimension = &(p_2_data->at(n_dimension));
			this->matlab_console.send_array_2_matlab_temp_var(p_dimension);
			//Create variable name
			std::string var_name = type + "." + name + "." + dimensions[n_dimension];
			this->matlab_console.eval(var_name + "= temp_var;");
		}
	}
}