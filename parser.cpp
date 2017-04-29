
#include "document.h"

/*I haven't implemented yet the unknown data the function to read the unknown data*/




/* function for converting a vector of char to its origin hexadecimal values
 */
std::vector<char> convert_to_hex(std::vector<char> str) {
    static char hex_table[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                               '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    std::vector<char> res;
    for (unsigned char it: str) { 
        res.push_back(hex_table[it / 16]);
        res.push_back(hex_table[it % 16]);
    }
    return res;
}



/* function for iterating over vector v, in a "distance" = data_size
 * at the end, we modify pos = current position on this vector
 */
std::vector<char> iterate_and_get(std::vector<char> v, unsigned int& pos, unsigned int data_size){
	
	std::vector<char> res;
	
	for (unsigned int i; i<data_size; ++i) { 
        res.push_back(v[pos + i]);
    }

    pos += data_size;
    return res;
}



double read_double(std::vector<char> v, unsigned int& pos){	//sizeof(double)=8
	
	return *reinterpret_cast<double*>(iterate_and_get(v,pos,8).data());
}


int read_int32(std::vector<char> v, unsigned int& pos){	//sizeof(int)=4

	return *reinterpret_cast<int*>(iterate_and_get(v,pos,4).data());
}


long read_int64(std::vector<char> v, unsigned int& pos){	//sizeof(long)=8
	
	return *reinterpret_cast<long*>(iterate_and_get(v,pos,8).data());
}


unsigned long read_uint64(std::vector<char> v, unsigned int& pos){	//sizeof(unsigned long)=8

	return *reinterpret_cast<int*>(iterate_and_get(v,pos,8).data());
}


bool read_bool(std::vector<char> v, unsigned int& pos){

	unsigned int pos_old = pos;

	pos++; //go to next element

	return v[pos_old]=='\x01';

}


std::string read_cstring(std::vector<char> v, unsigned int& pos){
	std::string cstring;
	for(;v[pos]!='\x00';pos++){
		cstring += v[pos];
	}

	//pass the '\x00' at the end of cstring and go to next element 
	pos ++;

	return cstring;
}


std::string read_objectId(std::vector<char> v, unsigned int& pos){
	std::vector<char> objId = convert_to_hex(iterate_and_get(v,pos,12));

	return std::string(objId.data(), objId.size());
}


/*first take the length of string, then iterate and get characters*/
std::string read_string(std::vector<char> v, unsigned int& pos){

	unsigned int strlen = read_int32(v,pos);

	return std::string(iterate_and_get(v,pos,strlen).data(),strlen);
}


std::vector<char> read_embedded_doc(std::vector<char> v, unsigned int& pos){

	unsigned int doc_len = read_int32(v,pos);
	std::vector<char> res(doc_len); //read length of doc

	for(unsigned int i=0; i<doc_len; i++)
		res[i] = v[pos+i-4];
	pos += (doc_len - 4);

	return res;
}

void parse(document& doc){

	unsigned int pos = 0;

	std::vector<char> parsed_doc = doc.get_parsed_doc();
	std::string keyname; 
	int length = read_int32(parsed_doc,pos);
	doc.set_length (length);

	unsigned int indicator;

	while (pos<length-1){

		indicator = pos;

		//go to the begin of keyname encoded
		pos++; 
		element* elm;

		//read keyname and add into vector of ordered keys
		keyname = read_cstring(parsed_doc,pos);
		doc.add_ordered_key(keyname); 

		switch(parsed_doc[indicator]){
			//double
			case '\x01': {							
							//element elm(read_double(parsed_doc,pos),DOUBLE); 
							elm = new double_element(read_double(parsed_doc,pos));
							doc.add_list(keyname,elm);
							break; 
						}

			/*//JScode
			case '\x0D': {	
							//element elm(read_string(parsed_doc,pos), JSCODE); 
							doc.add_list(keyname,elm);
							break; 
						}*/

			//string UTF-8
			case '\x02': {	
							//element elm(read_string(parsed_doc,pos), STRING); 
							elm = new string_element(read_string(parsed_doc,pos));
							doc.add_list(keyname,elm);
							break; 
						}
			
			//array
			//case '\x04': 

			/*//document embedded
			case '\x03': {	
							document embedded_doc(read_embedded_doc(parsed_doc,pos));
							parse(embedded_doc);
							element elm(&embedded_doc); 
							doc.add_list(keyname,elm);
							break; 
						}

			//undefine value
			case '\x06':{	
							element elm(UNDEFINED); 
							doc.add_list(keyname,elm);
							break; 
						}*/

			//ObjectID
			case '\x07': {	
							//element elm(read_objectId(parsed_doc,pos), OBJECT_ID); 
							elm = new string_element(read_objectId(parsed_doc,pos));
							doc.add_list(keyname,elm);
							break; 
						}

			/*//Boolean
			case '\x08': {	
							element elm(read_bool(parsed_doc,pos)); 
							doc.add_list(keyname,elm);
							break; 
						}

			//UTC datetime
			case '\x09': {	
							element elm(read_int64(parsed_doc,pos), UTC_TIME); 
							doc.add_list(keyname,elm);
							break; 
						}

			//null value
			case '\x0A': {	
							element elm(_NULL_); 
							doc.add_list(keyname,elm);
							break; 
						}*/

			//int32
			case '\x10':{	
							//element elm(read_int32(parsed_doc,pos), _INT32_); 
							elm = new int32_element(read_int32(parsed_doc,pos));
							doc.add_list(keyname,elm);
							break; 
						}				

			/*//timestamp
			case '\x11':{	
							//element elm(read_uint64(parsed_doc,pos)); 
							elm = new timestamp_element(read_uint64(parsed_doc,pos));
							doc.add_list(keyname,elm);
							break; 
						}*/	

			//int64
			case '\x12':{	
							//element elm(read_int64(parsed_doc,pos), _INT64_); 
							elm = new int64_element(read_int64(parsed_doc,pos));
							doc.add_list(keyname,elm);
							break; 
						}

			/*case '\xFF':{	
							element elm(MIN_KEY); 
							doc.add_list(keyname,elm);
							break; 
						}

			case '\x7F':{	
							element elm(MAX_KEY); 
							doc.add_list(keyname,elm);
							break; 
						}

/*			//binary data
			case '\x05': 	
			
			//regex
			case '\x0B':	

			//DBpointer
			case '\x0C':

			//symbol
			case '\x0E':

			//code_w_s
			case '\x0F':	
						
			//decimal128
			case '\x13':		
*/
		}
	
	}

}



