EXE = $${PWD\#\#*/}
CXXFLAGS = -Wall -g
SOURCES = $(wildcard *.cpp)
SOURCES2 = $(SOURCES:.cpp=)
OBJS = $(SOURCES:.cpp=.o)
DEPS = $(wildcard *.h)

all: $(EXE) run

build: $(EXE)

c: clean all

echo:
	echo $(Folder)
	
$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXE)
	
	

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 
	
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXE) $(OBJS) $(wildcard *.stackdump) $(SOURCES:.cpp=.exe) $(wildcard *.exe)
	# rm *.o*
	# rm *~ 

	


run:
	./$(EXE)


	
depend: .depend

.depend: $(DEPS)
	rm -f ./.depend
	$(CC) $(CXXFLAGS) -MM $^ > ./.depend;
	
include .depend

