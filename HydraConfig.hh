//Config file Reader for both CSP and H.Y.D.R.A.


#ifndef HYDRACONFIG_HH_
#define HYDRACONFIG_HH_

#include <iostream> //only kept for debugging purposes
#include <fstream>  //already exists in config.hh
#include <regex>    //already exists in config.hh
#include "config.hh"
//regex included in config.hh
using namespace std;

/*------------------------------------------------------------------------------------------------
default heights and lengths, need max and min distances
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

TODO:
  Specify the format of the config file
--------------------------------------------------------------------------------------------------*/

class hydraConf {
private:
  string fileName;
public:
  /*list of variables and data types
  MACHINE SPECS:
    machine units (millimeters, centimeters, etc)
    maximum velocity
    maximum acceleration
    home location
    maximum step rate (in Hertz)
    axis

    double wattage
    double voltage
    Vec3d rail;
    Vec3d arm;
//---------------------------------//
    double max distance of rail
    double min distance of rail
//---------------------------------//
    double max distance of arm1
    double min distance of arm1

    double max depth of drill1
    double min depth of drill1

    double max rotation of drill1
    double min rotation of drill1
//---------------------------------//
    double max distance of arm2
    double min distance of arm2

    double max depth of drill2
    double min depth of drill2

    double max rotation of drill2
    double min rotation of drill2
//---------------------------------//  
  BUILD: (how will shapes and constraints be represented)
    constraint
      bounds
      circle
      cube
    shapes (must differentiate shapes)   
      polyhedron
      plane
      spline
      Bezier
  */

  hydraConf(string file) : fileName(file){}
  void loadConfig() {
    ifstream inp(fileName);     //opening stream to read file
    string line;                //for each line in the file
    std::smatch match;          //letting system know that we are looking for string objects

    regex checkVector("(\[\d+(.\d*),\d+(.\d*),\d+(.\d*)\])"); //this reads vector in form of [double,double,double]
    regex checkCommand("#(\s|[a-zA-z0-9]*)*\n");              //this reads whole command line (# command command command)
    regex checkConstraint(""); //TODO: make an expression that finds the constraint


    while (getline(inp, line)) {
      //checking for vector quantity
      if (std::regex_search(line, match, checkVector)) { //if (regex_match(line, vector)){
        //TODO: make this do something if we come across a vector
        //match.str() //<--returns the matched string

      }
      //checking for commands ("#")
      else if (std::regex_search(line, match, checkCommand)){
        continue;
      }
      //TODO: more things to find inside of a given file
    } //end loop
  }
};

hydraConf config(insert configuration file here); //global variable

int main(){
  //TODO: configuring
}

#endif
