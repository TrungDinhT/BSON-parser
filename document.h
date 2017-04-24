#ifndef DOCUMENT_H
#define DOCUMENT_H



#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

class element;

#include "element.h"

class document{

private:
	std::vector<char> parsed_doc; 
	std::unordered_map<std::string, element> e_list;
	std::vector<std::string> ordered_key;
	int length;

public: 
	document(const std::vector<char> buffer): parsed_doc(buffer){}
	document(const document& doc);
	std::vector<char> get_parsed_doc() const { return parsed_doc; }
	int get_length() const { return length; }
	std::unordered_map<std::string, element> get_list_element() const { return e_list; }
	std::vector<std::string> get_ordered_key() const { return ordered_key; };
	std::ostream& dump(std::ostream& f) const;

	void set_length(const int l){ length = l; }
	void add_list(const std::string& key, element& elm){ e_list.insert(std::pair<std::string, element> (key,elm)); }
	void add_ordered_key(const std::string& k){ ordered_key.push_back(k); }
};

void parse(document& doc);

#endif 