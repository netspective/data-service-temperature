#include <boost/program_options.hpp>
#include <temperature.h>

string _domainid,_deviceid,_loginfo,_logdata,_logconfpath,_hostip;

int main(int argc, char* argv[]) 
{
	if (!parse_args_pub(argc, argv,_domainid,_deviceid,_loginfo,_logdata,_logconfpath))
	return 1;

	publishTemperature(_deviceid,_domainid,_loginfo,_logdata,_logconfpath);
	return 0;
}

