TARGET	 = libLattice.so
PLUGIN   = libAction.so

CXX	 = g++
CXXFLAGS = -c -O3 -Wall -fPIC $(shell root-config --cflags)

LD	 = g++
LDFLAGS	 = -O3 -shared

SRCFILES = $(wildcard src/*.cc)
HDRFILES = $(patsubst src/%.cc,src/%.h,$(SRCFILES))
ALLSOURCES = $(SRCFILES)
ALLOBJECTS = $(patsubst src/%.cc,obj/%.o,$(ALLSOURCES))

PLUGINSRC = $(wildcard actions/*.cc)
PLUGINOBJ = $(patsubst actions/%.cc,obj/actions/%.o,$(PLUGINSRC))

INC = -I. -I$(shell root-config --incdir)
LIBS = $(shell root-config --libs)

all: $(TARGET) $(PLUGIN)

$(TARGET): $(ALLOBJECTS) obj/Dict.o
	$(LD) $(LDFLAGS) -o $@ $(LIBS) $^

$(PLUGIN): $(PLUGINOBJ)
	$(LD) $(LDFLAGS) -o $@ $(LIBS) $^

obj/Dict.o: src/Dict.cpp src/Dict.h
	-@mkdir -p obj 2> /dev/null
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $< $(LIBS)

obj/Main.o: src/Main.cc
	-@mkdir -p obj 2> /dev/null
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $< $(LIBS)

obj/%.o: src/%.cc $(HDRFILES)
	-@mkdir -p obj 2> /dev/null
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $< $(LIBS)

obj/actions/%.o: actions/%.cc
	-@mkdir -p obj/actions 2> /dev/null
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $< $(LIBS)

src/Dict.cpp: $(HDRFILES) src/LinkDef.h
	rootcint -f $@ -c $(INC) $^

clean:
	-@rm -f src/Dict.* obj/* obj/actions/* lib*.so 2> /dev/null
