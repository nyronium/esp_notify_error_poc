#pragma GCC system_header

#include <cstdint>

#include <host/ble_uuid.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <os/os_mbuf.h>
#include <nvs_flash.h>
#include <nvs_flash.h>

#include <esp_err.h>
#include <esp_nimble_hci.h>
#include <esp_timer.h>
#include <esp_task_wdt.h>

#include <nimble/nimble_port.h>
#include <nimble/nimble_port_freertos.h>

#include <host/ble_hs.h>
#include <host/ble_uuid.h>
#include <host/ble_gap.h>
#include <host/ble_gatt.h>
#include <host/util/util.h>

#include <services/gap/ble_svc_gap.h>
#include <services/gatt/ble_svc_gatt.h>

#undef min
#undef max


namespace esp {

template<typename... Args>
inline void check(esp_err_t error, const char* functionMessage, Args&&... args) {
	if (error != ESP_OK) {
		ESP_LOGE("esp::check", "%s returned with error: %s", functionMessage, esp_err_to_name(error));
	}
}

} // namespace esp
