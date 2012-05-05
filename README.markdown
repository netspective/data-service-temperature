# Temperature Library

Temperature library is intended to greatly simplify the use of Temperature device simulation with DDS. As such, Temperature library have functions that reduces by several times the line of code that need to be written for a creating Temperature Simulation DDS application. 

# Compilation and Installation
Clone the library from the github

	git clone git@github.com:netspective/data-service-temperature.git
	
	cd data-service-temperature

Compiling
	
	make

Installing
	
	make install 

	or 

	make install PREFIX=<installation path>



## Simplified Functions
Following are Temperature functions and their descriptions

Note: Refer the demo programs for reference

#### Running Publisher 

SYNOPSIS

	int publishTemperature(string deviceid,string domainid,string loginfo,string logdata,string logconfpath);

DESCRIPTION

	The publish function used to publish the Blood Pressure data in the DDS. 

ARGUMENTS

	domain             Device Domain 

	device-id          Device ID - for device identification

	log-info           Log information category

	lod-data           Log data file 

	log4cpp-conf       Log configuration and format specification file


#### Echo Subscribers

SYNOPSIS

	int echoSubscribeTemperature(string deviceid,string domainid,string loginfo,string logdata,string logconfpath);

DESCRIPTION

This function is used to subscribe and join the Temperature topic. Log4cpp config is used to maintain the logs and thier path.
 
ARGUMENTS

	domain             Device Domain 

	device-id          Device ID - for device identification

	log-info           Log information category

	lod-data           Log data file 

	log4cpp-conf       Log configuration and format specification file


#### Alarm Subscriber

SYNOPSIS

	int alarmSubscribeTemperature(string  domainid,string deviceid,int maxTemp,int minTemp,int avgTemp,string loginfo,string logdata,string logconfpath);


DESCRIPTION

This function is used to subscribe and join the Temperature topic with alarm notification. Log4cpp config is used to maintain the logs and thier path.

 
ARGUMENTS


	help                  Produce help message

	domain arg            Device Domain

	device-id arg         Device ID for identification

	log-info arg          Log information category

	log-data arg          Log data category 

	log4cpp-conf arg      Log configuration and format specification file

	avg-time-period arg   Average time period for temperature - default 1 min

	temp-low arg          Temperature low level alarm  specification -default<88

	temp-high arg         Temperature high level alarm specification-default>92


#### Persistance Subscriber

SYNOPSIS

	int persistSubscribeTemperature(string domainid,string deviceid,string loginfo,string logdata,string logconfpath,string host,string database);

DESCRIPTION

This function is used to subscribe and join the Temperature topic and store the output in the MongoDB database notification. Log4cpp config is used to maintain the logs and thier path.
 
ARGUMENTS

	domain           Device Domain

	device-id        Device ID for identification

	host             Host Ip_Address

	database         Database Name

	log-info         Log information category

	log-data         Log data category

	log4cpp-conf     Log configuration and format specification file
