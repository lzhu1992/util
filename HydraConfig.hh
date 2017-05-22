#Config file for both CSP and H.Y.D.R.A.

#ifndef HYDRACONFIG_HH_
#define HYDRACONFIG_HH_

#include <iostream> //only kept for debugging purposes
#include <fstream>
#include "config.hh"
//regex included in config.hh
using namespace std;

/*default heights and lengths, need max and min distances
VECTOR VARIABLES
 rail  //this will be represented as a vector (including boundaries perhaps)
 arm   //this will be represented as a vector (including boundaries perhaps)

SHAPE VARIABLES
 shape(s)Desired //maybe this should become an array of polyhedrons
 boundsConstraint
 circularConstraint
 Constraints
 
//THIS IS ONLY EXAMPLE --> std::regex_search(insert subject string, insert regex expression);
//using regex we want to find vector text
*/

class hydraConf {
private:
  string fileName;
  std::regex vector("(\[\d+(.\d*),\d+(.\d*),\d+(.\d*)\])");  //this reads vector in form of [double,double,double]
  std::regex command(""); //TODO: must find a way to capture a whole command line (# command command command)

  
public:
  hydraConf(string file) : fileName(file){}
  
  void loadConfig() {
    ifstream inp(fileName);     //opening stream to read file
    string line;                //for each line in the file
    std::smatch match;          //letting system know that we are looking for string objects
    while (getline(inp, line)) {
      //checking for vector quantity
      if (std::regex_search(line, match, vector)) {
        //TODO: make this do something if we come across a vector
      }
      //checking for commands ("#")
      else if (std::regex_search(line, match, command)){
        continue;
      }
      //TODO: more things to find inside of a given file
    } //end loop
  }
};

hydraConf config();

int main(){
  //TODO: configuring
}

#endif
