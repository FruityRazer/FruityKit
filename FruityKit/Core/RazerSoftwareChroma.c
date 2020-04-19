//
//  RazerSoftwareChroma.c
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

#include "RazerSoftwareChroma.h"

#include "USBCommon.h"

IOReturn razer_huntsman_set_row_raw(IOUSBDeviceInterface **dev, char row_number, char *keys, int len) {
    struct razer_report report = get_razer_report(0x1f, 0x0f, 0x03, 0x4a);

    report.arguments[0] = 0x00;
    report.arguments[1] = 0x00;
    report.arguments[2] = row_number;
    report.arguments[3] = 0x00;
    report.arguments[4] = 0x16;

    int key_count = len;

    for (int i = 0; i <= key_count; i++) {
        int key = (i * 3);

        report.arguments[5 + key + 0] = keys[key + 0];
        report.arguments[5 + key + 1] = keys[key + 1];
        report.arguments[5 + key + 2] = keys[key + 2];
    }

    report.crc = razer_calculate_crc(&report);

    return perform_razer_usb_call(dev, &report, 0x02);
}

IOReturn razer_huntsman_set_static_color(IOUSBDeviceInterface **dev, char row_number, struct razer_rgb *rgb) {
    struct razer_report report = get_razer_report(0x1f, 0x0f, 0x03, 0x4a);
    
    report.arguments[0] = 0x00;
    report.arguments[1] = 0x00;
    report.arguments[2] = row_number;
    report.arguments[3] = 0x00;
    report.arguments[4] = 0x16;
    
    int keys = 25;
    
    for (int i = 0; i <= keys; i++) {
        int key = (i * 3);
        
        report.arguments[5 + key + 0] = rgb->r;
        report.arguments[5 + key + 1] = rgb->g;
        report.arguments[5 + key + 2] = rgb->b;
    }
    
    report.crc = razer_calculate_crc(&report);
    
    return perform_razer_usb_call(dev, &report, 0x02);
}

IOReturn razer_huntsman_fake_wave_one_run(IOUSBDeviceInterface **dev, struct razer_rgb *rgb) {
    for (int current_key = 0; current_key <= 25; current_key++) {
        for (char row = 0x00; row < 6; row++) {
            struct razer_report report = get_razer_report(0x1f, 0x0f, 0x03, 0x4a);
            
            report.arguments[0] = 0x00;
            report.arguments[1] = 0x00;
            report.arguments[2] = row;
            report.arguments[3] = 0x00;
            report.arguments[4] = 0x16;
            
            report.arguments[5 + (current_key * 3) + 0] = rgb->r;
            report.arguments[5 + (current_key * 3) + 1] = rgb->g;
            report.arguments[5 + (current_key * 3) + 2] = rgb->b;
            
            report.crc = razer_calculate_crc(&report);
            
            perform_razer_usb_call(dev, &report, 0x02);
        }
        
        usleep(100000);
    }
    
    return (IOReturn) 0;
}

IOReturn razer_base_station_pre(IOUSBDeviceInterface **dev) {
    {
        struct razer_report report = get_razer_report(0x1f, 0x00, 0x00, 0x00);
        
        ((char *) &report)[5] = 0x02;
        ((char *) &report)[7] = 0x84;
        
        report.crc = razer_calculate_crc(&report);
        
        perform_razer_usb_call(dev, &report, 0x02);
    }
    
    usleep(100000);
    
    {
        struct razer_report report = get_razer_report(0x1f, 0x00, 0x00, 0x00);
        
        ((char *) &report)[5] = 0x02;
        ((char *) &report)[7] = 0x04;
        ((char *) &report)[8] = 0x03;
        
        report.crc = razer_calculate_crc(&report);
        
        perform_razer_usb_call(dev, &report, 0x02);
    }
    
    usleep(100000);
    
    {
        struct razer_report report = get_razer_report(0x1f, 0x00, 0x00, 0x00);
        
        ((char *) &report)[5] = 0x06;
        ((char *) &report)[6] = 0x0f;
        ((char *) &report)[7] = 0x02;
        ((char *) &report)[10] = 0x08;
        ((char *) &report)[12] = 0x01;
        
        report.crc = razer_calculate_crc(&report);
        
        perform_razer_usb_call(dev, &report, 0x02);
    }
    
    usleep(100000);
    
    return (IOReturn) 0;
}

IOReturn razer_base_station_set_static_color(IOUSBDeviceInterface **dev, struct razer_rgb *rgb) {
    struct razer_report report = get_razer_report(0x1f, 0x0f, 0x03, 0x32);
    
    report.arguments[0] = 0x00;
    report.arguments[1] = 0x00;
    report.arguments[2] = 0x00;
    report.arguments[3] = 0x00;
    report.arguments[4] = 0x0e;
    
    for (int i = 0; i <= 14; i++) {
        int part = (i * 3);
        
        report.arguments[5 + part + 0] = rgb->r;
        report.arguments[5 + part + 1] = rgb->g;
        report.arguments[5 + part + 2] = rgb->b;
    }
    
    report.crc = razer_calculate_crc(&report);
    
    return perform_razer_usb_call(dev, &report, 0x00);
}

IOReturn razer_base_station_set_colors(IOUSBDeviceInterface **dev, char *parts) {
    struct razer_report report = get_razer_report(0x1f, 0x0f, 0x03, 0x32);
    
    report.arguments[0] = 0x00;
    report.arguments[1] = 0x00;
    report.arguments[2] = 0x00;
    report.arguments[3] = 0x00;
    report.arguments[4] = 0x0e;
    
    for (int i = 0; i <= 14; i++) {
        int part = (i * 3);
        
        report.arguments[5 + part + 0] = parts[part + 0];
        report.arguments[5 + part + 1] = parts[part + 1];
        report.arguments[5 + part + 2] = parts[part + 2];
    }
    
    report.crc = razer_calculate_crc(&report);
    
    return perform_razer_usb_call(dev, &report, 0x00);
}

IOReturn razer_hyperflux_set_colors(IOUSBDeviceInterface **dev, char *parts) {
    struct razer_report report = get_razer_report(0x1f, 0x0f, 0x03, 0x38);
    
    report.arguments[0] = 0x00;
    report.arguments[1] = 0x00;
    report.arguments[2] = 0x00;
    report.arguments[3] = 0x00;
    report.arguments[4] = 0x10;
    
    for (int i = 0; i <= 14; i++) {
        int part = (i * 3);
        
        report.arguments[5 + part + 0] = parts[part + 0];
        report.arguments[5 + part + 1] = parts[part + 1];
        report.arguments[5 + part + 2] = parts[part + 2];
    }
    
    report.crc = razer_calculate_crc(&report);
    
    return perform_razer_usb_call(dev, &report, 0x00);
}
