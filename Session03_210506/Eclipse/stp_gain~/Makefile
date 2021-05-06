# Makefile to build class 'pan~' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

#C:\Program Files (x86)\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0#C:\Program Files (x86)\mingw-w64\i686-7.3.0-posix-dwarf-rt_v5-rev0\mingw32\bin

# library name
lib.name = externals.howto.stp_gain

# input source file (class name == source file basename)
class.sources = stp_gain~.c

# all extra files to be included in binary distribution of the library
datafiles =

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
