// disp_vector.cpp
#include "disp_vector.h"

#include <iostream>

using std::cout;
using std::endl;

double dispVector( const vector<int>& vec )
{
   for ( const auto& v : vec )
      cout << v << endl;

   return 0;
}