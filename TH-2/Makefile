CC = g++
CFLAGS = -std=c++11 -Wall -O2 -pthread
LIBRARY_NAME = parallel_scheduler
DEMO_NAME = demo_application
LIBRARY_OUTPUT = lib$(LIBRARY_NAME).so

$(LIBRARY_OUTPUT): parallel_scheduler.o
	$(CC) -shared -o $(LIBRARY_OUTPUT) parallel_scheduler.o


$(DEMO_NAME): demo_application.o $(LIBRARY_OUTPUT)
	$(CC) -o $(DEMO_NAME) demo_application.o -L. -lparallel_scheduler


parallel_scheduler.o: parallel_scheduler.cpp parallel_scheduler.h
	$(CC) $(CFLAGS) -fPIC -c parallel_scheduler.cpp


demo_application.o: demo_application.cpp parallel_scheduler.h
	$(CC) $(CFLAGS) -c demo_application.cpp


clean:
	rm -f *.o $(LIBRARY_OUTPUT) $(DEMO_NAME)


all: $(LIBRARY_OUTPUT) $(DEMO_NAME)
