#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>

//using the parse_input function given to do the actual scanning.
extern void parse_input(Field&);


int main(int argc, char** argv){

	String rules(argv[1]);
	String* parts;
	size_t size = 0;	

//here we split the rule recieved to find its type and pattern(dst or src).
	rules.split("=", &parts, &size);

//this "if" will set the rule for ip addresses.
	if((parts[0].trim().equals(String("src-ip")))|| 
		(parts[0].trim().equals(String("dst-ip")))){
		
		Ip iprules(parts[0].trim());     	
		iprules.set_value(parts[1].trim());
		parse_input(iprules);
	}

//this "if" will set the rule for port addresses.
	if((parts[0].trim().equals(String("src-port")))|| 
	  (parts[0].trim().equals(String("dst-port"))))
	{
		Port portrules(parts[0].trim());
		portrules.set_value(parts[1].trim());
		parse_input(portrules);
	}

//it is up to the user to delete array split.
	delete[] parts;
}

