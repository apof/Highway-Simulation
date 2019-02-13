#include <iostream>
#include <cstdlib>

class segment;

using namespace std;

class highway {
  private:
   int Segs;
   segment **seg_Array;
   int number_of_cars;
  public:
   highway(int,int,int);
   ~highway();
   int  get_no_of_cars();
   void operate();
};
