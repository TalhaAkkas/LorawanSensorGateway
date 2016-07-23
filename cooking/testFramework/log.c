// log.cpp; 
 
#include <stdlib.h>
#include <stdio.h>
#include "log.h"
 
int LogCreated = 0;

void LogWithFormat(const char* format, ...)
{

    va_list args;
    va_start(args, format);

    if(priority & PRIO_LOG){
    	char[] logLine = malloc(sizeof(char) * getLogLineSize());

    	snprintf(logLine, getLogLineSize(), format args);
    	Log(logLine);

		free(logLine);
    }

    va_end(args);

}
void Log (char *message)
{
	FILE *file;
 
	if (!LogCreated) {
		file = fopen(LOGFILE, "w");
		LogCreated = 1;
	}
	else		
		file = fopen(LOGFILE, "a");
		
	if (file == NULL) {
		if (LogCreated)
			LogCreated = 1;
		return;
	}
	else
	{
		fputs(message, file);
		fclose(file);
	}
 	
	if (file)
		fclose(file);
}
 
void LogErr (char *message)
{
	Log(message);
	Log("\n");
}

int getLogLineSize()
{
	return  250;
}