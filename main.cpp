#include "highway.h"

using namespace std;

int main(int argc,char* argv[]) {

    int N,K,Percent,Nsegs;

    if(argc != 5){
        cerr << "Usage: project <N> <NSegs> <K> <Percent>" << endl;
        return -1;
    }
    else{
            N = atoi(argv[1]);
            Nsegs = atoi(argv[2]);
            K = atoi(argv[3]);
            Percent = atoi(argv[4]);

        cout << "Starting simulation with " << Nsegs << " segments." << endl;
        cout << "Initial K for each entrance is " << K << "." << endl;
        cout << "Set ready percentage is " << Percent << "%." << endl;
        cout << "The simulation will run for " << N << " circles." << endl << endl;
        cout << "*****************************************************************"<<endl;
    }

    srand((unsigned)time(NULL));

    highway the_highway(Nsegs,Percent,K);

    for(int i = 0; i < N; i++){
        cout<<"===== Operation Circle #" << i+1 << " =====" << endl << endl;
        the_highway.operate();
        cout<<"Total number of cars in the highway: " << the_highway.get_no_of_cars() << endl;
        cout << endl << endl;
    }

    return 0;
}
