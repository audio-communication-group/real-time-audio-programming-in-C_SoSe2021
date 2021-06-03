# Makefile to build class 'stp_gain' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name

# add folder shortcut examples:
# INCLUDES = -I../includes
# TESTING = testing

lib.name = rtap_biquad

# input source file (class name == source file basename)
class.sources = rtap_biquad~.c
rtap_biquad~.class.sources = vas_iir_biquad.c
rtap_biquad~.class.sources += vas_mem.c
# all extra files to be included in binary distribution of the library
datafiles = cicerospeech.wav

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=pd-lib-builder/

CC += $(INCLUDES)
# CC +=  -mavx -DVAS_USE_AVX

include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder




