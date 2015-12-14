#include "SIMULATOR_THREAD.h"

SIMULATOR_THREAD::SIMULATOR_THREAD(SIMULATOR_THREAD_CONSTRUCTOR constructor)
{
	this->done_flag = false;
	this->finish_flag = false;
	this->start_flag = false;
	this->itens_2_simulate = constructor.itens_2_simulate;
	this->thread_handle = std::thread(SIMULATOR_THREAD::thread_function,std::ref(*this));
}

void SIMULATOR_THREAD::thread_function(SIMULATOR_THREAD& p_simulator_thread)
{
	//Atualize loop thread
	bool finish_flag = false;
	do {
		std::unique_lock<std::mutex> locker(p_simulator_thread.thread_data_locker_mutex);
		while (p_simulator_thread.start_flag == false) p_simulator_thread.start_CV.wait(locker);
		finish_flag = p_simulator_thread.finish_flag;
		for (unsigned int i = 0; i < p_simulator_thread.itens_2_simulate.size(); i++)
			p_simulator_thread.itens_2_simulate[i]->atualize();
		p_simulator_thread.start_flag = false;
		p_simulator_thread.done_flag = true;
		p_simulator_thread.done_CV.notify_one();
	} while (finish_flag == false);
}