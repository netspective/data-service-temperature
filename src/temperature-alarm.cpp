#include <temperature.h>
#include "ccpp_temperature.h"
#define devid "deviceID"


using namespace DDS;
using namespace std;
namespace po = boost::program_options;
using namespace com::netspective::medigy;
stringstream temp,prtemp;


int alarmSubscribeTemperature(string domainid,string deviceid,string loginfo,string logdata,string logconfpath,int avgtime,int templow,int temphigh)
{
	 long timestart,timeend=0,avg=0;
	 int nrecord=0;


 	 /*Initializing SimpleDDS library*/
	 DataService *simpledds;
	 TemperatureTypeSupport_var typesupport;
    	 DataReader_ptr content_reader;
    	 TemperatureDataReader_var bpReader;
    	 ReturnCode_t status;
	 int i=0;

	 /*Setting QoS Properties for Topic*/
	 DDS::TopicQos tQos;
	 getQos(tQos);

	 simpledds = new OpenSpliceDataService(tQos,loginfo,logconfpath);
	 typesupport = new TemperatureTypeSupport();
         simpledds->logger->info(" Temperature Alarm Subscriber Started");
	 /*Creating content Filtered Subscriber*/
	 StringSeq sSeqExpr;
         sSeqExpr.length(0);
	 content_reader = simpledds->filteredSubscribe(typesupport, deviceid ,devid , deviceid,sSeqExpr);
    	 bpReader = TemperatureDataReader::_narrow(content_reader);
   	 TemperatureSeq  bpList;
     	 SampleInfoSeq     infoSeq;
	 simpledds->logger->info("Temerature Alarm Subscriber for %s",deviceid.c_str());
	 simpledds->logger->info("Format: DOMAIN, DEVICE_ID, START_TIME, END_TIME, AVERAGE_TEMPERATURE");

	 /*Receiving Data from DDS */
	 while (1) 
	 {
         	status = bpReader->take(
            	bpList,
            	infoSeq,
            	LENGTH_UNLIMITED,
            	ANY_SAMPLE_STATE,
           	ANY_VIEW_STATE,
            	ANY_INSTANCE_STATE);
         	checkStatus(status, "take");
          	if (status == RETCODE_NO_DATA) 
		{
          		continue;
          	}
          	for (i = 0; i < bpList.length(); i++) 
	  	{

			if(infoSeq[i].valid_data)
			{
	
				avg+=(long)bpList[i].temp;
				if(nrecord == 0)
	                        {
	                                timestart=(long)bpList[i].timeOfMeasurement;
	                        }
	                        else
	                        {
					timeend =(long) bpList[i].timeOfMeasurement;
	                                if((timeend - timestart) > (60*avgtime))
	                                {
						avg=avg/nrecord;
						if(avg < templow || avg > temphigh)
						{
							prtemp <<bpList[i].deviceDomain<<COMMA;
							prtemp <<bpList[i].deviceID<<COMMA<<timestart<<COMMA<<timeend<<COMMA<<avg;
			 				simpledds->logger->info(prtemp.str().c_str());
							prtemp.str(CLEAN);
							
						}
						nrecord = -1;
	                               }
	                         }
				
			}


		}
		status = bpReader->return_loan(bpList, infoSeq);
        	checkStatus(status, "return_loan");
		nrecord++;
		
    	}
        /* We're done.  Delete everything */
	simpledds->logger->info("Temperature Alarm Subscriber Ends %s",deviceid.c_str());
        simpledds->deleteReader(content_reader);
        delete simpledds;
        return 0;
}
