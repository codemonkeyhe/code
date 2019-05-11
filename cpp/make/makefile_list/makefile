name1 := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
$(warning $(MAKEFILE_LIST))
include inc.mk
name2 := $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
$(warning $(MAKEFILE_LIST))

all:
	@echo name1 = $(name1)
	@echo name2 = $(name2)
