//
//  RazerSoftwareChroma.h
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

#ifndef RazerSoftwareChroma_h
#define RazerSoftwareChroma_h

#include <IOKit/usb/IOUSBLib.h>

#include "razercommon.h"

IOReturn razer_huntsman_set_row_raw(IOUSBDeviceInterface **dev, char row_number, char *keys, int len);
IOReturn razer_huntsman_set_static_color(IOUSBDeviceInterface **dev, char row_number, struct razer_rgb *rgb);
IOReturn razer_huntsman_fake_wave_one_run(IOUSBDeviceInterface **dev, struct razer_rgb *rgb);

IOReturn razer_base_station_pre(IOUSBDeviceInterface **dev);
IOReturn razer_base_station_set_static_color(IOUSBDeviceInterface **dev, struct razer_rgb *rgb);
IOReturn razer_base_station_set_colors(IOUSBDeviceInterface **dev, char *parts);

IOReturn razer_hyperflux_set_colors(IOUSBDeviceInterface **dev, char *parts);

#endif /* RazerSoftwareChroma_h */
