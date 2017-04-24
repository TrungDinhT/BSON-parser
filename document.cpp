#include "document.h"
#include <iostream>
#include <unordered_map>

/*I haven't implemented the function to turn UTC_TIME and timestamp to readable format
 *I don't distinguish either JScode, string and objectID*/


//copy constructor 

document::document(const document& doc): length(doc.get_length()){
	
	for(auto it : doc.get_parsed_doc()){
		parsed_doc.push_back(it);
	}

	for(auto it : doc.get_ordered_key()){
		ordered_key.push_back(it);
	}

	for(auto it : doc.get_list_element()){
		e_list.insert(it);
	}

}



//overloaded operator<<

std::ostream& operator<<(std::ostream&f, const element& elm){
	switch(elm.get_type()){
			//double
			case _INT32_: { f<<elm.get_int32(); break; }
			case _INT64_: { f<<elm.get_int64(); break; }
			case DOUBLE: { f<<elm.get_double(); break; }
			case ARRAY:
			case DOCUMENT: { f<<elm.get_embedded_doc()->dump(f); break; }
			case _BOOL_: { if(elm.get_bool()) f<<"true"; else f<<"false"; break; }
			case UNDEFINED: { f<<"(undefined)"; break;}
			case MIN_KEY: { f<<"(min key)"; break;}
			case MAX_KEY: { f<<"(max key)"; break;}
			case _NULL_: { f<<"NULL"; break; }
			case STRING:
			case OBJECT_ID:
			case JSCODE: { f<<"\""<<elm.get_string()<<"\""; break; }
			
//---------non-implemented type -> to string unknown (format: hexadecimal)---------//
			
			case REGEX:
			case SYMBOL:
			case DB_POINTER:
			case DEC128: 
     		case BINARY:
     		case CODE_W_S: 
     		default: f<<"\""<<elm.get_string()<<"\"";

//---------------------------non-implemented yet-----------------------------------//

     		/*case ARRAY: 
			case UTC_TIME:
			case TIMESTAMP:*/
		}

	return f;

}





std::ostream& document::dump(std::ostream& f) const {


	f<<"{"<<std::endl;

	for(auto it: ordered_key){
		f<<"    \""<< it <<"\": "<< e_list.at(it) <<","<<std::endl;
	}

	f<<"}";
	return f;
}