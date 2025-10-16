PROGRAMA = p06_automata_simulator
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SOURCES = cya_p06.cc automata.cc estado.cc
OBJECTS = $(SOURCES:.cc=.o)

all: $(PROGRAMA)

$(PROGRAMA): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAMA) $(OBJECTS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) 