TOP=../..

include $(TOP)/configure/CONFIG

LIBRARY_IOC += pr4000

# xxxRecord.dbd will be installed into <top>/dbd
DBD += pr4000.dbd

# The following are compiled and added to the support library
pr4000_SRCS += pr4000Main.cpp

# pr4000.dbd will be created from these files
pr4000_DBD += $(EPICS_BASE_IOC_LIBS)
pr4000_DBD += asyn utilities
pr4000_DBD += asubFunctions

# We need to link this IOC Application against the EPICS Base libraries
pr4000_LIBS += $(EPICS_BASE_IOC_LIBS)

pr4000_SRCS += units.c

# googleTest Runner
ifeq ($(findstring 10.0,$(VCVERSION)),)

TESTPROD_HOST += runner
USR_CPPFLAGS += -I$(GTEST)/googletest/include
runner_SRCS += units.c units_tests.cpp run_all_tests.cc
runner_LIBS += gtest
runner_LIBS += $(EPICS_BASE_IOC_LIBS)

endif

include $(TOP)/configure/RULES
