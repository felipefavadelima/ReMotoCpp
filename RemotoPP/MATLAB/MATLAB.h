
//Code description: This code implements a MATLAB access to plot data

//CHANGE LOG:
//Date:29/10/2105
//By: Felipe Fava de Lima - felipe@leb.usp.br - felipefavadelima@gmail.com
//Description: First code

//Programming good practices: When you´re writing a new code, please try to use
//intuitive variables and methods names, add comments as you can , and please,
//try to write your code not for you , but for others !!!  
//Good Work!

//Steps to use this code
//1 - A x64 Matlab version must be installed in the computer
//2 - Configure the following paths in your compiler:
//Include path: ..\MATLAB\(Matlab version folder)\bin\win64 (Ex: C:\Program Files\MATLAB\R2012b\bin\win64)
//Library path: ..\MATLAB\(Matlab version folder)\extern\lib\win64\microsof (Ex:C:\Program Files\MATLAB\R2012b\extern\lib\win64\microsof)
//Executables path: ..\MATLAB\(Matlab version folder)\bin\win64 (Ex: C:\Program Files\MATLAB\R2012b\bin\win64)
//Set the following library dependencies: libmx.lib , libeng.lib , libmex.lib, libmat.lib
//To debug, set the following Enviroment: PATH=..\MATLAB\(Matlab version folder)\bin\win64\;%PATH% (Ex: PATH=C:\Program Files\MATLAB\R2012b\bin\win64\;%PATH%)
//Reference video: https://www.youtube.com/watch?v=vQ5aIxCX3To

//check if inclued before
#ifndef MATLAB_H
#define MATLAB_H

//includes
//Matlab
#include <Engine.h>
#include <string>
#include <vector>
#include "DEFAULT_DATA_TYPE.h"
#pragma comment (lib, "libmat.lib")
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libeng.lib")

class MATLAB
{
	public:
		MATLAB();
		void send_array_2_matlab_temp_var(std::vector<num_type>* array);
		void eval(std::string command_2_eval);
	private:
		Engine* matlab_engine_pointer;
};

#endif