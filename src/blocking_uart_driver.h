/*
Copyright (c) 2014-2015, Club Vaudois de Robotique Autonome (CVRA) All rights
reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef BLOCKING_UART_DRIVER_H
#define BLOCKING_UART_DRIVER_H

#include <ch.h>
#include <hal.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const struct BaseSequentialStreamVMT blocking_uart_put_vmt;

typedef struct {
    const struct BaseSequentialStreamVMT *vmt;
    USART_TypeDef *dev;
} BlockingUARTDriver;

msg_t blocking_uart_put(void *instance, uint8_t b);
msg_t blocking_uart_get(void *instance);
size_t blocking_uart_write(void *instance, const uint8_t *bp, size_t n);
size_t blocking_uart_read(void *instance, uint8_t *bp, size_t n);

void blocking_uart_init(BlockingUARTDriver *driver, USART_TypeDef *uart, uint32_t baud);

#ifdef __cplusplus
}
#endif

#endif /* BLOCKING_UART_DRIVER_H */
