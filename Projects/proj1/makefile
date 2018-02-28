EXE = $${PWD\#\#*/}
CXXFLAGS = -Wall -g
SOURCES = $(wildcard S*.cpp)
SOURCES2 = $(SOURCES:.cpp=)
OBJS = $(SOURCES:.cpp=.o)
DEPS = $(wildcard *.h)

# all: $(EXE) run

build: $(OBJS)

# c: clean all

echo:
	echo $(Folder)
	
$(EXE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXE)
	
	

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 
	
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXE) $(OBJS) $(wildcard *.stackdump) $(SOURCES:.cpp=.exe) $(wildcard *.exe) $(wildcard *.out)
	# rm *.o*
	# rm *~ 

	


run:
	./$(EXE)

run01:
	g++ -g p1test01.cpp SSLColumn.cpp; g++ p1test01.cpp SSLColumn.cpp -o t01.out; ./t01.out
run02:
	g++ -g p1test02.cpp SSLColumn.cpp; g++ p1test02.cpp SSLColumn.cpp -o t02.out; ./t02.out
run03:
	g++ -g p1test03.cpp SSLColumn.cpp; g++ p1test03.cpp SSLColumn.cpp -o t03.out; ./t03.out

run04:	
run05:	
	echo
	
run06:
	g++ -g p1test06.cpp SSLColumn.cpp SortedSquareList.cpp; g++ p1test06.cpp SSLColumn.cpp SortedSquareList.cpp -o t06.out; ./t06.out
run07:
	g++ -g p1test07.cpp SSLColumn.cpp SortedSquareList.cpp; g++ p1test07.cpp SSLColumn.cpp SortedSquareList.cpp -o t07.out; ./t07.out
run08:
	g++ -g p1test08.cpp SSLColumn.cpp SortedSquareList.cpp; g++ p1test08.cpp SSLColumn.cpp SortedSquareList.cpp -o t08.out; ./t08.out
run09:
	g++ -g p1test09.cpp SSLColumn.cpp SortedSquareList.cpp; g++ p1test09.cpp SSLColumn.cpp SortedSquareList.cpp -o t09.out; ./t09.out
runXX:
	g++ -g p1testXX.cpp SSLColumn.cpp SortedSquareList.cpp
	# g++ p1testXX.cpp SSLColumn.cpp SortedSquareList.cpp -o tXX.out; ./tXX.out < input.txt
	
depend: .depend

.depend: $(DEPS)
	rm -f ./.depend
	$(CC) $(CXXFLAGS) -MM $^ > ./.depend;
	
include .depend


