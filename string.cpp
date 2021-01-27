#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h"

using namespace std;




String::String(): data(NULL),length(0){}

String::String(const String &str){      
    
    length=str.length; 
	if (length==0){
        data = NULL;
        return;
    }

    data=new char[length+1];                 
    strcpy(data,str.data);
};

String::String(const char *str){
   
    if (!str){
        length = 0;
        data = NULL;
        return;
    }

    length=strlen(str);      
    data=new char[length+1];
    strcpy(data,str);

};

String::~String(){
    delete[] data;       
};



String& String::operator=(const String &rhs){
    
    length=rhs.length;   
    delete[] data;
    data= new char[length+1];                
    strcpy(data,rhs.data);
    return *this;
}

String& String::operator=(const char *str){
     
    length=strlen(str);
    delete[] data;
    data= new char[length+1];
    strcpy(data,str);
    return *this;
}



bool String::equals(const String &rhs) const{

    if(length!=rhs.length){
       return false;
    }
    
    if(strcmp(data,rhs.data)){
        return false;
    }

    return true;
    
}

bool String::equals(const char *rhs) const{
    
    size_t len_rhs=strlen(rhs);
	if (rhs==NULL){
        return false;
    }
    
    
    if(length!=len_rhs){
        return false;
    }
    if(strcmp(data,rhs)){
        return false;
    }

    return true;

}


void String::split(const char *delimiters, String **output, size_t *size) const{
   
    *size=1;
    size_t delim_len=strlen(delimiters);
    
    size_t i, delim;
    char copy[length + 1] = {0};
    strcpy(copy, data);
    
    for(i=0; i<length; i++){
        for(delim=0;delim<delim_len;delim++){
            if(data[i]==delimiters[delim]){
                (*size)++;
                copy[i]='\0';
            }
        }

    }

    *output= new String[(*size)]; 

    int begin=0;
    int sub_len;
    for(i=0; i<(*size); i++){
            
    	sub_len=strlen(&copy[begin]);
    	(*output)[i]=String(&copy[begin]);
        begin=begin+sub_len+1;
            
    }

    return;

}

int String::to_integer() const{
     
    
    String* parts = NULL;
    size_t size = 0, i = 0;

//specificly made for ip address
    split(".", &parts, &size);
    int val = 0;

    if(size==SEGMENTS){
        for(i = 0; i < size; i++){
            int byte = parts[i].trim().to_integer();
            if ( (byte > 255) || (byte<0) ){
                delete[] parts;
                return 0;
            }           
//this is the bitwise "or"ing that will give us the proper value
            val |= byte << (24-(8 * i));
        }

        delete[] parts;
        return val;
    }else { 
        val = atoi(data);
        if(val!=0){
            delete[] parts;
            return val;
        }
    }

    delete[] parts;
    
    return 0;
}


String String::trim() const{

    int end=length;
    int begin=0;
    
    while(data[begin]==' '){
        begin++;
    }
    while((data[end-1]==' ')&&(begin!=(end-1))){      
        end--;
    }

    if (begin >= end){
        return String();
    }

    int lentemp=(end-begin);
    char temp[lentemp+1];


    strncpy(temp, &data[begin], lentemp);  
    temp[lentemp] = '\0';

    return String(temp);
  
}


