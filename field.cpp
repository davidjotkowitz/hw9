#include "field.h"
#include <cstring>
#include <iostream>
#include "ip.h"
#include "port.h"


Field::Field(String pattern, field_type type):pattern(pattern),type(type){}

Field::Field(String pattern):pattern(pattern),type(GENERIC){}

Field::~Field(){}
	//delete this->pattern;  //do we need a this?

field_type Field::get_type() const{
	return type;
}


bool Field::set_value(String val){
	if(this->type==IP){
		return ((Ip*)this)->set_value(val);
	} else if(this->type==PORT){
		return ((Ip*)this)->set_value(val);
	}else return false;
}


bool Field::match_value(String val) const{
	if(this->type==IP){
		return ((Ip*)this)->match_value(val);
	} else if(this->type==PORT){
		return ((Port*)this)->match_value(val);;
	}else return false;	
}

bool Field::match(String packet){
	
	String *packet_str;	
	size_t packet_cnt= 0;
	
//here we split our packet into it's address elements, by ","
	packet.split(",", &packet_str, &packet_cnt);
	
	if (!packet_cnt){
		return false;
	} 

	String *address;
	size_t address_cnt= 0;
	bool val = false;	

	for(size_t i = 0; i < packet_cnt; i++){	

//here we split the element to its type, and its actual address, by "="
		packet_str[i].split("=", &address, &address_cnt);	
		if (!address_cnt){
			continue;
		} 
		
//if the element matches the rule belonging to this, we will return true
		if (address_cnt==2){		
			if (pattern.trim().equals(address[0].trim())){
				val = match_value(address[1].trim());
			}
		}		
		delete[] address;
	}
	delete[] packet_str;	
	return val;
}
