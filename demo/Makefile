# Makefile 

# The top level directory
TOPDIR := $(shell pwd)
# The source directory locations
IDL_DIR=$(TOPDIR)/idl
CPP_DIR=$(TOPDIR)
CPP_LIB_DIR=$(TOPDIR)/lib
temperature_LIB=$(TOPDIR)/../lib

# The C/C++ compilers to use
#CPP=/usr/bin/g++ 
CPP=/usr/bin/g++
IDLPP= idlpp

# The C/C++ compiler flags
CPPFLAGS= -Wl,-allow-multiple-definition -g -Wall -I/opt/mongo-cxx-driver-v1.8/mongo/client -I$(OSPL_HOME)/include/dcps/C++/SACPP -I$(OSPL_HOME)/include -I$(OSPL_HOME)/include/sys -I$(CPP_LIB_DIR)
LDFLAGS= -L/opt/mongo-cxx-driver-v1.8 -L/lib64 -L$(OSPL_HOME)/lib -L/usr/lib -Wl,-rpath,$(OSPL_HOME)/lib -Wl,-allow-multiple-definition
LIBS=  -lboost_thread -lboost_program_options -lboost_system -ldcpsgapi -ldcpssacpp -lddsdatabase -lddsos  /lib/libsimpledds.a /lib/libtemperature.a /lib/liblogger.a
#LIBS=  -lboost_thread -lboost_program_options -lboost_system -ldcpsgapi -ldcpssacpp -lddsdatabase -lddsos  /lib/libtemperature.a

# Boost Libraries is used by the  publisher/generator examples
#BOOST_LIBS= -lboost_thread -lboost_program_options -lboost_system

# The target programs to build
TARGETS= \
	$(CPP_DIR)/bin/temperature-pub \
	$(CPP_DIR)/bin/temperature-echo \
	$(CPP_DIR)/bin/temperature-alarm \
	$(CPP_DIR)/bin/temperature-persist



all: $(TARGETS)

clean: 
	rm -f $(TOPDIR)/bin/*; \
	rm -f $(TOPDIR)/src/*.o;


# Compile the temperaturePublish binary
$(CPP_DIR)/bin/temperature-pub:
	cd $(CPP_DIR)/src; \
	$(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/temperature-pub.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -o $(TOPDIR)/bin/temperature-pub $(CPP_DIR)/src/temperature-pub.o /lib/libtemperature.a $(temperature_LIB)/gen/temperature/libtemperature.a $(LIBS);

# Compile the temperaturePublish binary
$(CPP_DIR)/bin/temperature-echo:
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/temperature-echo.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -o $(TOPDIR)/bin/temperature-echo $(CPP_DIR)/src/temperature-echo.o /lib/libtemperature.a $(temperature_LIB)/gen/temperature/libtemperature.a $(LIBS);

# Compile the temperaturePublish binary
$(CPP_DIR)/bin/temperature-alarm:
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/temperature-alarm.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -o $(TOPDIR)/bin/temperature-alarm $(CPP_DIR)/src/temperature-alarm.o /lib/libtemperature.a $(temperature_LIB)/gen/temperature/libtemperature.a $(LIBS);

# Compile the temperaturePublish binary
$(CPP_DIR)/bin/temperature-persist:
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -c $(CPP_DIR)/src/temperature-persist.cpp; \
        $(CPP) $(LDFLAGS) $(LIBS) $(BOOST_LIBS)  -llog4cpp -lmongoclient -o $(TOPDIR)/bin/temperature-persist $(CPP_DIR)/src/temperature-persist.o /lib/libtemperature.a $(temperature_LIB)/gen/temperature/libtemperature.a $(LIBS);
 
