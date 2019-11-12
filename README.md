This example is pulled from a bigger project to show and debug an error
in the nimble stack from esp.

### Problem

Quick successive calls to gatt notify will crash the system.

### Reproducing

1. Simply build the project like any other esp project. It requires the new xtensa compiler as it uses modern c++ (with gcc-8).

   ```bash
   $IDF_PATH/tools/idf.py build
   $IDF_PATH/tools/idf.py monitor
   ```

2. After starting the monitor you must connect to the device with any BLE capable device.
3. Observe that you will see following line before the crash:

   ```E (882) NimBLE: Controller not ready to receive packets from host at this time, try again after sometime```

A logger in the esp nimble stack greatly reduces the amount of crashes occurring (just takes some seconds instead of immediately).
By the way: Why is there a logger by default? This increases latency A LOT!

To have a very reliable immediate crash, you should disable the logger in
`components/bt/host/nimble/nimble/nimble/host/src/ble_gattc.c` (line 490 on current esp-idf master):

```c
static void
ble_gattc_log_proc_init(const char *name)
{
	//BLE_HS_LOG(INFO, "GATT procedure initiated: %s", name); // <-- DISABLE THIS LINE!
}
```
