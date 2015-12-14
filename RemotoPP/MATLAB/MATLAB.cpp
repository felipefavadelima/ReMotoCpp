#include "MATLAB.h"

MATLAB::MATLAB()
{
	this->matlab_engine_pointer = engOpen("null");
	
}


void MATLAB::eval(std::string command_2_eval)
{
	engEvalString(this->matlab_engine_pointer, command_2_eval.c_str());
}

void MATLAB::send_array_2_matlab_temp_var(std::vector<num_type>* array)
{
	num_type * p_array = &(*array)[0];
	mxArray* x_data_mx = mxCreateDoubleMatrix((*array).size(), 1, mxREAL);
	memcpy((void *)mxGetPr(x_data_mx), (void *)p_array, sizeof(num_type) * (*array).size());
	engPutVariable(this->matlab_engine_pointer, "temp_var", x_data_mx);
}

