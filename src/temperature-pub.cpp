#include <temperature.h>
#include "ccpp_temperature.h""
#define devid "deviceID"

using namespace DDS;
using namespace std;
namespace po = boost::program_options;
using namespace com::netspective::medigy;

char buf[BUFFERSIZE], c;
stringstream prtemp;
char* tempRandomData()
{

        char send_data[1024],temp[1024];
        int sys;

        strcpy(send_data,"");
        strcpy(temp,"");

        sprintf(temp, "%d", time(0));
        strcat(send_data,temp);
        sys = rand()%30+95;
        sprintf(temp, "%d", sys);
        strcat(send_data,":");
        strcat(send_data,temp);
	sleep(1);
	return send_data;


}

int publishTemperature(string deviceid,string domainid,string loginfo,string logdata,string logconfpath)
{

	/*Initializing SimpleDDS library*/
	DataService *simpledds;
	TemperatureTypeSupport_var typesupport;
	DataWriter_ptr writer;
	TemperatureDataWriter_var bpWriter;

        /*Setting QoS Properties for Topic*/
	DDS::TopicQos tQos;
	getQos(tQos);

	simpledds = new OpenSpliceDataService(tQos,loginfo,logconfpath);
	typesupport = new TemperatureTypeSupport();
	writer = simpledds->publish(typesupport);
	bpWriter = TemperatureDataWriter::_narrow(writer);


	simpledds->logger->info("Temperature Publisher Started %s",deviceid.c_str());	

	Temperature data;
	
	/*Storing Domain and Device ID*/
	data.deviceID = DDS::string_dup(deviceid.c_str());
	data.deviceDomain = DDS::string_dup(domainid.c_str());
	simpledds->logger->info("Temperature Started Publishing Data In DDS");
        simpledds->logger->info("Format: TIMEOFMEASURED, TEMPERATURE");
	
	while (1) 
	{
		
			strcpy(buf,tempRandomData());
			char * pch;
			pch = strtok (buf,":");
			data.timeOfMeasurement = atol(pch);
			prtemp<<data.timeOfMeasurement<<COMMA;
			pch = strtok (NULL, ":");
			data.temp = (short)atoi(pch);
			prtemp<<data.temp;
			simpledds->logger->info(prtemp.str().c_str());
			bpWriter->write(data, NULL);
			prtemp.str(CLEAN);
		
	}

	/*Deleting SimpleDDS Instance*/
	simpledds->logger->info(" Temperature Publisher Ends %s ",deviceid.c_str());
	simpledds->deleteWriter(writer);
	delete simpledds;
	return 0;
}
