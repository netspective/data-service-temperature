#include <boost/program_options.hpp>
#include <temperature.h>


string _domainid,_deviceid,_loginfo,_logdata,_logconfpath;
int avgTemp,maxTemp,minTemp;

int main(int argc, char* argv[]) 
{
	if (!parse_args_temp_alarm(argc, argv,_domainid,_deviceid,_loginfo,_logdata,_logconfpath,avgTemp,maxTemp,minTemp))
    	return 1;
	
	alarmSubscribeTemperature(_domainid,_deviceid,_loginfo,_logdata,_logconfpath,avgTemp,maxTemp,minTemp);
	return 0;
}

