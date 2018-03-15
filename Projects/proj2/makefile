EXE = $(patsubst %.cpp,%,$(wildcard p2*.cpp)) $(patsubst %.cpp,%,$(wildcard test*.cpp))
CXXFLAGS = -Wall -g
SOURCES = $(filter-out $(patsubst %, %.cpp,$(EXE)),$(wildcard *.cpp))
SOURCES2 = $(SOURCES:.cpp=)
OBJS = $(SOURCES:.cpp=.o)
DEPS = $(wildcard *.h)


initialize: $(OBJS) p2testXX

all: $(EXE) run

build: $(EXE)

c: clean all

echo:
	echo $(EXE)
	echo $(SOURCES)
	echo $(SOURCES2)
	echo $(OBJS)
	echo $(DEPS)
	
	
# $(EXE): $(OBJS)
	# $(CXX) $(OBJS) -o $(EXE)
	
	

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 
	

%: %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $< -o $@

clean:
	rm -f $(EXE) $(OBJS) $(wildcard *.stackdump) $(SOURCES:.cpp=.exe) $(wildcard *.exe)
	# rm *.o*
	
	# rm *~ 

	
run(%): %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $< -o $%
	./$% < input.txt > output.txt
	
gdb(%): %.cpp $(OBJS) run(%)
	# $(CXX) $(CXXFLAGS) $(OBJS) $< -o $%
	# ./$% < input.txt 
	./$@.bat $% 

	
run:
	./$(EXE)


	
depend: .depend

.depend: $(DEPS)
	rm -f ./.depend
	$(CC) $(CXXFLAGS) -MM $^ > ./.depend;
	
include .depend


