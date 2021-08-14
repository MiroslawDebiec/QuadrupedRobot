#include "SpiffHandler.h"


void SpiffHandler::saveFile(String output_string, String file_name){
    File file = SPIFFS.open(SPIFF_PATH + file_name, FILE_WRITE);
    file.print(output_string); 
    file.close();
}

void SpiffHandler::saveFile(File input_file, String file_name){
    File file_opened = SPIFFS.open(SPIFF_PATH + file_name, FILE_WRITE);
    file_opened.print(input_file); 
    file_opened.close();
}

File SpiffHandler::readFile(String file_name){
    File file = SPIFFS.open(SPIFF_PATH + file_name, FILE_READ);
    return file; 
    file.close();
}
