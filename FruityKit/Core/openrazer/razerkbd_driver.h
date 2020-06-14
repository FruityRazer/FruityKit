/*
 * Copyright (c) 2015 Tim Theede <pez2001@voyagerproject.de>
 *               2015 Terry Cain <terrys-home.co.uk>
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#ifndef __HID_RAZER_KEYBOARD_CHROMA_H
#define __HID_RAZER_KEYBOARD_CHROMA_H

#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>

size_t razer_kbd_attr_read_mode_game(IOUSBDeviceInterface **usb_dev, char *buf);
size_t razer_kbd_attr_write_mode_macro(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_mode_macro_effect(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_read_mode_macro_effect(IOUSBDeviceInterface **usb_dev, char *buf);
size_t razer_kbd_attr_write_mode_pulsate(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_read_mode_pulsate(IOUSBDeviceInterface **usb_dev, char *buf);
size_t razer_kbd_attr_read_tartarus_profile_led_red(IOUSBDeviceInterface **usb_dev, char *buf);
size_t razer_kbd_attr_read_tartarus_profile_led_green(IOUSBDeviceInterface **usb_dev, char *buf);
size_t razer_kbd_attr_read_tartarus_profile_led_blue(IOUSBDeviceInterface **usb_dev, char *buf);
size_t razer_kbd_attr_write_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_mode_spectrum(IOUSBDeviceInterface **usb_dev);
size_t razer_kbd_attr_write_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_mode_starlight(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_set_logo(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_mode_custom(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_set_fn_toggle(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_write_set_brightness(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
size_t razer_kbd_attr_read_set_brightness(IOUSBDeviceInterface **usb_dev, char *buf);
size_t razer_kbd_attr_write_matrix_custom_frame(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);

#endif
