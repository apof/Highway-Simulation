#ifndef OOP_PROJECT_ENTRANCE_H
#define OOP_PROJECT_ENTRANCE_H

#include <cstdlib>

class segment;
class car_queue;

class entrance {
private:
    int entrance_id;
    int segs;
    int K;
    int employee_toll_count;
    int electronic_toll_count;
    car_queue **employee_tolls;
    car_queue **electronic_tolls;
    segment *my_segment;

    int cars_in_electronic_tolls(void) const;
    int cars_in_employee_tolls(void) const;

    void pass_cars(int max_cars);
    void add_cars(void);

public:
    entrance(int id, int total_segs, int init_K, segment *my_seg, int my_seg_size);
    ~entrance();

    void operate(int max_cars);

    int get_car_count(void) const;
};


#endif //OOP_PROJECT_ENTRANCE_H
