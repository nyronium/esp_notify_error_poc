#include "system.h"
#include "application.h"

extern "C" {
	void app_main();
}

void app_main() {
	if (nvs_flash_init() != ESP_OK) {
		esp::check(nvs_flash_erase(), "nvs_flash_erase()");
		esp::check(nvs_flash_init(), "nvs_flash_init()");
	}

	Application::StartTask();

	// Delete this initial task
	vTaskDelete(nullptr);
}
