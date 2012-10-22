
EXECUTABLE=dsim
DEPS=make.dep
CPPFLAGS=-I. -std=c++0x -g 

SOURCES=\
	agenda.cpp \
	wire.cpp \
	globals.cpp \
	main.cpp

OBJECTS=$(SOURCES:.cpp=.o)

deps : $(SOURCES)
	g++ $(CPPFLAGS) -M $(SOURCES) > $(DEPS)

include $(DEPS)

$(EXECUTABLE) : $(OBJECTS)
	g++ $(CPPFLAGS) -o $@ $(OBJECTS)

clean :
	rm -f $(TARGET) $(OBJECTS) $(DEPS)
