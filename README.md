# BSON parser

A simple BSON parser written in C++.


### Compile

This should be compiled in C++11.


### Function

In main, BSON file will be loaded on a vector char for parsing.

Base class _Document_ provides methods for accessing parsed values, including:

+   _dump()_ for printing out parsed values in JSON format.

+   _operator[]_ (overloaded) for searching value by keyname.

+   *key_iterator* for iterating through all parsed values following the order of insertion 

Test files are in folder "samples". Test by running file main (after compiling) with filename

-> ./main test.bson
  
