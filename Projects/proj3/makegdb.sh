if [ -f ./$1.exe ]; then
	make clean $1 && valgrind --track-origins=yes --leak-check=full ./$1
else
	make $1 && valgrind --track-origins=yes --leak-check=full ./$1
	
fi
