f: func.o client.o
	g++ func.o client.o -o f
func.o: func.cpp func.h com_str.h
	g++ func.cpp -c -o func.o
client.o: client.cpp func.h
	g++ client.cpp -c -o client.o
clean:
	rm *.o f
