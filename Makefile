## makefile for the fake rate framework

GIT_VERSION = $(shell git describe --abbrev=4 --dirty --always)

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs) -lRooFitCore -lRooFit
ROOTGLIBS   = $(shell root-config --glibs)
#ROOTINCDIR  = $(shell root-config --incdir)

LIBS        = $(ROOTLIBS)
INCLUDES    = -I. $(ROOTCFLAGS)
# this is a roofit version somewhere: -I/swshare/cms/slc5_amd64_gcc462/lcg/roofit/5.32.03-cms16/include/

CXX         = g++ -g -fPIC -fno-var-tracking -Wno-deprecated -D_GNU_SOURCE -O2
CXXFLAGS    = $(INCLUDES)


SRCSA       = src/main/Base.cc src/main/Dileptons.cc src/main/AnalysisModules.cc src/main/Sketches.cc \
              src/helper/AnalysisTools.cc src/helper/DataSample.cc src/helper/Histogram.cc src/helper/H1D.cc src/helper/H2D.cc src/helper/OtherInput.cc src/helper/OtherOutput.cc src/helper/Tools.cc src/helper/Verbose.cc
OBJSA       = $(patsubst %.C,%.o,$(SRCSA:.cc=.o))

includes    = $(wildcard src/head/*.hh)

.SUFFIXES: .cc,.C,.hh,.h
.PHONY : clean depend git-version


# Rules ====================================

Dileptons: src/exe/Dileptons.C $(OBJSA)
	$(CXX) $(INCLUDES) $(LIBS) -ldl -o $@ $^

depend: .depend

depend: 
	rm -f ./.depend
	$(foreach SRC,$(SRCSA),$(CXX) -I. -I$(shell root-config --incdir) -MG -MM -MT $(patsubst %.C,%.o,$(SRC:.cc=.o)) $(SRC) >> ./.depend;)

clean:
	find src -name '*.o' -exec $(RM) -v {} ';' 
	$(RM) .depend
	$(RM) Dileptons

git-version:
	@printf "#\n# Current Git Version is $(GIT_VERSION)\m#\n"

-include .depend
