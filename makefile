default:
	g++ -std=c++11 -c *.cpp
	g++ -std=c++11 *.o -o evtol.out && ./evtol.out

clean:
	rm *.o
	rm *.out