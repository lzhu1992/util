/** Config file for both CSP and H.Y.D.R.A. **/

/**
Config will have a class and the parameters passed to it each time.
It will check if they are the same as specified, and print error messages accordingly.
*/

//ToDo: How do I pass variable length vaiables if this a generic config?

#ifndef CONFIG_HH_
#define CONFIG_HH_

#include <iostream>
#include <regex>

/**
PSEUDO CODE
template t1
HashMap<String, t1> map1
Read_file(file):
	map[key]=value
if  else (proj_name):
	if(!check_correct_projNAME(map1)):
		print "config file not good"
		exit 1
*/

class buff_size{ //To be able to access the buffer size and multiplier easily.
public:
	int size; //Size of the buffer
	char mul; //Multiplier, M for mega, m for milli, k for kilo etc
	buff(int x, char a){
		size = x; mul = a;
	}
};

//ToDo: Write a function to take out the comments from the strings, to take care of any comments

/** 
RegEx search expression is #(\s|[a-zA-z0-9]*)*\n
This means # followed by space(s) followed by character(s) and finally a new line.
Need to think if newline is really required.
*/

//ToDo: Function to take out the white spaces from the names

using namespace std;

#endif


/**
Proposed changes

config will include configCSP and configHYDRA

a hashmap of parameters will be send to config, along with the project name.

Depending on the project name, the function will check if the config is correct or incorrect, form configCSP or configHYDRA
*/