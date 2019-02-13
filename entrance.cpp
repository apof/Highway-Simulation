#include "entrance.h"
#include "segment.h"
#include "car_queue.h"
#include "car.h"

entrance::entrance(int id, int total_segs, int init_K, segment *my_seg, int my_seg_size)
:entrance_id(id), segs(total_segs), K(init_K),my_segment(my_seg) {

    my_segment = my_seg;
    car *a_car;

    employee_toll_count = my_seg_size/20 == 0 ? 1 : my_seg_size/20;

    employee_tolls = new car_queue*[employee_toll_count] ;
    for (int i = 0; i < employee_toll_count; i++) {
        employee_tolls[i] = new car_queue;
        for (int j = rand() % 5; j > 0; j--) {
            a_car = new car(rand() % (segs - entrance_id) + entrance_id,false);
            employee_tolls[i]->add_start(a_car);
        }
    }

    electronic_toll_count = my_seg_size/10 == 0 ? 1 : my_seg_size/10;

    electronic_tolls = new car_queue*[electronic_toll_count];
    for (int i = 0; i < electronic_toll_count; i++) {
        electronic_tolls[i] = new car_queue;
        for (int j = rand() % 5; j > 0; j--) {
            a_car = new car(rand() % (segs - entrance_id) + entrance_id, false);
            electronic_tolls[i]->add_start(a_car);
        }
    }

    std::cout << "Created entrance for segment " << entrance_id << " with " << employee_toll_count << " employee tolls and " << electronic_toll_count << " electronic tolls." << std::endl;
}

entrance::~entrance() {
    for (int i = 0; i < employee_toll_count; i++) {
        delete employee_tolls[i];
    }
    delete[] employee_tolls;

    for (int j = 0; j < electronic_toll_count; j++) {
        delete electronic_tolls[j];
    }
    delete[] electronic_tolls;
}

int entrance::cars_in_electronic_tolls(void) const {
    int count = 0;
    for (int i = 0; i < electronic_toll_count; i++) {
        count += electronic_tolls[i]->get_size();
    }
    return count;
}

int entrance::cars_in_employee_tolls(void) const {
    int count = 0;
    for (int i = 0; i < employee_toll_count; i++) {
        count += employee_tolls[i]->get_size();
    }
    return count;
}

void entrance::pass_cars(int max_cars) {
    std::cout << "\t->A maximum of " << max_cars << " cars can pass from the tolls in segment " << entrance_id << "." << std::endl;
    car* a_car;
    int i, j;

    int passed_from_employee = max_cars * 0.4;
    if(passed_from_employee > cars_in_employee_tolls()){
        passed_from_employee = cars_in_employee_tolls();
    }
    if(passed_from_employee > K){
        passed_from_employee = K;
    }


    int passed_from_electronic = max_cars - passed_from_employee;
    if(passed_from_electronic > cars_in_electronic_tolls()){
        passed_from_electronic = cars_in_electronic_tolls();
    }
    if(passed_from_electronic > 2*K){
        passed_from_electronic = 2*K;
    }



    j = -1;
    for (i = 0; i < passed_from_electronic; i++) {
        do{
            j = (j + 1) % electronic_toll_count;
        }while(electronic_tolls[j]->get_size() == 0);

        a_car = electronic_tolls[j]->remove_end();
        a_car->set_current_segment(entrance_id);
        my_segment->add_car(a_car);
    }
    std::cout << "\t\t" << passed_from_electronic << " cars passed from electronic tolls in entrance " << entrance_id << "." << std::endl;

    j = -1;
    for (i = 0; i < passed_from_employee; i++) {
        do{
            j = (j + 1) % employee_toll_count;
        }while(employee_tolls[j]->get_size() == 0);

        a_car = employee_tolls[j]->remove_end();
        a_car->set_current_segment(entrance_id);
        my_segment->add_car(a_car);
    }
    std::cout << "\t\t" << passed_from_employee << " cars passed from employee tolls in entrance " << entrance_id << "." << std::endl;

    if(passed_from_electronic == 2*K && passed_from_employee == K){
        K++;
        std::cout << "\t->K increased in entrance " << entrance_id << "." << std::endl;
    }
    else{
        K--;
        std::cout << "\t->K decreased in entrance " << entrance_id << "." << std::endl;
    }
}

void entrance::add_cars(void) {
    std::cout << "\t-> New cars arriving at the tolls." << std::endl;
    car *a_car;

    for (int i = 0; i < employee_toll_count; i++) {
        for (int j = rand() % 3; j > 0; j--) {
            std::cout << "\t\t";
            a_car = new car(rand() % (segs - entrance_id) + entrance_id,false);
            employee_tolls[i]->add_start(a_car);
        }
    }

    for (int i = 0; i < electronic_toll_count; i++) {
        for (int j = rand() % 5; j > 0; j--) {
            std::cout << "\t\t";
            a_car = new car(rand() % (segs - entrance_id) + entrance_id, false);
            electronic_tolls[i]->add_start(a_car);
        }
    }
}

void entrance::operate(int max_cars) {
    add_cars();
    pass_cars(max_cars);
}

int entrance::get_car_count(void) const {
    return cars_in_electronic_tolls() + cars_in_employee_tolls();
}