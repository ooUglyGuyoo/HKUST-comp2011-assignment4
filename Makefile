ALL:
	g++ -g *.cpp -o a.out
	./a.out
	
	#g++.exe -g *.cpp -o make.exe
	#./make.exe

	#//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./a.out
