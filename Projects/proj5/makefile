# EXE2 = $${PWD\#\#*/}
TEST = $(patsubst %.cpp,%, $(wildcard *testXX.cpp) Driver.cpp)
EXE = $(patsubst %.cpp, %, $(filter-out $(TEST:=.cpp),$(wildcard p[0-9]*.cpp)))

GDBFLAGS = -O2 -ggdb
CXXFLAGS = -Og -ggdb
# CXXFLAGS = -Wall -g
# SOURCES = $(filter-out $(patsubst %, %.cpp,$(EXE)),$(wildcard *.cpp))
SOURCES = $(filter-out $(EXE:=.cpp) $(TEST:=.cpp),$(wildcard *.cpp))
SOURCES2 = $(SOURCES:.cpp=)
OBJS = $(SOURCES:.cpp=.o)
DEPS = $(wildcard *.h)

initalize: $(OBJS)

test: $(TEST)

testing: $(TEST)
	./$(TEST) < input.txt

all: $(EXE) run

build: $(EXE)

c: clean all

echo:
	echo TEST: $(TEST)
	echo EXE: $(EXE)
	echo SOURCES: $(SOURCES)
	echo SOURCES2: $(SOURCES2)
	echo OBJS: $(OBJS)
	echo DEPS: $(DEPS)

	
$(EXE): %: %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(filter-out $<,$(OBJS:.o=.cpp)) $< -o $@
	
$(TEST): %: %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(filter-out $(patsubst %.cpp,%.o,$<),$(OBJS)) $< -o $@


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 
	


clean:
	rm -f $(EXE) $(TEST) $(OBJS) $(wildcard *.stackdump) $(wildcard *.exe)
	# rm *.o*
	# rm *~ 

run(%): %.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $(filter-out $(patsubst %.cpp,%.o,$<),$(OBJS)) $< -o $%
	./$% < input.txt > output.txt
	
gdb(%): %.cpp $(OBJS) 
	$(CXX) $(CXXFLAGS) $(filter-out $(patsubst %.cpp,%.o,$<),$(OBJS)) $< -o $%
	./$@.bat $% 	

gdb2(%): %.cpp $(OBJS) 
	$(CXX) $(GDBFLAGS) $(filter-out $(patsubst %.cpp,%.o,$<),$(OBJS)) $< -o $%
	./gdb.bat $% 	

diff(%): %.txt run(%)
	bash -c "diff $< output.txt" > diff.txt
	
run:
	./$(EXE)


	
depend: .depend

.depend: $(DEPS)
	rm -f ./.depend
	$(CC) $(CXXFLAGS) -MM $^ > ./.depend;
	
include .depend


