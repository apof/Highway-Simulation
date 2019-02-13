#include "entrance.h"
#include "segment.h"
#include "car_queue.h"
#include "car.h"

segment::segment(int id,int NSegs,int percent,int K ) : seg_id(id),Segs(NSegs),Percent(percent){
    cout << "Give segment's " << seg_id << " capacity: ";
    cin >> capacity;
    ready_queue = new car_queue();
    stay_queue = new car_queue();
    exit_queue = new car_queue();
    the_entrance = new entrance(seg_id, Segs, K, this, capacity);
    int num_of_cars = rand() % capacity;
    cout << "Number of cars selected to enter at start: " << num_of_cars << endl;
    car* a_car;
    for(int i = 0; i < num_of_cars; i++){
        if(seg_id != Segs-1){
            if(rand() % 2 == 0){
                a_car=new car(rand()%(Segs-seg_id-1)+seg_id+1,seg_id,false);            //ta ama3ia pou dhmiourgountai exoun ws e3odo kapoio epomeno segment
      		    stay_queue->add_start(a_car);
            }
            else{
                a_car=new car(rand()%(Segs-seg_id-1)+seg_id+1,seg_id,true);
                ready_queue->add_start(a_car);
            }
        }
        else{
            if(rand() % 2 == 0){
                a_car = new car(Segs-1, seg_id, false);           //ta ama3ia pou dhmiourgountai gia to teleytaio segment prepei na to exoun kai ws e3odo giati
                stay_queue->add_start(a_car);                  //den yparxei epomeno
            }
            else{
                a_car = new car(Segs-1, seg_id, true);
                exit_queue->add_start(a_car);
            }
        }
    }
 	cout << "Segment with id: " << seg_id << " and capacity " << capacity << " just created" << endl;

}

segment::~segment() {
	delete ready_queue;
    delete stay_queue;
    delete exit_queue;
    delete the_entrance;
    cout << "Segment with id: " << seg_id << " deleted" << endl;
}

void segment::connect_segment(segment* p, segment* n) {           //to segment syndeetai me to prohgoumeno kai to epomeno tou
    prev = p;
    next = n;
}

void segment::exit(void) {
    car *a_car;
    int max = exit_queue->get_size();
	for(int i = 0; i < max; i++){
        a_car=exit_queue->remove_end();
		delete a_car;
    }
    cout << "\t->Number of cars that exited segment " << seg_id << ": " << max << endl;
}

void segment::pass(void) {
   int max_pass_number;
   int pass_number;
   int next_seg;

    max_pass_number = next->get_capacity() - next->get_no_of_cars();     //ypologizei ton megisto arithmo autokinhtwn pou mporei na dexthei to epomeno segment
    if (max_pass_number == 0){
        cout<<"\t->The segment is full and cars can not pass!"<<endl;          //an o arithmos aytos einai 0 to epomeno segment einai full den mporei na dexthei ama3ia
    }
    else{
        if(max_pass_number > ready_queue->get_size())                 //an to epomeno segment dexetai parapanw ama3ia apo ta ready kanoun pass ola ta diathesima ready
            pass_number = ready_queue->get_size();
        else
            pass_number = max_pass_number;                               //an to epomeno segment den mporei na dexthei ola ta ready perna mono enas arithmos apo ayta

        car* a_car;
        cout << "\t->Number of cars selected to pass: " << pass_number << endl;
        for(int i=0; i<pass_number; i++){
            a_car = ready_queue->remove_end();
            a_car->set_not_ready();                                                  //kathe  ama3i otan kanei pass ena segment aexikopoieitai ws stay
            next_seg=seg_id+1;
            a_car->set_current_segment(next_seg);                                    //to seg_id tou ay3anetai kata 1 kathws pia tha kineitai sto epomeno segment
            next->stay_queue->add_start(a_car);                                       //kai topotheteitai sthn stay queue tou epomenou segment
        }
    }
}


int segment::get_no_of_cars(void) {
	return ready_queue->get_size()+stay_queue->get_size()+exit_queue->get_size();                              //plhthos aytokinhtwn enos segment =
                                                                                                                   //plhthos stay + plhthos ready + plhthos exit
}

void segment::set_ready(void) {
    if(stay_queue->get_size() != 0){
        int set_ready_number = (stay_queue->get_size()) * (Percent/100.0);            //epilegetai enas tyxaios arithmos ama3iwn apo th stay queue
        car* a_car;
        cout << "\t->Number of cars set ready: " << set_ready_number << endl;
        for (int i=0; i<set_ready_number; i++){
            a_car=stay_queue->remove_end();                               //afairountai apo thn stay queue
            a_car->set_ready();                                             //tithente ready
            if (a_car->get_dest()==seg_id)
                exit_queue->add_start(a_car);                                   //ama to ama3i exei ws proorismo to segment ayto mpainei sth exit_queue
            else
               ready_queue->add_start(a_car);                                   // alliws mpainoun sth ready queue
        }
    }
}

void segment::add_car(car* a_car) {
    stay_queue->add_start(a_car);
}

void segment::enter(void) {
    the_entrance->operate(capacity-get_no_of_cars());
                                                                                                  //stelnetai sth operate tou entrance o megistos aritmos ama3iwn
}                                                                                                //pou mporei na dexthei apo ta diodia tou entrance

void segment::operate(void) {
    cout<<"-Cars exiting from segment "<<seg_id<<endl;
    exit();                                                                  //prwta e3erxontai apo ton komvo osa am3ia einai etoima kai ton exoun ws proorismo
    if (prev!=NULL){
        cout<<"-Cars passing from segment "<<seg_id-1<<" to segment "<<seg_id<<endl;
        prev->pass();                                                                             //ta ypoloipa ready ama3ia pernoun ston epomeno komvo
    }
    cout<<"-Cars being set ready in segment "<<seg_id<<endl;
    set_ready();
    cout<<"-Cars entering from the entrance"<<endl;                                                    //kapoia apo ta stay ama3ia tithente ready
    enter();

    cout << endl << "========================================" << endl;
    if(the_entrance->get_car_count() != 0){
        cout << "Delays at the entrance of junction " << seg_id << "." << endl;
    }
    if(prev != NULL && prev->ready_queue->get_size() != 0){
        cout << "Delays after junction " << seg_id << "." << endl;
    }
    else if(the_entrance->get_car_count() == 0){
        cout << "Keep safe distances!" << endl;
    }
    cout << "========================================" << endl << endl;
}

