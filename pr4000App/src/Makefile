TOP=../..

include $(TOP)/configure/CONFIG

# -------------------------------
# Build an Diamond Support Module
# -------------------------------

PROD_IOC += pr4000

# xxxRecord.dbd will be installed into <top>/dbd
DBD += pr4000.dbd

# The following are compiled and added to the support library
pr4000_SRCS += pr4000Main.cpp

# pr4000.dbd will be created from these files
pr4000_DBD += base.dbd

# We need to link this IOC Application against the EPICS Base libraries
pr4000_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES
