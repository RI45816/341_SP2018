if [ -f ./$1.exe ]; then
	make clean $1 && valgrind -v --track-origins=yes --leak-check=full ./$1 < input.txt
else
	make $1 && valgrind -v --track-origins=yes --leak-check=full ./$1 < input.txt
	
fi
