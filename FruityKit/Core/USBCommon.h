//
//  USBCommon.h
//  FruityKit
//
//  Created by Eduardo Almeida on 08/07/18.
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

#ifndef USBCommon_h
#define USBCommon_h

#include <IOKit/usb/IOUSBLib.h>

#include "razercommon.h"

IOReturn perform_razer_usb_call(IOUSBDeviceInterface **dev, void *data, uint report_index);
IOReturn razer_get_report(IOUSBDeviceInterface **dev, struct razer_report *request_report, struct razer_report *response_report);
bool razer_send_payload(IOUSBDeviceInterface **dev, struct razer_report *request_report, struct razer_report *response_report);
UInt16 get_device_id(IOUSBDeviceInterface **dev);

#endif /* USBCommon_h */
