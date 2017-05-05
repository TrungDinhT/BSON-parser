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



//Convert for dump
std::vector<char> convert_to_hex(std::vector<char> v);


struct element{

private: 
    dataType type; //inaccessible to modified for any derived class of base

public:
    element(const dataType& t=UNDEFINED): type(t){} 

    //accessors
    dataType getType() const { return type; }

};


template<typename T> struct type_element: public element{

    T value;

    type_element(const T val, const dataType& t): value(val), element(t){}

};

struct double_element: public type_element<double>{
    double_element(const double val, const dataType& t): type_element(val,t){}
};

struct string_element: public type_element<std::string>{
    string_element(const std::string val, const dataType& t): type_element(val,t){}
};


//overloading operator<< to facilitate the print-out of method dump()
std::ostream& operator<<(std::ostream& f, element* elm);



/*
//-------------------------classes of accessors------------------------

class double_tools{

public:
    virtual double getValue() const = 0;
    virtual void setValue(const double val) = 0;
};


class string_tools{

public:
    virtual std::string getValue() const = 0;
    virtual void setValue(const std::string val) = 0;
};

//class int32_tools;
//class int64_tools;
//class uint64_tools;
//class bool_tools;

class element: public virtual double_tools, public virtual string_tools
//, public int32_tools, 
//public int64_tools, public uint64_tools, public bool_tools

{

protected: 
    dataType type;

public:
    element(const dataType& t=UNDEFINED): type(t){} 

    //accessors
    dataType getType() const { return type; }


    virtual void print_out(std::ostream& f) const = 0;

};


//---------------------------Subclasses------------------------------



class double_element: public element, public virtual double_tools{

private:
    double value;

public:

    double_element(const double val): element(DOUBLE), value(val){}   

    double double_tools::getValue() const {return value;}
    void setValue(const double val) { value = val; }

    void print_out(std::ostream& f)const{ f << value; }


    /*std::string string_tools::getValue() const;
    void setValue(const std::string val);
};


/*class int32_element: public element{

protected:

    int value;

public:

    friend element;
    int32_element(const int& val): element(_INT32_), value(val){}   
    //int getValue() const { return value; }
    void setValue(const int& val) { value = val; }

    //void setKeyname(const std::string& k) { keyname = k; }

    //static_cast<const double&> void getValue() const {return value;}

    void print_out(std::ostream& f)const{ f << value; }

    void setType() { type = _INT32_; }

};


class int64_element: public element{

protected:

    long value;

public:

    friend element;
    int64_element(const long& val): element(_INT64_), value(val){}   
    //long getValue() const { return value; }
    void setValue(const long& val) { value = val; }

    //void setKeyname(const std::string& k) { keyname = k; }

    void print_out(std::ostream& f)const{ f << value; }

    void setType() { type = _INT64_; }

};


class string_element: public element{

private:
    std::string value;

public:

    string_element(const std::string val): element(STRING), value(val){}   
    
    std::string getValue() const { return value; }
    void setValue(const std::string val) { value = val; }

    void print_out(std::ostream& f)const{ f<<"\""<<value<<"\""; }   


    double getValue() const {}
    void setValue(const double val) {}

};


class objectID_element: public element{

protected:
    std::string value;

public:

    objectID_element(const std::string val): element(OBJECT_ID), value(val){}   
    
    std::string getValue() const { return value; }
    void setValue(const std::string val) { value = val; }

    void print_out(std::ostream& f)const{ f<<"\""<<value<<"\""; }   


    double getValue() const {}
    void setValue(const double val) {}

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

*/





#endif 
