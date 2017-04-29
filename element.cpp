#include "document.h"
#include <iostream>
#include <unordered_map>

/*I haven't implemented the function to turn UTC_TIME and timestamp to readable format
 *I don't distinguish either JScode, string and objectID*/




//overloaded operator<<
/*
std::ostream& operator<<(std::ostream& f, const element* elm){
	switch(elm.getType()){
			//double
			case _INT32_: 
			case _INT64_: 
			case DOUBLE: { f<<elm->getValue(); break; }
			//case ARRAY:
			//case DOCUMENT: { f<<elm->getValue()->dump(f); break; }
			case _BOOL_: { if(elm->getValue()) f<<"true"; else f<<"false"; break; }
			//case UNDEFINED: { f<<"(undefined)"<<elm; break;}
			case MIN_KEY: { f<<"(min key)"; break;}
			case MAX_KEY: { f<<"(max key)"; break;}
			case _NULL_: { f<<"NULL"; break; }
			case STRING:
			case OBJECT_ID: { f<<"\""<<elm->getValue()<<"\""; break; }
			//case JSCODE: { f<<"\""<<elm->getValue()<<"\""; break; }
			
//---------non-implemented type -> to string unknown (format: hexadecimal)---------//
			
			case REGEX:
			case SYMBOL:
			case DB_POINTER:
			case DEC128: 
     		case BINARY:
     		case CODE_W_S: 
     		default: f<<"\""<<elm->getValue()<<"\"";

//---------------------------non-implemented yet-----------------------------------//

     		/*case ARRAY: 
			case UTC_TIME:
			case TIMESTAMP:
		}

	return f;

}
*/



