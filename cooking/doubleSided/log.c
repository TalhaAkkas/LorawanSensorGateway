// log.cpp; 
 
#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#include <stdarg.h>
 
int LogCreated = 0;

int getLogLineSize(void);
/*
void LogWithFormat(const char* format, ...)
{

    va_list args;
    va_start(args, format);

//    if(priority & PRIO_LOG){
    	char logLine [getLogLineSize()];

    	snprintf(logLine, getLogLineSize(), format, args);
    	Log(logLine);
    	printf("%s", logLine);
    	
//    }

    va_end(args);

}*/
void Log (char *message)
{
	printf(message);
	FILE *file;
 
	if (!LogCreated) {
		file = fopen(LOGFILE, "a");
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
 	
	//if (file)
		//fclose(file);
}
 
void LogErr (char *message)
{
	Log(message);
//	Log("\n");
}

int getLogLineSize()
{
	return  250;
}
