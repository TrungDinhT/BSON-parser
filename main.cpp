
#include "document.h"

int main(int argc, char* argv[]){

	/*
	*Create path to file for parsing
	*/
	std::string path("samples/");
	path+=std::string (argv[1]); 	

	std::ifstream file(path);

    if (file)
    {
        std::cout<<"path file: "<<path<<std::endl;
        /*
         * Get the size of the file
         */
        file.seekg(0,std::ios::end);
        std::streampos length = file.tellg();
        file.seekg(0,std::ios::beg);

        /*
         * Use a vector as the buffer.
         * Then read the whole file into the buffer.
         */
        std::vector<char> buffer(length);
        file.read(&buffer[0],length); 


        /*
        *fetch, parse and then print out as human readable format
        */
        document doc(buffer);
        parse(doc,buffer);
        doc.dump(std::cout);

	}


	return 0;	
}


