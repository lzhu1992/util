# Config file for CSP

#ifndef CONFIGCSP_HH_
#define CONFIGCSP_HH_

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

enum prot = { "csp", "https", "http"}; //only protocols we'll use
enum ip = {"ipV4", "ipV6"}; //only IP versions we'll use at the moment

class csp{
public:
	uint16_t port; // Port number to talk/listen on
	prot protocol; // Specifies what protocol we're going to use
	ip ip_ver; // Version if IP we're going to use
	String log; // The name of the log file to be generated
	String base; // this depends on os, base for all directory

	csp(){
		ifstream reader;
		char x[10];
		String line;
		reader.open("csp.conf", ios::in);
		while(!reader.eof()){
			reader>>x;
			//split x into words
			if(strcmp(x, "PORT"))
				port = uint16_t(x[1]);
			else if(strcmp(x,"LOG"))
				log = x[1];
		}
	}
};

#endif