//
//  DeviceQuery.h
//  FruityKit
//
//  Created by Eduardo Almeida on 07/07/18.
//  Copyright © 2018 Eduardo Almeida. All rights reserved.
//

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
 * e-mail - Eduardo Almeida <hello [_at_] edr [_dot_] io>
 */

#ifndef DeviceQuery_h
#define DeviceQuery_h

#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>

#include "DeviceQuery+Devices.h"

typedef struct razer_device_r {
    razer_device *devices;
    unsigned int length;
} razer_device_r;

razer_device_r dq_get_device_list(void);

bool dq_check_device_connected(int device_id);

IOUSBDeviceInterface** dq_get_device(int device_id);
void dq_close_device(IOUSBDeviceInterface **device);

#endif /* DeviceQuery_h */
