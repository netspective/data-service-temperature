# Makefile 

# The top level directory
TOPDIR := $(shell pwd)

# The source directory locations
IDL_DIR=$(TOPDIR)/idl
CPP_DIR=$(TOPDIR)
CPP_LIB_DIR=$(TOPDIR)/lib

ifeq ($(strip $(PREFIX)),)

        TARGET_PATH=$(TOPDIR)
else
        TARGET_PATH=$(PREFIX)
endif


# The C/C++ compilers to use
#CPP=/usr/bin/g++ 
CPP=/usr/bin/g++
IDLPP= idlpp

# The C/C++ compiler flags
CPPFLAGS= -g -Wall -I/opt/mongo-cxx-driver-v1.8/mongo/client -I$(OSPL_HOME)/include/dcps/C++/SACPP -I$(OSPL_HOME)/include -I$(OSPL_HOME)/include/sys -I$(CPP_LIB_DIR)
LDFLAGS= -L/opt/mongo-cxx-driver-v1.8 -L/lib64 -L$(OSPL_HOME)/lib -L/usr/lib -Wl,-rpath,$(OSPL_HOME)/lib
LIBS= -ldcpsgapi -ldcpssacpp -lddsdatabase -lddsos  -lsimpledds

# Boost Libraries is used by the  publisher/generator examples
BOOST_LIBS= -lboost_thread -lboost_program_options -lboost_system

# The target programs to build
TARGETS= \
	$(CPP_DIR)/bin/temperature-pub \
	$(CPP_DIR)/bin/temperature-sub-echo \
	$(CPP_DIR)/bin/temperature-sub-alarm \
	$(CPP_DIR)/bin/temperature-sub-persist \
	$(CPP_DIR)/bin/lib

INSTALL_TARGETS= \
	temperature_install



# Build all targets
all: check_idlpp $(TARGETS)

install: $(INSTALL_TARGETS)

# Clean all files, including C++ generated from IDL
clean:
	rm -f /lib//libtemperature.so;  \
	rm -f /usr/include/temperature.h;  \
	rm -f /usr/include/Functions.h;  \
	rm -f $(CPP_DIR)/lib/gen/temperature/*;  \
	rm -f $(CPP_DIR)/*.a;  \
	rm -f $(CPP_DIR)/src/*.o;  \
	rm -f $(CPP_DIR)/lib/*.o; \
	rm -f $(TOPDIR)/bin/*
	rm -f $(TARGETS)

# Check that the idlpp compiler is in the current path
check_idlpp:
	@$(IDLPP) | grep Usage > /dev/null;


# Generate the temperature C++ source files from the IDL
$(CPP_DIR)/lib/gen/temperature/temperature.h:
	mkdir -p $(CPP_DIR)/lib/gen/temperature; \
	cd ${IDL_DIR}; $(IDLPP) -S -l cpp -d $(CPP_DIR)/lib/gen/temperature temperature.idl; 

# Compile the temperature IDL-generated C++ files into libtemperature.a
$(CPP_DIR)/lib/gen/temperature/libtemperature.a: $(CPP_DIR)/lib/gen/temperature/temperature.h
	cd $(CPP_DIR)/lib/gen/temperature; \
	$(CPP) $(CPPFLAGS) -c temperature.cpp; \
        $(CPP) $(CPPFLAGS) -c temperatureDcps.cpp; \
        $(CPP) $(CPPFLAGS) -c temperatureDcps_impl.cpp; \
        $(CPP) $(CPPFLAGS) -c temperatureSplDcps.cpp; \
        ar cr libtemperature.a temperature.o temperatureDcps.o temperatureDcps_impl.o temperatureSplDcps.o; \
        ranlib libtemperature.a

# Compile the Functions helper class
Functions.o: $(CPP_LIB_DIR)/Functions.cpp
	$(CPP) $(CPPFLAGS) -c $(CPP_LIB_DIR)/Functions.cpp


# Compile the temperaturePublish binary
$(CPP_DIR)/bin/temperature-pub: $(CPP_DIR)/lib/gen/temperature/libtemperature.a $(CPP_LIB_DIR)/Functions.o
	cd $(CPP_DIR)/src; \
	$(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/temperature -c $(CPP_DIR)/src/temperature-pub.cpp -o  $(CPP_DIR)/src/temperature-pub.o $(LDFLAGS) $(LIBS); 

# Compile the temperatureSubscribe binary
$(CPP_DIR)/bin/temperature-sub-echo: $(CPP_DIR)/lib/gen/temperature/libtemperature.a $(CPP_LIB_DIR)/Functions.o
	cd $(CPP_DIR)/src; \
	$(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/temperature -c $(CPP_DIR)/src/temperature-echo.cpp -o $(CPP_DIR)/src/temperature-echo.o $(LDFLAGS) $(LIBS);

# Compile the temperatureSubscribe binary
$(CPP_DIR)/bin/temperature-sub-alarm: $(CPP_DIR)/lib/gen/temperature/libtemperature.a $(CPP_LIB_DIR)/Functions.o
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/temperature -c $(CPP_DIR)/src/temperature-alarm.cpp -o $(CPP_DIR)/src/temperature-alarm.o  $(LDFLAGS) $(LIBS); 

# Compile the temperatureSubscribe binary
$(CPP_DIR)/bin/temperature-sub-persist: $(CPP_DIR)/lib/gen/temperature/libtemperature.a $(CPP_LIB_DIR)/Functions.o 
	cd $(CPP_DIR)/src; \
        $(CPP) $(CPPFLAGS) -I$(CPP_DIR)/lib/gen/temperature -c $(CPP_DIR)/src/temperature-persist.cpp -o $(CPP_DIR)/src/temperature-persist.o $(LDFLAGS) $(LIBS);

# Creating Libraries
$(CPP_DIR)/bin/lib:
	cd $(CPP_DIR)/src; \
	ar cr $(CPP_DIR)/libtemperature.a $(CPP_DIR)/src/temperature-pub.o $(CPP_LIB_DIR)/Functions.o $(CPP_DIR)/lib/gen/temperature/libtemperature.a \
	$(CPP_DIR)/src/temperature-echo.o $(CPP_DIR)/src/temperature-alarm.o $(CPP_DIR)/src/temperature-persist.o; \
        ranlib $(CPP_DIR)/libtemperature.a; 
	
temperature_install:
	mkdir -p $(TARGET_PATH)/lib; \
        mkdir -p $(TARGET_PATH)/include; \
	cp $(CPP_DIR)/libtemperature.a $(TARGET_PATH)/lib; \
	cp $(CPP_DIR)/libtemperature.a /lib; \
        cp $(CPP_DIR)/lib/temperature.h $(TARGET_PATH)/include; \
        cp $(CPP_DIR)/lib/temperature.h /usr/include; \
        cp $(CPP_DIR)/lib/Functions.h /usr/include;

