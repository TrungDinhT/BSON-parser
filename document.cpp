#include "document.h"


/*Functions to turn UTC_TIME, timestamp to readable format haven't been implemented
Function to dump to hexadecimal hasn't been implemented
 *JScode, string and objectID are considered as a same type*/

int read_length(const std::vector<char>& buffer){
		std::vector<char> res;
		res.push_back(buffer[0]);
		res.push_back(buffer[1]);
		res.push_back(buffer[2]);
		res.push_back(buffer[3]);
		return *reinterpret_cast<int*>(res.data());
}

document::document(const std::vector<char>& buffer): parsed_doc(buffer), length(read_length(buffer)){}

document::~document(){
		for(auto it: ordered_key)
			delete e_list.at(it);
}

Object document::operator[](const std::string keyname) {

	//if key not found, create a new element
	element* elm;
	try { elm = e_list.at(keyname); }
	catch(std::exception& e) { add_list(keyname, new element); }

	std::string to_convert;
	switch(elm->getType()){
		case DOUBLE:{ to_convert = static_cast<double_element*>(elm)->value; break; }
		case STRING:
		case OBJECT_ID:{ to_convert = static_cast<string_element*>(elm)->value; break; }
	}

	return to_convert;

}


unsigned int call_for_dump = 0;

std::ostream& document::dump(std::ostream& f) const {

	call_for_dump++;

	f<<std::endl;

	for(unsigned int i=0;i<call_for_dump-1;i++) f<<"    ";
	f<<"{"<<std::endl;

	unsigned int c=0;

	element* elm;

	for(auto it: ordered_key){
		c++;
		for(unsigned int i=0;i<call_for_dump;i++) f<<"    ";
		f<<"\""<< it <<"\": ";
		elm = e_list.at(it);
		switch(elm->getType()){

			//double
			case DOUBLE: { f<<static_cast<double_element*>(elm)->value; break; }
			
			//types considered as string
			case STRING: 
			case JSCODE: 
			case OBJECT_ID: { f<<"\""<<static_cast<string_element*>(elm)->value<<"\""; break; }

			//integer 
			case _INT32_: { f<<static_cast<int32_element*>(elm)->value; break; } 
			
			//long integer
			case _INT64_: { f<<static_cast<int64_element*>(elm)->value; break; }
			
			//case ARRAY:
			
			//embedded document
			case DOCUMENT: { static_cast<embedded_document*>(elm)->value->dump(f); break; }
			
			//boolean
			case _BOOL_: { if(static_cast<bool_element*>(elm)->value) f<<true; else f<<false; break; }

/*			//timestamp
			case TIMESTAMP: { f<<"\""<<static_cast<timestamp*>(elm)->to_readable_time()<<"\""; break;}
*/

			//UTC_TIME
			case UTC_TIME: { f<<"\""<<static_cast<int64_element*>(elm)->to_readable_time()<<"\""; break;}
			
			//types with no value
			case UNDEFINED: { f<<"(UNDEFINED)"<<elm; break;}
			case MIN_KEY: { f<<"(MIN KEY)"; break;}
			case MAX_KEY: { f<<"(MAX KEY)"; break;}
			case _NULL_: { f<<"(NULL)"; break; }


			
//---------non-implemented type -> to string unknown (format: hexadecimal)---------//
			
/*			case REGEX:
			case SYMBOL:
			case DB_POINTER:
			case DEC128: 
     		case BINARY:
     		case CODE_W_S: 
*/
     		default: { f<<static_cast<unknown_element*>(elm)->value; }

//---------------------------non-implemented yet-----------------------------------//

		}
		if(c < ordered_key.size()) { f<<","; }
		std::cout<<std::endl;
	}

	for(unsigned int i=0;i<call_for_dump-1;i++) f<<"    ";
	f<<"}";
	call_for_dump--;
	return f;
}