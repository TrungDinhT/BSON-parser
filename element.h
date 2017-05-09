#ifndef ELEMENT_H
#define ELEMENT_H


/*element in the document*/

/* Array hasn't been implemented
   Types that will be dumped into hexadecimal (string unknown), including:
   DBpointer, symbol, regex, decimal128, code_w_s, binary data*/

/* Enumeration dataType is used for "imposing type" to different elements*/


#include <iostream>
#include <vector>



class document;


//#include "document.h"

enum dataType {
    _INT32_, 
    _INT64_, 
    DOUBLE, 
    ARRAY,
    DOCUMENT,
    _BOOL_, 
    UTC_TIME,
    TIMESTAMP,
    _NULL_, 
    STRING,
    OBJECT_ID,  
    JSCODE,
    UNDEFINED,
    MIN_KEY, 
    MAX_KEY,

//---------non-implemented type -> to string unknown (format: hexadecimal)---------//
/*    
    REGEX, 
    SYMBOL,
    DB_POINTER, 
    DEC128, 
    BINARY, 
    CODE_W_S
*/
    UNKNOWN
};



//Convert for dump
std::vector<char> convert_to_hex(std::vector<char> v);


struct element{

private: 
    dataType type; //inaccessible to modified for any derived class of base

public:
    element(const dataType& t=UNKNOWN): type(t){} 

    //accessors
    dataType getType() const { return type; }

};



template<typename T> struct type_element: public element{
    T value;
    type_element(T val, const dataType& t): value(val), element(t){}
};



struct double_element: public type_element<double>{
    double_element(const double val, const dataType& t): type_element(val,t){}
};


struct string_element: public type_element<std::string>{
    string_element(const std::string val, const dataType& t): type_element(val,t){}
};


struct bool_element: public type_element<bool>{
    bool_element(const bool val, const dataType& t): type_element(val,t){}
};


struct embedded_document: public type_element<document*>{
    embedded_document(document* doc, const dataType& t): type_element(doc,t){}
};


struct array: public type_element<std::vector<element*>>{
    array(std::vector<element*> v, const dataType& t): type_element(v,t){}
};


struct int32_element: public type_element<int>{
    int32_element(const int val, const dataType& t): type_element(val,t){}
};


struct int64_element: public type_element<long>{
    int64_element(const long val, const dataType& t): type_element(val,t){}

    std::string to_readable_time(){
        if (getType()==UTC_TIME){
            time_t rawtime = static_cast<time_t>(value/1000);
            struct tm * dt;
            char buffer [30];
            dt = localtime(&rawtime);
            strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%Y", dt);
            return std::string(buffer);
        }
        return "";
    }
};


struct timestamp: public type_element<unsigned long>{
    timestamp(const unsigned long val, const dataType& t): type_element(val,t){}
};

struct unknown_element: public type_element<std::string>{
    unknown_element(const std::string val, const dataType& t): type_element(val,t){}
};



#endif 
