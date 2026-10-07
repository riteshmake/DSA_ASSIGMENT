CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99
CXXFLAGS = -Wall -Wextra -std=c++11

TARGETS = q1_stack/stack_c q1_stack/stack_cpp q2_circular_queue/queue_c q2_circular_queue/queue_cpp

all: $(TARGETS)

q1_stack/stack_c: q1_stack/stack.c
	$(CC) $(CFLAGS) -o $@ $<

q1_stack/stack_cpp: q1_stack/stack.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

q2_circular_queue/queue_c: q2_circular_queue/circular_queue.c
	$(CC) $(CFLAGS) -o $@ $<

q2_circular_queue/queue_cpp: q2_circular_queue/circular_queue.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) *.exe q1_stack/*.exe q2_circular_queue/*.exe

.PHONY: all clean
