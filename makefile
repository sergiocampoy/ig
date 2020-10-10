# ##############################################################################
#
# Informática Gráfica (Grado Informática)
# Makefile (sirve para Linux y macOS)
#
# ##############################################################################

# custom pathing
home            := .
include         := $(home)/include
src             := $(home)/src
obj             := $(home)/obj
bin             := $(home)/bin


.SUFFIXES:
.PHONY: x

exe             := $(bin)/pracs_exe # ejecutable
units_cc        := $(wildcard $(src)/*.cc) $(wildcard $(src)/*.cpp) # lista con los .cc/.cpp
units_o         := $(addsuffix .o, $(basename $(units_cc))) # lista con todos los .o
units_o         := $(notdir $(units_o)) # elimina $(src)/
units_o         := $(addprefix $(obj)/, $(units_o)) # añade $(obj)/
headers         := $(wildcard *.h*) # lista con todos los .h
uname           := $(shell uname -s) # Linux o Darwin
en_macos        := $(findstring Darwin,$(uname)) # "" o "Darwin"
en_linux        := $(findstring Linux,$(uname)) # "Linux" o ""
compiler        := $(if $(en_linux), g++, clang++ ) # "g++" o "clang++"
sistoper        := $(if $(en_macos), macOS, Linux ) # "macOS" o "Linux"

cc_flags_common := -std=c++11 -g -I/usr/include -Iinclude
cc_flags_linux  := -DLINUX
cc_flags_macos  := -DMACOS
cc_flags        := $(cc_flags_common) $(if $(en_linux), $(cc_flags_linux), $(cc_flags_macos))

glu_flag_macos  := /System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGLU.dylib
ld_libs_common := -ljpeg
ld_libs_linux  := -lGLEW -lGLU -lglut -lGL
ld_libs_macos  := -framework OpenGL -framework GLUT $(glu_flag_macos)
ld_libs        := $(ld_libs_common) $(if $(en_linux), $(ld_libs_linux), $(ld_libs_macos))


x: $(exe)
	@echo Enlazando para: $(sistoper)
	./$(exe)

test:
	@echo "units_cc = $(units_cc)"
	@echo "units_o = $(units_o)"
	@echo $(en_macos)
	@echo $(sistoper)

$(exe): $(units_o) makefile
	$(compiler) -o $(exe)  $(units_o) $(ld_libs)

$(obj)/%.o : $(src)/%.cc
	$(compiler) -c -o $@ $(cc_flags) $<

$(obj)/%.o : $(src)/%.cpp
	$(compiler) -c -o $@ $(cc_flags) $<

$(units_cc) : $(headers)
	touch $(units_cc)

clean:
	rm -f $(obj)/*.o $(bin)/*_exe
