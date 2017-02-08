#define compile option

###############################################################
#                                                             #
#                                                             #
#            this part need user modify                       #
#                                                             #
###############################################################
# sub dirs
SUBDIRS = base

.PHONY: all
all:$(SUBDIRS)
## 
ifneq "$(SUBDIRS)" ""
	(for i in ${SUBDIRS}; do (cd $$i; pwd; ${MAKE} $@); done)
endif