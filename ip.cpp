
#include "ip.h"
#include <cstring>
#include <iostream>



Ip::Ip(String pattern): Field(pattern, IP) {}

bool Ip::set_value(String val){

	String* rules;
	size_t size = 0;	
	val.split("/", &rules, &size);

	if (size != 2){
		delete[] rules;
		return false;
	}

//here we take the actual address
	int ip = rules[0].trim().to_integer();
//here we take the mask. 
	int mask = 32 - rules[1].trim().to_integer();
	delete[] rules;
	if((mask < 0) || (mask > 32)) {	
		return false;
	}


	unsigned int mask_bit;
	if(mask == 32){
		mask_bit=0xFFFFFFFF;
	}else{
		mask_bit=((unsigned int)1 << mask)-1;
	}
//this gives us the lowest value to be with zeros in all the masked bits, 
//and the highest value to be with ones in all masked bits
	low = ip & (~mask_bit);
	high = ip | mask_bit; 
	
	return true;
}

bool Ip::match_value(String val) const{
//we will only give the function the actual ip address, 
//so we dont need to worry about trims or anything
	unsigned int address = (unsigned int)val.trim().to_integer();
	return ((address>=low) && (address<=high));
}



