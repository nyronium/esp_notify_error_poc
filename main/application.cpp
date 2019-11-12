#include "system.h"
#include "application.h"


int OnMidiPacket(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context) {
	// XXX contrived example, not used.
	return 0;
}


[[noreturn]] void Application::TaskMain(void*) {
	try {
		static Application application{};
		Application::instance = &application;
		application();
	} catch (std::exception& e) {
		abort();
	}
	abort();
}

void Application::StartTask() {
	xTaskHandle taskHandle = nullptr;
	xTaskCreatePinnedToCore(&TaskMain, "BleNotifyErrorApp", 0x10000, nullptr, tskIDLE_PRIORITY + 10, &taskHandle, 1);
	esp_task_wdt_delete(taskHandle);
}


void Application::operator()() {
	while (true) {
		blecfg::midiPacketSend = { 0x80, 0x80, 0x90, 0x05, 0xff, 0x06, 0xff };
		bleInstance.template NotifyAll<blecfg::MidiChrUuid>();
	}
}
