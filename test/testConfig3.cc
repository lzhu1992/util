#include "Config.hh"

int main() {
	Config::Type machinePart =
		Config::define(Config::STRING, "name",
									 Config::STRING, "varname",
									 Config::Vec3D,  "start",
									 Config::Vec3D,  "end");
	// TODO: How to handle variable numbers and configs with both primitives and define?
	Config c("machine.conf",
					 "part1", machinePart,
					 "part2", machinePart);

}
