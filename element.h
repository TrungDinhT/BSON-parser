#ifndef ELEMENT_H
#define ELEMENT_H


/*element in the document*/

/* I'm considering array and document are the same
   All types that are not implemented yet or deprecated 
   will be turn into a string of hexadecimal (string unknown), including:
   DBpointer, symbol, regex, decimal128, code_w_s, binary data*/

/* variable type and type enumeration dataType 
 * are used for distinguishing different attributes represented by the same data type*/

/////////////////////* ACCESSORS STILL DONT WORK!!!! *///////////////////////////////////////


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

/*
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
*/


//overloading operator<< to facilitate the print-out of method dump()
//std::ostream& operator<<(std::ostream& f, const element* elm);

//Convert for dump
std::vector<char> convert_to_hex(std::vector<char> v);



class element {

protected: 

    //std::string keyname;
    dataType type;


public:

    element(const dataType& t=UNDEFINED): type(t){} 

    //accessors
    dataType getType() const { return type; }
    //std::string getKeyname(){ return keyname; }
    virtual void setType() = 0;

    

    virtual void print_out(std::ostream& f) const = 0;

};


//---------------------------Subclasses------------------------------



class double_element: public element{

protected:

    double value;

public:

    friend element;
    double_element(const double& val): element(DOUBLE), value(val){}   
    double getValue() const { return value; }
    void setValue(const double& val) { value = val; }

    //void setKeyname(const std::string& k) { keyname = k; }

    void print_out(std::ostream& f)const{ f << value; }

    void setType() { type = DOUBLE; }
};


class int32_element: public element{

protected:

    int value;

public:

    friend element;
    int32_element(const int& val): element(_INT32_), value(val){}   
    int getValue() const { return value; }
    void setValue(const int& val) { value = val; }

    //void setKeyname(const std::string& k) { keyname = k; }

    void print_out(std::ostream& f)const{ f << value; }

    void setType() { type = _INT32_; }

};


class int64_element: public element{

protected:

    long value;

public:

    friend element;
    int64_element(const long& val): element(_INT64_), value(val){}   
    long getValue() const { return value; }
    void setValue(const long& val) { value = val; }

    //void setKeyname(const std::string& k) { keyname = k; }

    void print_out(std::ostream& f)const{ f << value; }

    void setType() { type = _INT64_; }

};


class string_element: public element{

protected:

    std::string value;

public:

    friend element;
    string_element(const std::string& val): element(STRING), value(val){}   
    std::string getValue() const { return value; }
    void setValue(const std::string& val) { value = val; }

    //void setKeyname(const std::string& k) { keyname = k; }

    void print_out(std::ostream& f)const{ f<<"\""<<value<<"\""; }   

    void setType() { type = STRING; }

};


class objectID_element: public element{

protected:

    std::string value;

public:

    friend element;
    objectID_element(const std::string& val): element(OBJECT_ID), value(val){}   
    std::string getValue() const { return value; }
    void setValue(const std::string& val) { value = val; }

    //void setKeyname(const std::string& k) { keyname = k; }

    void print_out(std::ostream& f)const{ f<<"\""<<value<<"\""; }   

    void setType() { type = OBJECT_ID; }

};


class embedded_document: public element{

};



class array: public element{

};


class boolean_element: public element{

};

class timestamp_element: public element{

};

class undefined_element: public element{

};

class null_element: public element{

};





#endif 
