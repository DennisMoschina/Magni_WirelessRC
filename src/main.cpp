#include <Arduino.h>

#include <BLECommunicator.h>
#include <CommunicatorUI.h>
#include <Communicator.h>
#include <UserInterface.h>
#include <communication.h>
#include <remoteControl.h>

void setup() {
  GlobalTime* time = new GlobalTime();

  BLECommunicator* com = new BLECommunicator(DEVICE_NAME);
  UserInterface* ui = new CommunicatorUI(com);

  RemoteControl* rc = new RemoteControl(*time, *ui);

  com->advertise();
  rc->startControlling();
}

void loop() {
  // Delete this task
  vTaskDelete(NULL);
}