
SUBDIRS = 
SUBMAKES = Makefile.socket Makefile.thread Makefile.client Makefile.server


.PHONY:all
all:$(SUBDIRS)

ifneq "$(SUBDIRS)" ""
	(for i in ${SUBDIRS}; do (cd $$i; pwd; ${MAKE} $@); done)
endif
ifneq "$(SUBMAKES)" ""
	for i in ${SUBMAKES};\
		do (${MAKE} -f $$i $@;)\
	done
endif

.PHONY:clean
clean:$(SUBDIRS)

ifneq "$(SUBDIRS)" ""
	(for i in ${SUBDIRS}; do (cd $$i; pwd; ${MAKE} $@); done)
endif
ifneq "$(SUBMAKES)" ""
	for i in ${SUBMAKES};\
		do (${MAKE} -f $$i $@;)\
	done
endif