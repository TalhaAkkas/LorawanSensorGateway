
//////////////////////////////////////////////
// Main loop setup() and loop() declarations
//////////////////////////////////////////////
#include "log.h"
#include "demonize.h"
int main (){
	Log("Listener Started")
	setupDeamon();
	Log("Deamon Started");
	radioModuleSetup();
	Log("Lorawan setup");
	while(1){
		loop();
	}
	return (0);
}