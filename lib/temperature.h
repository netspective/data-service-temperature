#ifndef __TEMPERATURE_H_
#define __TEMPERATURE_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <OpenSpliceDataService.h>

#include "Functions.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <ctime> 
#include <boost/program_options.hpp>

/*Log4cpp Library*/
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Configurator.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/SimpleLayout.hh>


using namespace std;

int publishTemperature(string deviceid,string domainid,string loginfo,string logdata,string logconfpath);
int echoSubscribeTemperature(string deviceid,string domainid,string loginfo,string logdata,string logconfpath);
int alarmSubscribeTemperature(string  domainid,string deviceid,string loginfo,string logdata,string logconfpath,int avgTemp,int maxTemp,int minTemp);
int persistSubscribeTemperature(string domainid,string deviceid,string loginfo,string logdata,string logconfpath,string host,string database);
#endif


