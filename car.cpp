#include <iostream>
#include "car.h"

car::car(int dest_seg, bool isready)
:destination(dest_seg), current_segment(-1), ready(isready){
    std::cout << "Creating a car with destination " << destination << std::endl;
}

car::car(int dest_seg, int cur_seg, bool isready)
:destination(dest_seg), current_segment(cur_seg), ready(isready){
    std::cout << "Creating a car in segment " << current_segment << " with destination " << destination << std::endl;
}


bool car::is_ready(void) const {
    return ready;
}

int car::get_dest(void) const {
    return destination;
}


void car::set_ready(void) {
    ready = true;
}

void car::set_not_ready(void) {
    ready = false;
}

void car::set_current_segment(int segment) {
    current_segment = segment;
}
