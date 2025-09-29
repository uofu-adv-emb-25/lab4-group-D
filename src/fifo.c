#include <stdio.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <pico/stdlib.h>
#include <pico/cyw43_arch.h>
#include <unity.h>

struct request_msg {
    int32_t input;
    int32_t output;
    uint32_t handled_by;
};

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id) {
    // keep helping
    while(1) {
        // read the input
        struct request_msg reqBuf;
        xQueueReceive(requests, &reqBuf, portMAX_DELAY);

        // calculate
        reqBuf.output = reqBuf.input + 5;
        reqBuf.handled_by = id;

        // send the output
        xQueueSend(results, &reqBuf, portMAX_DELAY);
    }
}
