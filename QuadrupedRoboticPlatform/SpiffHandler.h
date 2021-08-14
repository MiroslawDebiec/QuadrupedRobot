#pragma once
#include <SPIFFS.h>

#define SPIFF_PATH "/data/"

class SpiffHandler
{
    public: 
        static File readFile(String file_name);
        static void saveFile(File file, String file_name);
        static void saveFile(String output_string, String file_name);
    private:
        
};
