/**
 * @file usb_keyboard_wrap.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void usb_kb_wrap_init();
void usb_kb_wrap_report(uint8_t* keycode);


#ifdef __cplusplus
}
#endif