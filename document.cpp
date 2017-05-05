#include "document.h"
#include <iostream>
#include <unordered_map>

/*I haven't implemented the function to turn UTC_TIME and timestamp to readable format
 *I don't distinguish either JScode, string and objectID*/

document::document(const std::vector<char> buffer): parsed_doc(buffer){
		std::vector<char> res;
		res.push_back(buffer[0]);
		res.push_back(buffer[1]);
		res.push_back(buffer[2]);
		res.push_back(buffer[3]);
		length = *reinterpret_cast<int*>(res.data());
	}

std::ostream& document::dump(std::ostream& f) const {


	f<<"{"<<std::endl;

	for(auto it: ordered_key){
		f<<"    \""<< it <<"\": ";
		f<<e_list.at(it);
		//e_list.at(it)->print_out(f);
		f<<","<<std::endl;
	}

	f<<"}";
	return f;
}