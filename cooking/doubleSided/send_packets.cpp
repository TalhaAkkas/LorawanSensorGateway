/*  
 *  ------ P2P Code Example -------- 
 *  
 *  Explanation: This example shows how to configure the module
 *  for P2P mode and the corresponding parameters. After this, 
 *  the example shows how to send packets to other radio modules
 *  which must be set with the same radio settings
 *  
 *  Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify  
 *  it under the terms of the GNU General Public License as published by  
 *  the Free Software Foundation, either version 3 of the License, or  
 *  (at your option) any later version.  
 *   
 *  This program is distributed in the hope that it will be useful,  
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of  
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
 *  GNU General Public License for more details.  
 *   
 *  You should have received a copy of the GNU General Public License  
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 *  Version:           0.3
 *  Design:            David Gascon
 *  Implementation:    Luismi Marti, Ruben Martin  
 */

#include "arduPiLoRaWAN.h"
#include "log.h"
#include <stdio.h>      /* puts, printf */
#include <time.h>  


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


// socket to use
//////////////////////////////////////////////
uint8_t sock = SOCKET0;
//////////////////////////////////////////////

// define radio settings
//////////////////////////////////////////////
uint8_t power = 15;
uint32_t frequency = 868100000;
char spreading_factor[] = "sf12";
char coding_rate[] = "4/5";
uint16_t bandwidth = 125;
char crc_mode[] = "on";
int delayTime = 100;
int testId = 0;
//////////////////////////////////////////////

// define functions
uint8_t radioModuleSetup(void);

// define data to send
char dataPayload[31];

// variable
uint8_t error;


void setup() 
{
  printf("Radio P2P example - Sending packets\n\n");

  // module setup
  error = radioModuleSetup();
  
  // Check status
  if (error == 0)
  {
    printf("Module configured OK\n");     
  }
  else 
  {
    printf("Module configured ERROR\n");     
  }  

}

/***********************************************************************************
*
* radioModuleSetup()
*
*   This function includes all functions related to the module setup and configuration
*   The user must keep in mind that each time the module powers on, all settings are set
*   to default values. So it is better to develop a specific function including all steps
*   for setup and call it everytime the module powers on.
*
*
***********************************************************************************/
uint8_t radioModuleSetup()
{ 
  uint8_t status = 0;
  uint8_t e = 0;
  
  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////

  e = LoRaWAN.ON(sock);

  // Check status
  if (e == 0)
  {
    printf("1. Switch ON OK\n");     
  }
  else 
  {
    printf("1. Switch ON error = %d\n",e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 2. Enable P2P mode
  //////////////////////////////////////////////

  e = LoRaWAN.macPause();

  // Check status
  if (e == 0)
  {
    printf("2. P2P mode enabled OK\n");
  }
  else 
  {
    printf("2. Enable P2P mode error = %d\n", e);
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 3. Set/Get Radio Power
  //////////////////////////////////////////////

  // Set power
  e = LoRaWAN.setRadioPower(power);

  // Check status
  if (e == 0)
  {
    printf("3.1. Set Radio Power OK\n");
  }
  else 
  {
    printf("3.1. Set Radio Power error = %d\n", e);
    status = 1;
  }

  // Get power
  e = LoRaWAN.getRadioPower();

  // Check status
  if (e == 0) 
  {
    printf("3.2. Get Radio Power OK. "); 
    printf("Power: %d\n",LoRaWAN._radioPower);
  }
  else 
  {
    printf("3.2. Get Radio Power error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 4. Set/Get Radio Frequency
  //////////////////////////////////////////////

  // Set frequency
  e = LoRaWAN.setRadioFreq(frequency);

  // Check status
  if (e == 0)
  {
    printf("4.1. Set Radio Frequency OK\n");
  }
  else 
  {
    printf("4.1. Set Radio Frequency error = %d\n", error);
    status = 1;
  }

  // Get frequency
  e = LoRaWAN.getRadioFreq();

  // Check status
  if (e == 0) 
  {
    printf("4.2. Get Radio Frequency OK. "); 
    printf("Frequency: %d\n", LoRaWAN._radioFreq);
  }
  else 
  {
    printf("4.2. Get Radio Frequency error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 5. Set/Get Radio Spreading Factor (SF)
  //////////////////////////////////////////////

  // Set SF
  e = LoRaWAN.setRadioSF(spreading_factor);

  // Check status
  if (e == 0)
  {
    printf("5.1. Set Radio SF OK\n");
  }
  else 
  {
    printf("5.1. Set Radio SF error = %e\n", e);
    status = 1;
  }

  // Get SF
  e = LoRaWAN.getRadioSF();

  // Check status
  if (e == 0) 
  {
    printf("5.2. Get Radio SF OK. "); 
    printf("Spreading Factor: %s\n", LoRaWAN._radioSF);
  }
  else 
  {
    printf("5.2. Get Radio SF error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 6. Set/Get Radio Coding Rate (CR)
  //////////////////////////////////////////////

  // Set CR
  e = LoRaWAN.setRadioCR(coding_rate);

  // Check status
  if (e == 0)
  {
    printf("6.1. Set Radio CR OK\n");
  }
  else 
  {
    printf("6.1. Set Radio CR error = %d\n", e);
    status = 1;
  }

  // Get CR
  e = LoRaWAN.getRadioCR();

  // Check status
  if (e == 0) 
  {
    printf("6.2. Get Radio CR OK. "); 
    printf("Coding Rate: %s\n",LoRaWAN._radioCR);
  }
  else 
  {
    printf("6.2. Get Radio CR error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 7. Set/Get Radio Bandwidth (BW)
  //////////////////////////////////////////////

  // Set BW
  e = LoRaWAN.setRadioBW(bandwidth);

  // Check status
  if (e == 0)
  {
    printf("7.1. Set Radio BW OK\n");
  }
  else 
  {
    printf("7.1. Set Radio BW error = %d\n", e);
  }

  // Get BW
  e = LoRaWAN.getRadioBW();

  // Check status
  if (e == 0) 
  {
    printf("7.2. Get Radio BW OK. "); 
    printf("Bandwidth: %u\n", LoRaWAN._radioBW);
  }
  else 
  {
    printf("7.2. Get Radio BW error = %d\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");



  //////////////////////////////////////////////
  // 8. Set/Get Radio CRC mode
  //////////////////////////////////////////////

  // Set CRC
  e = LoRaWAN.setRadioCRC(crc_mode);

  // Check status
  if (e == 0)
  {
    printf("8.1. Set Radio CRC mode OK\n");
  }
  else 
  {
    printf("8.1. Set Radio CRC mode error = %d\n", e);
    status = 1;
  }

  // Get CRC
  e = LoRaWAN.getRadioCRC();

  // Check status
  if (e == 0) 
  {
    printf("8.2. Get Radio CRC mode OK. "); 
    printf("CRC status: %u\n",LoRaWAN._crcStatus);
  }
  else 
  {
    printf("8.2. Get Radio CRC mode error = %e\n", e); 
    status = 1;
  }
  printf("-------------------------------------------------------\n");


  return status;
}

char* generateTestStartMessage(int testId)
{
  char* data = (char*) malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", TestStartMessage, testId, tm.tm_hour, tm.tm_min, tm.tm_sec);
  return data;
}
char* generateTestEndMessage(int testId)
{
  char* data = (char*) malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", TestEndMessage, testId, tm.tm_hour, tm.tm_min, tm.tm_sec);
  return data;
}
char* generateTestResultMessage(int testId, int isAllInRightOrder, int recievedPacketCount, int totalTimeInSecs)
{
  char* data = (char*) malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA", TestEndMessage, testId, isAllInRightOrder, recievedPacketCount, totalTimeInSecs);
  return data;
}
char* generateTestSampleMessage(int testId, int testIndex)
{
  char* data = (char*) malloc(sizeof(char) * 30);
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  
  sprintf(data, "%dT%dA%dA%dA%dA%dA", TestStartMessage, testId, testIndex, tm.tm_hour, tm.tm_min, tm.tm_sec);
  return data;
}
void setupArguments(int argc, char *argv[]){
 
  power = atoi(argv[1]);
  //frequency = atoi(argv[2]);
  strcpy(spreading_factor, argv[3]);
  strcpy(coding_rate, argv[4]);
  bandwidth = atoi(argv[5]);
  strcpy(crc_mode, argv[6]);
  delayTime = atoi(argv[7]);
  testId = atoi(argv[8]);

  char logLine [getLogLineSize()];
  snprintf(logLine, getLogLineSize(), "|SETCONFIG| p %d, f %d, sf %s, cr %s, bw %d, crc %s, dt %d, testId %d \n", power, frequency, spreading_factor, coding_rate, bandwidth, crc_mode, delayTime, testId);
  Log(logLine);
}
//////////////////////////////////////////////
// Main loop setup() and loop() declarations
//////////////////////////////////////////////


static int call = 0;
void loop() 
{
  // Send packet
  char* data; 
  if(call == 0){
    data = generateTestStartMessage(testId);
  }else if (call < 21){
    data = generateTestSampleMessage(testId, call - 1);
  }else if(call == 22){
    data = generateTestEndMessage(testId);
  }else{
    exit(0);
  }
  printf("%s\n",data);

  sprintf(dataPayload, "%-30s", data);
  error = LoRaWAN.sendRadio(dataPayload);
  
  // Check status
  if (error == 0)
  {
    printf("--> Packet sent OK\n");
  }
  else 
  {
    printf("Error sending packets. error = %d\n", error);  
  }
  
  delay(delayTime);
  call++;
}

int main (int argc, char *argv[])
{
  setupArguments(argc, argv);
	setup();
	while(1){
		loop();
	}
	return (0);
}

