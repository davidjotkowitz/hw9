#include "port.h"
#include <cstdlib>


Port::Port(String pattern):Field(pattern, PORT){}

bool Port::set_value(String val){

	String* range_taken;	
	size_t size = 0;	
	val.split("-", &range_taken, &size);
	if ((size)!=2){
		delete[] range_taken;
		return false;
	}
	
	
	range[0]= range_taken[0].trim().to_integer();
	range[1]= range_taken[1].trim().to_integer();
	delete[] range_taken;
	
	if(range[0] > range[1]){
		return false;
	}else{
		return true;
	}
}

bool Port::match_value(String val) const{

//we will only give the function the actual ip address, 
//so we dont need to worry about trims.
	int address = val.trim().to_integer();
	return ((address>=range[0]) && (address<=range[1]));
}

