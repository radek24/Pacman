#include "Core.h"

int getSpriteIndexFromTime(float time, int sprites)
{
     return ((int)(time * 10) % sprites);
}

int LogErrorCallback(const char* const filename, size_t line_number, size_t column, char* line, Ini_File_Error error)
{
	
	PAC_FATAL("%s:%lu:%lu %s:\n%s\n", filename, line_number, column, ini_file_error_to_string(error), line);
	PAC_ASSERT(0);
	return 0;
	
}
