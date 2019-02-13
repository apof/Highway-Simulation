#ifndef OOP_PROJECT_SEGMENT_H
#define OOP_PROJECT_SEGMENT_H

#include <iostream>
#include <cstdlib>

using namespace std;

class entrance;
class car;
class car_queue;

class segment {
private:
    int capacity;
    int seg_id;
    int Percent;
    int Segs;
    car_queue* ready_queue;
    car_queue* stay_queue;
    car_queue* exit_queue;
    entrance*  the_entrance;
    segment* next;
    segment* prev;
public:
    segment(int,int,int,int);
    ~segment();
    void connect_segment(segment* p,segment* n);
    int get_capacity() const { return capacity; }
    void enter(void);
    void add_car(car*);
    void exit(void);
    void pass(void);
    int get_no_of_cars(void);
    void set_ready(void);
    void operate(void);
};

#endif