#include "parser.h"

int main(int argc, char* argv[]){

	/*
	*Create path to file for parsing
	*/
	char path[] = "samples/";
	strcat(path,argv[1]); 
	

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



		 /*Constructor BSON*/
	    BSON parser(buffer);
	    
	    /* Parse the file */
	    parser.Parse();

	    /*Print the content in format readable*/
	    parser.Dump();
    
	}


	return 0;	
}


