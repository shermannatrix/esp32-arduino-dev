#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5;	// In seconds
BLEScan *pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
	void onResult(BLEAdvertisedDevice advertisedDevice) {
		Serial.printf("%16s\t%16s\t%5d\n", 
			advertisedDevice.getName().c_str(), 
			advertisedDevice.getAddress().toString().c_str(),
			advertisedDevice.getRSSI());
	}
};

void setup() {
	Serial.begin(115200);
	Serial.println("Scanning...");

	BLEDevice::init("");
	pBLEScan = BLEDevice::getScan();	// create a new scan
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	pBLEScan->setActiveScan(true);	// active scan uses more power, but get results faster
	pBLEScan->setInterval(100);
	pBLEScan->setWindow(99);		// less or equal setInterval value
}

void loop() {
	Serial.println("\n\nDevice Name\t\tAddress\t\t\tRSSI");
	Serial.println("--------------------------------------------------");
	BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
	Serial.print("Devices found:");
	Serial.println(foundDevices.getCount());
	Serial.println("Scan done!");
	pBLEScan->clearResults();		// delete results from BLEScan buffer to release memory
	delay(15000);
}