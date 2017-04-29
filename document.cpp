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



std::ostream& document::dump(std::ostream& f) const {


	f<<"{"<<std::endl;

	for(auto it: ordered_key){
		f<<"    \""<< it <<"\": ";
		//f<<e_list.at(it)->getValue();
		e_list.at(it)->print_out(f);
		f<<","<<std::endl;
	}

	f<<"}";
	return f;
}