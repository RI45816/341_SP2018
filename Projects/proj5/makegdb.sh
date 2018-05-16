if [ -f ./$1.exe ]; then
	make clean 
fi
make $1
if [ $2 ]; then
	valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all --vgdb=yes --vgdb-error=0 ./$1 < input.txt & gdb $1 -x "gdb commands.gtxt"
else
	valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./$1 < input.txt
fi
