all: make

make: main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o
	g++ -g main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o -o exe 

%.o: %.cpp
	g++ -std=c++14 -c -o $@ $<

clean:
	rm -f *.o exe

