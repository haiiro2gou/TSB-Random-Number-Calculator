// pymodulue.cpp
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "disp_vector.h"

PYBIND11_MODULE( mymodule, m )
{
   m.doc() = "mymodule";
   m.def( "disp_vec", &dispVector, "display vector" );
}