#ifndef OOP_PROJECT_CAR_H
#define OOP_PROJECT_CAR_H


class car {
private:
    int destination;
    int current_segment;
    bool ready;
public:
    car(int dest_seg, bool isready);
    car(int dest_seg, int cur_seg, bool isready);

    bool is_ready(void) const;
    int get_dest(void) const;

    void set_ready(void);
    void set_not_ready(void);
    void set_current_segment(int segment);
};


#endif //OOP_PROJECT_CAR_H
