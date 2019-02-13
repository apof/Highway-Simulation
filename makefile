.PHONY: project clean

project: main.o car_queue.o car.o segment.o highway.o entrance.o
	g++ -o project main.o car_queue.o car.o segment.o highway.o entrance.o
	rm *.o

main.o: main.cpp
	g++ -c main.cpp

car_queue.o: car_queue.cpp car_queue.h 
	g++ -c car_queue.cpp
 
car.o: car.cpp car.h
	g++ -c car.cpp

segment.o: segment.cpp segment.h  
	g++ -c segment.cpp

highway.o: highway.cpp highway.h
	g++ -c highway.cpp

entrance.o: entrance.cpp entrance.h 
	g++ -c entrance.cpp

clean:
	rm project
          
