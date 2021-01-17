/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * Should you need to contact me, the author, you can do so by
 * e-mail - mail your message to Terry Cain <terry@terrys-home.co.uk>
 */

#ifndef razeraccessory_driver_h
#define razeraccessory_driver_h

#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>

bool razer_accessory_attr_write_mode_none(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_accessory_attr_write_mode_custom(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_accessory_attr_write_mode_static(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_accessory_attr_write_mode_wave(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_accessory_attr_write_mode_spectrum(IOUSBDeviceInterface **dev);
bool razer_accessory_attr_write_mode_reactive(IOUSBDeviceInterface **dev, const char *buf, size_t count);
bool razer_accessory_attr_write_mode_breath(IOUSBDeviceInterface **dev, const char *buf, size_t count);

#endif /* razeraccessory_driver_h */
