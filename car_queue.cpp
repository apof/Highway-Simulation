#include <stdio.h>
#include "car_queue.h"
#include "car.h"

car_queue::car_queue(void) :size(0), start(NULL), end(NULL){}

car_queue::~car_queue() {
    Node *n = start;
    Node *temp;
    for (int i = 0; i < size; i++) {
        temp = n->next;
        delete n->data;
        delete n;
        n = temp;
    }
}

int car_queue::get_size(void) const {
    return size;
}

void car_queue::add_start(car *a_car) {
    Node *n = new Node(a_car, start, NULL);

    if(size == 0){
        start = end = n;
    }
    else{
        start->previous = n;
        start = n;
    }

    size++;
}

car *car_queue::remove_end(void) {
    if(size == 0){
        return NULL;
    }

    Node* n = end;
    car* a_car = end->data;

    if(size == 1){
        start = end = NULL;
    }
    else{
        end = end->previous;
        end->next = NULL;
    }

    size--;
    delete n;
    return a_car;
}