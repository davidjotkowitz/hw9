#!/bin/bash

#we read each rule seperatly, then "uniq" when we add the address
while read line
do
	line=`echo "$line" | tr -d ' ' | sed -e 's/#.*//'`
	
	if [[ "$line" == "" ]]; then
		continue
	fi

#here we parse acourding to ","
	readarray -d , -t rules <<< "$line"	
	
	packet_caught=""
	for rule in "${rules[@]}"
	do
#we go through all the addresses for every rule
		packet_caught+=`./firewall.exe "$rule" < $1`
		packet_caught+="\n"
	done

#we add to the list all the new addresses	
	list+=`echo -e "${packet_caught}" | sed '/^$/d' | sort | uniq -c  | grep -E "^[ ]*${#rules[@]} " | sed -e "s/^[ ]*${#rules[@]} //"`
	list+="\n"

done

#print the final list
echo -e "${list}" | sed '/^$/d' | tr -d ' ' | sort

