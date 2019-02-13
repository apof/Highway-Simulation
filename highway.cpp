#include "highway.h"
#include "segment.h"

highway::highway(int Nsegs,int Percent,int K) : Segs(Nsegs),number_of_cars(0){
    seg_Array=new segment*[Segs];
    for(int i=0; i<Segs; i++) {
        seg_Array[i] = new segment(i, Segs, Percent, K);
        cout << endl;
    }

    for (int i = 0; i < Segs; i++){
        if (i != 0 && i != Segs-1)
            seg_Array[i]->connect_segment(seg_Array[i-1], seg_Array[i+1]);                 //to segment syndeetai me to prohgoumeno kai to epomeno tou
        else if (i==0)
            seg_Array[i]->connect_segment(NULL, seg_Array[i+1]);                           //to prwto segment den exei prohgoumeno ara o prev deikths prepei na tethei NULL
        else
            seg_Array[i]->connect_segment(seg_Array[i-1], NULL);                           //to teleytaio segment den exei epomeno ara o deikths next prepei na einai NULL
    }
    cout<<"Segments connected!"<<endl;

    cout << "Highway with " << Segs << " segments created." <<endl;
}

highway::~highway(){
    for(int i = 0; i <Segs; i++)
        delete seg_Array[i];

    delete [] seg_Array;
    cout<<"Highway destroyed."<<endl;
}

int highway::get_no_of_cars() {
    return number_of_cars;
}


void highway::operate() {
    number_of_cars=0;
    for(int i = Segs-1; i >= 0; i--){
        cout << "#### Segment " << i << " operation. ####" << endl << endl;
        seg_Array[i]->operate();
        number_of_cars += seg_Array[i]->get_no_of_cars();
        cout << endl << endl;
    }
}