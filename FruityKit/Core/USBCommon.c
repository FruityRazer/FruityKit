//
//  USBCommon.c
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

IOReturn razer_get_report(IOUSBDeviceInterface **dev, struct razer_report *request_report, struct razer_report *response_report) {
    return razer_get_usb_response(dev, 0x00, request_report, 0x00, response_report);
}

bool razer_send_payload(IOUSBDeviceInterface **dev, struct razer_report *request_report) {
    return razer_send_payload3(dev, request_report, NULL);
}

bool razer_send_payload3(IOUSBDeviceInterface **dev, struct razer_report *request_report, struct razer_report *response_report) {
    IOReturn retval = -1;
    
    struct razer_report *loc_response_report = (struct razer_report *)malloc(sizeof(struct razer_report));
    memset(loc_response_report, 0, sizeof(struct razer_report));
    
    request_report->crc = razer_calculate_crc(request_report);
    
    retval = razer_get_report(dev, request_report, loc_response_report);
    
    if (retval == kIOReturnSuccess) {
        // Check the packet number, class and command are the same
        if(request_report->remaining_packets != loc_response_report->remaining_packets ||
           request_report->command_class != loc_response_report->command_class ||
           request_report->command_id.id != loc_response_report->command_id.id) {
            return false;
        } else if (loc_response_report->status == RAZER_CMD_FAILURE) {
            return false;
        } else if (loc_response_report->status == RAZER_CMD_NOT_SUPPORTED) {
            return false;
        } else if (loc_response_report->status == RAZER_CMD_TIMEOUT) {
            return false;
        }
    } else {
        return false;
    }
    
    if (response_report != NULL) {
        response_report = loc_response_report;
    } else {
        free(loc_response_report);
    }
    
    return true;
}

UInt16 get_device_id(IOUSBDeviceInterface **dev) {
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    return product;
}
