/* unordered_map to store pointers to elements while keeping accessing in O(1)
   
   vector of keyname to keep track of element's insertion order
   
   iterating over vector of keyname can only be conducted by iterator of document class

   look up for element with keyname is possible by overloading operator[]

*/



#ifndef DOCUMENT_H
#define DOCUMENT_H



#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>


#include "element.h"

class document{

private:

	std::vector<char> parsed_doc; 
	std::unordered_map<std::string, element*> e_list;
	std::vector<std::string> ordered_key;
	int length;

	document(const document& doc);

public: 

	document(const std::vector<char> buffer);
	
	int len() const { return length; }
	
	std::ostream& dump(std::ostream& f) const;

	void add_list(const std::string& key, element* elm){ 
		
		//keep track of insertion order
		ordered_key.push_back(key);
		e_list.insert(std::pair<std::string, element*> (key,elm));
	}
	
	const element& operator[](const std::string keyname) const; 


	class key_iterator{

	private:

		std::vector<std::string>::iterator str;
		key_iterator(std::vector<std::string>::iterator pstr): str(pstr){}
		friend class document;

	public:

		key_iterator(): str(nullptr){}
		bool operator!=(key_iterator it) const { return it.str != str; }
		key_iterator& operator++() { str++; return *this; }
		key_iterator operator++(int) { key_iterator* old = this; str++; return *old; }
		const std::string& operator*() const { return *str; }

	};


	key_iterator first_key() { key_iterator(ordered_key.begin()); }

	key_iterator last_key() { key_iterator(ordered_key.end()); }
};

void parse(document& doc, const std::vector<char>& to_parse);

#endif 