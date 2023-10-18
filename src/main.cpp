#include <Arduino.h>

#include <config.h>
#include <BLECommunicator.h>
#include <CommunicatorUI.h>
#include <Communicator.h>
#include <UserInterface.h>
#include <communication.h>
#include <remoteControl.h>

void setup() {
  GlobalTime* time = new GlobalTime();

  BLECommunicator* bleCom = new BLECommunicator(DEVICE_NAME);
  UserInterface* ui = new CommunicatorUI(bleCom);

  Communication* com = new Communication();

  RemoteControl* rc = new RemoteControl(*time, *ui, *com);

  bleCom->advertise();
  rc->startControlling();
}

void loop() {
  // Delete this task
  vTaskDelete(NULL);
}