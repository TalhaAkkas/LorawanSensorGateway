
typedef enum {
	PinponMessage,
	TestStartMessage,
	TestAckMessage,
	TestEndMessage,
	TestResultMessage,
	TestSampleMessage,
	ConfigurationMessage,
	ConfigurationAcceptMessage,
	AliveMessage
}MessageType;
typedef enum {
	MessageRecieved,
	MessageCreated,
	TestAckNotRecieved,
	TestAckRecieved,
	TestEndNotRecieved,
	TestEndRecieved,
	TestSampleRecieved,
	IdleForLongTime 
}EventTypes;

char* generatePinponMessage()
{
  char[] data = malloc(sizeof(char) * 30);
  static int index  = 0;
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", PinponMessage, index, tm.tm_hour, tm.tm_min, tm.tm_sec);
  index++;
}
char* generateTestStartMessage(int testId)
{
  char[] data = malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", TestStartMessage, testId, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
char* generateTestAckMessage(int testId)
{
  char[] data = malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", TestAckMessage, testId, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
char* generateTestEndMessage(int testId)
{
  char[] data = malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", TestEndMessage, testId, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
char* generateTestResultMessage(int testId, int isAllInRightOrder, int recievedPacketCount, int totalTimeInSecs)
{
  char[] data = malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", TestEndMessage, testId, isAllInRightOrder, recievedPacketCount, totalTimeInSecs);
}
void didReceivePinponMessage(char* payload)
{
	int messageIndex = atoi(strsep(&payload, "A"));
	int hour = atoi(strsep(&payload, "A"));
	int min = atoi(strsep(&payload, "A"));
	int sec = atoi(strsep(&payload, "A"));

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );

  	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	LogWithFormat("|DidReceivePinPon| index> %d ftime> %d:%d:%d ttime> %d:%d:%d ", messageIndex, hour, min, sec, tm.tm_hour, tm.tm_min, tm.tm_sec);
}
void didRecieveTestStartMessage(char* payload)
{
	int testId = atoi(strsep(&payload, "A"));
	int hour = atoi(strsep(&payload, "A"));
	int min = atoi(strsep(&payload, "A"));
	int sec = atoi(strsep(&payload, "A"));

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );

  	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	LogWithFormat("|DidReceiveTestStart| testId> %d ftime> %d:%d:%d ttime> %d:%d:%d ", testId, hour, min, sec, tm.tm_hour, tm.tm_min, tm.tm_sec);
	FireEvent(TestAckRecieved, testId);
}
void didRecieveTestAckMessage(char* payload)
{
	int testId = atoi(strsep(&payload, "A"));
	int hour = atoi(strsep(&payload, "A"));
	int min = atoi(strsep(&payload, "A"));
	int sec = atoi(strsep(&payload, "A"));

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );

  	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	LogWithFormat("|DidReceiveTestAck| testId> %d ftime> %d:%d:%d ttime> %d:%d:%d ", testId, hour, min, sec, tm.tm_hour, tm.tm_min, tm.tm_sec);
	FireEvent(TestAckRecieved, testId);
}
void didRecieveTestEndMessage(char* payload)
{
	int testId = atoi(strsep(&payload, "A"));
	int hour = atoi(strsep(&payload, "A"));
	int min = atoi(strsep(&payload, "A"));
	int sec = atoi(strsep(&payload, "A"));

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );

  	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	LogWithFormat("|DidReceiveTestAck| testId> %d ftime> %d:%d:%d ttime> %d:%d:%d ", testId, hour, min, sec, tm.tm_hour, tm.tm_min, tm.tm_sec);
	FireEvent(TestEndRecieved, testId);
}
void didRecieveTestSampleMessage(char* payload)
{
	int testId = atoi(strsep(&payload, "A"));
	int testIndex = atoi(strsep(&payload, "A"));
	int hour = atoi(strsep(&payload, "A"));
	int min = atoi(strsep(&payload, "A"));
	int sec = atoi(strsep(&payload, "A"));

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
  	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	LogWithFormat("|DidReceiveTestSample| testId> %d index: %d ftime> %d:%d:%d ttime> %d:%d:%d ", testId, testIndex, hour, min, sec, tm.tm_hour, tm.tm_min, tm.tm_sec);
	FireEvent(TestSampleRecieved, testId, testIndex);
}
void didRecieveTestResultMessage(char* payload)
{
	int testId = atoi(strsep(&payload, "A"));
	int isAllInRightOrder = atoi(strsep(&payload, "A"));
	int recievedPacketCount = atoi(strsep(&payload, "A"));
	int totalTimeInSecs = atoi(strsep(&payload, "A"));

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
  	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
	LogWithFormat("|DidReceiveTestResult| testId> %d rightOrder: %d recievedPacketCount> %d ttime> %d:%d:%d ", testId, isAllInRightOrder, recievedPacketCount, min, sec, tm.tm_hour, tm.tm_min, tm.tm_sec);
	FireEvent(TestResultMessage, testId, testIndex);
}
void processMessage(char* message)
{
	char* typeString = strsep(&stringp, "T");
	MessageType type = atoi(typeString);

	if(type == PinponMessage){
		didRecievePinponMessage(message);
	}else if(type == TestStartMessage){
		didRecieveTestStartMessage(message);
	}else if(type == TestAckMessage){
		didRecieveTestAckMessage(message);
	}else if(type == TestEndMessage){
		didRecieveTestEndMessage(message);
	}else if(type == TestResultMessage){
		didRecieveTestResultMessage(message);
	}else if(type == TestSampleMessage){
		didRecieveTestSampleMessage(message);
	}else if(type == ConfigurationMessage){

	}else if(type == ConfigurationAcceptMessage){

	}else if(type == AliveMessage){

	}
}