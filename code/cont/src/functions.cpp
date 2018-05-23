#include "functions.hpp"

/* Functions */
/* Returns true if file already exists. */
bool fileExists(string &file)
{
        if (FILE *f = fopen(file.c_str(), "r"))
                return true;
        else
                return false;
}
