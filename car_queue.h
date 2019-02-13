#ifndef OOP_PROJECT_CAR_QUEUE_H
#define OOP_PROJECT_CAR_QUEUE_H

class car;

class car_queue {
private:
    struct Node{
        car* data;
        Node* next;
        Node* previous;

        Node(car* a_car, Node* next_node, Node* prev_node)
        :data(a_car), next(next_node), previous(prev_node){};
    };
    int size;
    Node* start;
    Node* end;

public:
    car_queue(void);
    ~car_queue();

    int get_size(void) const;

    void add_start(car* a_car);
    car* remove_end(void);
};


#endif //OOP_PROJECT_CAR_QUEUE_H