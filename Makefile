#Makefile at top of application tree
TOP = .
include $(TOP)/configure/CONFIG
DIRS := $(DIRS) $(filter-out $(DIRS), configure)
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *App))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard iocBoot))

define DIR_template
 $(1)_DEPEND_DIRS = configure
endef
$(foreach dir, $(filter-out configure,$(DIRS)),$(eval $(call DIR_template,$(dir))))

iocBoot_DEPEND_DIRS += $(filter %App,$(DIRS))

# Comment out the following lines to disable creation of example iocs and documentation
#DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard etc))

#ifeq ($(wildcard etc),etc)
#	include $(TOP)/etc/makeIocs/Makefile.iocs
#	UNINSTALL_DIRS += documentation/doxygen $(IOC_DIRS)
#endif

# Comment out the following line to disable building of example iocs
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard iocs))
iocs_DEPEND_DIRS += $(filter %App,$(DIRS))

TEST_RUNNER = $(TOP)/pr4000App/src/O.$(EPICS_HOST_ARCH)/runner

include $(TOP)/configure/RULES_TOP

.PHONY: test
test:
ifneq ($(wildcard $(TEST_RUNNER)*),)
	$(TEST_RUNNER) --gtest_output=xml:$(TOP)/test-reports/TEST-PR4000.xml
endif

