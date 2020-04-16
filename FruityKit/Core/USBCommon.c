//
//  USBCommon.c
//  fruityrazer
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

#include "USBCommon.h"

#include "razercommon.h"

IOReturn perform_razer_usb_call(IOUSBDeviceInterface **dev, void *data, uint report_index) {
    IOReturn retval;
    
    IOUSBDevRequest request;
    
    request.bRequest = HID_REQ_SET_REPORT;
    request.bmRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_OUT;
    request.wValue = 0x0300;
    request.wIndex = report_index;
    request.wLength = RAZER_USB_REPORT_LEN;
    request.pData = data;
    
    retval = (*dev)->DeviceRequest(dev, &request);
    
    if (retval != kIOReturnSuccess)
        printf("Razer USB call failed!\n");
    
    return retval;
}
