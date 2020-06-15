/*
 * Copyright (c) 2015 Terry Cain <terry@terrys-home.co.uk>
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#ifndef __HID_RAZER_MOUSE_H
#define __HID_RAZER_MOUSE_H

#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>

bool razer_mouse_attr_write_mode_none(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_mode_custom(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_mode_static(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_logo_led_effect(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_logo_led_rgb(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_mode_wave(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_mode_spectrum(IOUSBDeviceInterface **dev);
bool razer_mouse_attr_write_mode_reactive(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_mode_breath(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_set_charging_effect(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_set_charging_colour(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_matrix_brightness(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_mouse_attr_write_set_low_battery_threshold(IOUSBDeviceInterface **dev, const char *buf, size_t count);

//

bool razer_mouse_attr_write_scroll_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_scroll_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_scroll_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_scroll_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_scroll_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_scroll_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);

bool razer_mouse_attr_write_logo_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_logo_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_logo_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_logo_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_logo_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_logo_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);

bool razer_mouse_attr_write_side_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side);
bool razer_mouse_attr_write_left_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_right_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_side_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side);
bool razer_mouse_attr_write_left_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_right_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_side_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side);
bool razer_mouse_attr_write_left_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_right_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_side_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side);
bool razer_mouse_attr_write_left_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_right_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_side_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side);
bool razer_mouse_attr_write_left_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_right_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_side_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side);
bool razer_mouse_attr_write_left_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);
bool razer_mouse_attr_write_right_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count);

#endif
