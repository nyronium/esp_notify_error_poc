#pragma once

#include "ble_instance.h"

#include <memory>


int OnMidiPacket(uint16_t connHandle, uint16_t attrHandle, ble_gatt_access_ctxt* context);


namespace blecfg {

inline ble::Array<64> midiPacketSend{};

using namespace ble;
namespace chr = ble::characteristic_options;
namespace svr = ble::server_options;

using MidiSvcUuid = Uuid128<0x03b80e5a, 0xede8, 0x4b33, 0xa751, 0x6ce34ec4c700>;
using MidiChrUuid = Uuid128<0x7772e5db, 0x3868, 0x4112, 0xa1a9, 0xf2669d106bf3>;

using MidiService = Service
	< MidiSvcUuid
	, Characteristic
		< MidiChrUuid
		, chr::BindSendArray<&midiPacketSend>
		, chr::WriteCallback<&OnMidiPacket>
		, chr::Notify
		, chr::WriteNoResponse
		>
	>;

using Server = ble::Server
	< MidiService
	, svr::AdvertiseUuid<MidiService::Uuid>
	>;

} // namespace blecfg


class Application {
public:
	inline static Application* instance = nullptr;

public:
	Application() = default;

	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

public:
	/**
	 * The main function for the application task.
	 */
	[[noreturn]] static void TaskMain(void*);

	/**
	 * Starts a new task for the application
	 */
	static void StartTask();

public:
	void operator()();

private:
	ble::Instance<blecfg::Server> bleInstance{"BNEA"};
};
