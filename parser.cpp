
#include "document.h"

/* Unknown data types (that will be dumped into hexa) haven't been treated
*  Array data type hasn't been treated
*/




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
	
	for (unsigned int i=0; i<data_size; ++i) { 
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

	//return read_cstring(v,pos);
}


std::vector<char> read_embedded_doc(std::vector<char> v, unsigned int pos){

	//read length of embedded document
	unsigned int doc_len = read_int32(v,pos);

	//reset the position at the beginning of embedded document
	pos-=4; 

	//read embedded document part into a new vector char 
	std::vector<char> res(iterate_and_get(v,pos,doc_len)); 

	return res;
}


static unsigned int pos = 0;

void parse(document& doc, const std::vector<char>& to_parse){

	pos+=4; // start after first 4 bytes of document's length

	static std::string keyname; 

	static unsigned int indicator;

	while (to_parse[pos]!='\x00'){

		indicator = pos;

		//go to the begin of keyname encoded
		pos++; 
		static element* elm;
		document* emb_doc;

		//read keyname and add into vector of ordered keys
		keyname = read_cstring(to_parse,pos);

		switch(to_parse[indicator]){

			//double
			case '\x01':{							
							elm = new double_element(read_double(to_parse,pos),DOUBLE);
							break; 
						}

			//string UTF-8
			case '\x02':{	 
							elm = new string_element(read_string(to_parse,pos), STRING);
							break; 
						}
			
			//array
			//case '\x04': 

			//document embedded
			case '\x03':{	
							std::vector<char> emb(read_embedded_doc(to_parse,pos));
							emb_doc = new document(emb);
							elm = new embedded_document(emb_doc,DOCUMENT);							
							break; 
						}

			//undefine value
			case '\x06':{	
							elm = new element(UNDEFINED);
							break; 
						}

			//ObjectID
			case '\x07':{	
							elm = new string_element(read_objectId(to_parse,pos), OBJECT_ID);
							break; 
						}

			//Boolean
			case '\x08':{	
							elm = new bool_element(read_bool(to_parse,pos), _BOOL_);
							break; 
						}

			//UTC datetime
			case '\x09':{	
							elm = new int64_element(read_int64(to_parse,pos), UTC_TIME);
							break; 
						}

			//null value
			case '\x0A':{	
							elm = new element(_NULL_);
							break; 
						}

			//JScode
			case '\x0D':{	
							elm = new string_element(read_string(to_parse,pos), JSCODE);
							break;
						}

			//int32
			case '\x10':{	
							elm = new int32_element(read_int32(to_parse,pos), _INT32_);
							break; 
						}				

			//timestamp
			case '\x11':{	
							elm = new timestamp(read_uint64(to_parse,pos), TIMESTAMP);
							break; 
						}

			//int64
			case '\x12':{	
							elm = new int64_element(read_int64(to_parse,pos), _INT64_);
							break; 
						}

			//min key
			case '\xFF':{	
							elm = new element(MIN_KEY);
							break; 
						}

			//max key
			case '\x7F':{	
							elm = new element(MAX_KEY);
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

		doc.add_list(keyname,elm);

		if (to_parse[indicator]=='\x03') {parse(*emb_doc, to_parse);}
	
	}

}



