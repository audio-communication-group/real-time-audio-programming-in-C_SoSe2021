# Makefile to build class 'rtap_osc6delay' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name

# add folder shortcut examples:
# INCLUDES = -I../includes
# TESTING = testing

lib.name = rtap_osc6_delay~

# input source file (class name == source file basename)
class.sources = rtap_osc6_delay~.c
rtap_osc6_delay~.class.sources = vas_delay.c
rtap_osc6_delay~.class.sources += vas_osc.c
rtap_osc6_delay~.class.sources += vas_mem.c
# all extra files to be included in binary distribution of the library
datafiles = 

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=pd-lib-builder/

CC += $(INCLUDES)
# CC +=  -mavx -DVAS_USE_AVX

include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder




