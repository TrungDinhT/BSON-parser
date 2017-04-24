#ifndef ELEMENT_H
#define ELEMENT_H


/*element in the document*/

/* I'm considering array and document are the same
   All types that are not implemented yet or deprecated 
   will be turn into a string of hexadecimal (string unknown), including:
   DBpointer, symbol, regex, decimal128, code_w_s, binary data*/


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
//---------non-implemented type -> to string unknown (format: hexadecimal)---------//
    UNDEFINED,
    REGEX, 
    SYMBOL,
    DB_POINTER, 
    DEC128, 
    MIN_KEY, 
    MAX_KEY,
    BINARY, 
    CODE_W_S
};


class element {
private:
    dataType type;

    /*
    unknown field to transform to hexadecimal
    * std::string binary;
    * std::string dec128;
    * std::string reg_exp;
    * std::string db_pointer;
    * std::string code_w_s;
    */
    std::string str;
    std::string unknown;

    int int32;
    long int64;
    double db;
    unsigned long timestamp;

    document *doc;

    bool boolean;

public:

    element(const int i32, const dataType t) : int32(i32), type(t){}

    element(const long i64, const dataType t) : int64(i64), type(t){}

    element(const double d) : db(d), type(DOUBLE){}

    element(const unsigned long tst) : timestamp(tst), type(TIMESTAMP){}

    element(bool b) : boolean(b), type(_BOOL_){}

    element(const dataType& t): type(t){} //_NULL_ or UNDEFINED or MIN_KEY or MAX_KEY

    element(const std::string &s, const dataType t): type(t) {
        switch(t){
            case STRING: case OBJECT_ID: case JSCODE: {str=s; break;}
            default: unknown = s;
        }
    }
   
    element(document* emb) : doc(emb), type(DOCUMENT){}
        
    std::string to_unknown_string();

    const dataType &get_type() const {
        return type;
    }



    int get_int32() const { return int32; }

    long get_int64() const { return int64; }

    double get_double() const { return db; }

    bool get_bool() const { return boolean; }

    const std::string& get_string() const { return str; }

    unsigned long get_timestamp() const { return timestamp; }

    document* get_embedded_doc() const {
        return doc;
    }

 

    void set_int32(const int i32) { 
        type = _INT32_;
        int32 = i32; 
    }

    void set_int64(const long i64, const dataType& t) { 
        type = t;
        int64 = i64; 
    }

    void setDouble(const double d) { 
        type = DOUBLE;
        db = d; 
    }

    void set_string(const std::string &s, const dataType& t) { 
        switch(t){
            case STRING: case OBJECT_ID: case JSCODE: {str=s; break;}
            default: unknown = s;
        }
    }

    void set_bool(bool b) {
        type = _BOOL_;
        boolean = b;
    }

    void set_timestamp(const unsigned long tst) {
        type = TIMESTAMP;
        timestamp = tst;
    }

    void set_UTC_time(const long utc) {
        type = UTC_TIME;
        int64 = utc;
    }

    void set_document(document *d) {
        type = DOCUMENT;
        doc = d;
    }


};


//overloading operator<< to facilitate the print-out of method dump()
std::ostream& operator<<(std::ostream& f, const element& e);

#endif 
