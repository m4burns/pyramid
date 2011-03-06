%module(directors="1") pyramid
%feature("autodoc", "1");

%include "typemaps.i"
%include "std_string.i"

%{
        #include "PythonMapper.h"
%}

%feature("director") PythonMapper;

//%apply SWIGTYPE *DISOWN {WyndhamCallbackList*};

%include "PythonMapper.h"

