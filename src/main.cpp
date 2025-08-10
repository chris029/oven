/*

GPIO setup - 6.10.24

ESP32:

Function               |  GPIO
-------------------------------------------
CARTRIDGE_HEATER_RELAY |  GPIO32
DISPLAY (default)      |  GPIO21 (SDA), GPIO22 (SCL)
EXHAUST_FAN PSM_PIN    |  GPIO33
EXHAUST_FAN ZC_PIN     |  GPIO25
PELLET_SPIRAL_RELAY    |  GPIO26
CONTROL_BUTTON         |  GPIO14

*/

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID "47485ae8-4684-407d-b63f-29423b73b115"
#define CHARACTERISTIC_UUID "08c4243d-23e0-426d-9425-73b201a9cc0a"
#define INDICATION_UUID "165138d2-92da-490b-b704-6d26f8e7f5d8"

#include "timer.hpp"
#include "state_machine.hpp"
#include "input_manager.hpp"
#include "operators.hpp"

StateMachine state_machine;
Timer main_timer;
InputManager input_manager(&state_machine);

BLECharacteristic *pCharacteristic = NULL;
BLECharacteristic *pIndCharacteristic = NULL;
BLEService *pService = NULL;

class MyServerCallbacks : public BLEServerCallbacks
{
public:
  void onConnect(BLEServer *pServer)
  {
    Serial.println("Something connected...");
  };
  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("Something disconnected...");
    BLEDevice::startAdvertising();
  }
};

MyServerCallbacks *myServerCallback;

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue();
    std::string commandShort = "shortPenis";
    std::string commandLong = "longPenis";

    Serial.print("something");

    if (rxValue.length() > 0)
    {
      if (rxValue.compare(commandShort) == 0)
      {
        input_manager.SetEventShortButtonPress();
      }
      else if (rxValue.compare(commandLong) == 0)
      {
        input_manager.SetEventLongButtonPress();
      }
      else
      {
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
        {
          Serial.print(rxValue[i]);
        }
        Serial.println();
      }
    }
  }
};

void setup()
{
#if defined(ARDUINO_ARCH_ESP32)
  Serial.begin(921600);
#else
  Serial.begin(115200);
#endif
  BLEDevice::init("Oven");

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());

  pIndCharacteristic = pService->createCharacteristic(
      INDICATION_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE);

  pIndCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  main_timer.SetupTimer();
  state_machine.SetupStateMachine(pIndCharacteristic);
  input_manager.SetupInputManager(pIndCharacteristic);
}

void loop()
{
  main_timer.WaitForTimer();
  input_manager.CheckInputs();
  state_machine.Run();

  std::string selected_state = std::string(state_machine.device_manager.display.GetSelectedState().c_str());
  pIndCharacteristic->setValue("SELECTED" + selected_state);
  pIndCharacteristic->notify();
  pIndCharacteristic->setValue("CURRENT" + state_machine.current_state_label);
  pIndCharacteristic->notify();
}