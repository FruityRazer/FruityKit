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

#include "razeraccessory_driver.h"
#include "razercommon.h"
#include "razerchromacommon.h"

#include "USBCommon.h"
#include "USBDeviceIdentifiers.h"

bool razer_accessory_attr_write_mode_none(IOUSBDeviceInterface **dev, const char *buf, size_t count) {
    return false;
}

bool razer_accessory_attr_write_mode_custom(IOUSBDeviceInterface **dev, const char *buf, size_t count) {
    return false;
}

bool razer_accessory_attr_write_mode_static(IOUSBDeviceInterface **dev, const char *buf, size_t count) {
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    if (count == 3) {
        switch (product) {
            case USB_DEVICE_ID_RAZER_FIREFLY:
            case USB_DEVICE_ID_RAZER_CORE:
            case USB_DEVICE_ID_RAZER_CHROMA_MUG:
                report = razer_chroma_standard_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*) & buf[0]);
                report.transaction_id.id = 0x3F;
                break;
                
            case USB_DEVICE_ID_RAZER_FIREFLY_HYPERFLUX:
            case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA:
            case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA_EXTENDED:
            case USB_DEVICE_ID_RAZER_CHROMA_HDK:
            case USB_DEVICE_ID_RAZER_CHROMA_BASE:
            case USB_DEVICE_ID_RAZER_NOMMO_PRO:
            case USB_DEVICE_ID_RAZER_NOMMO_CHROMA:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, ZERO_LED, (struct razer_rgb*) & buf[0]);
                report.transaction_id.id = 0x3F;
                break;
                
            case USB_DEVICE_ID_RAZER_KRAKEN_KITTY_EDITION:
            case USB_DEVICE_ID_RAZER_MOUSE_BUNGEE_V3_CHROMA:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, ZERO_LED, (struct razer_rgb*) & buf[0]);
                report.transaction_id.id = 0x1F;
                break;
                
            default:
                return false;
        }
    } else {
        return false;
    }
    
    return razer_send_payload(dev, &report);
}

bool razer_accessory_attr_write_mode_wave(IOUSBDeviceInterface **dev, const char *buf, size_t count) {
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    unsigned char direction = (unsigned char)strtol(buf, NULL, 10);
    
    switch (product) {
        case USB_DEVICE_ID_RAZER_FIREFLY:
        case USB_DEVICE_ID_RAZER_CORE:
        case USB_DEVICE_ID_RAZER_CHROMA_MUG:
            report = razer_chroma_standard_matrix_effect_wave(VARSTORE, BACKLIGHT_LED, direction);
            report.transaction_id.id = 0x3F;
            break;
            
        case USB_DEVICE_ID_RAZER_FIREFLY_HYPERFLUX:
        case USB_DEVICE_ID_RAZER_CHROMA_HDK:
        case USB_DEVICE_ID_RAZER_CHROMA_BASE:
        case USB_DEVICE_ID_RAZER_NOMMO_PRO:
        case USB_DEVICE_ID_RAZER_NOMMO_CHROMA:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, ZERO_LED, direction);
            report.transaction_id.id = 0x3F;
            break;
            
        case USB_DEVICE_ID_RAZER_MOUSE_BUNGEE_V3_CHROMA:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, ZERO_LED, direction);
            report.transaction_id.id = 0x1F;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(dev, &report);
}

bool razer_accessory_attr_write_mode_spectrum(IOUSBDeviceInterface **dev) {
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    switch (product) {
        case USB_DEVICE_ID_RAZER_FIREFLY:
        case USB_DEVICE_ID_RAZER_CORE:
        case USB_DEVICE_ID_RAZER_CHROMA_MUG:
            report = razer_chroma_standard_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            report.transaction_id.id = 0x3F;
            break;
            
        case USB_DEVICE_ID_RAZER_FIREFLY_HYPERFLUX:
        case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA:
        case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA_EXTENDED:
        case USB_DEVICE_ID_RAZER_CHROMA_HDK:
        case USB_DEVICE_ID_RAZER_CHROMA_BASE:
        case USB_DEVICE_ID_RAZER_NOMMO_PRO:
        case USB_DEVICE_ID_RAZER_NOMMO_CHROMA:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, ZERO_LED);
            report.transaction_id.id = 0x3F;
            break;
            
        case USB_DEVICE_ID_RAZER_MOUSE_BUNGEE_V3_CHROMA:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, ZERO_LED);
            report.transaction_id.id = 0x1F;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(dev, &report);
}

bool razer_accessory_attr_write_mode_reactive(IOUSBDeviceInterface **dev, const char *buf, size_t count) {
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    if (count == 4) {
        unsigned char speed = (unsigned char)buf[0];
        
        switch (product) {
            case USB_DEVICE_ID_RAZER_FIREFLY_HYPERFLUX:
            case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA:
            case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA_EXTENDED:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, ZERO_LED, speed, (struct razer_rgb *)&buf[1]);
                break;
                
            case USB_DEVICE_ID_RAZER_FIREFLY:
            case USB_DEVICE_ID_RAZER_CORE:
                report = razer_chroma_standard_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
        }
    } else {
        return false;
    }
    
    return razer_send_payload(dev, &report);
}

bool razer_accessory_attr_write_mode_breath(IOUSBDeviceInterface **dev, const char *buf, size_t count) {
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    switch (product) {
        case USB_DEVICE_ID_RAZER_FIREFLY_HYPERFLUX:
        case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA:
        case USB_DEVICE_ID_RAZER_GOLIATHUS_CHROMA_EXTENDED:
        case USB_DEVICE_ID_RAZER_CHROMA_HDK:
        case USB_DEVICE_ID_RAZER_CHROMA_BASE:
        case USB_DEVICE_ID_RAZER_NOMMO_PRO:
        case USB_DEVICE_ID_RAZER_NOMMO_CHROMA:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, ZERO_LED, (struct razer_rgb *)&buf[0]);
                    report.transaction_id.id = 0x3F;
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, ZERO_LED, (struct razer_rgb *)&buf[0], (struct razer_rgb *)&buf[3]);
                    report.transaction_id.id = 0x3F;
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, ZERO_LED);
                    report.transaction_id.id = 0x3F;
                    break;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_KRAKEN_KITTY_EDITION:
        case USB_DEVICE_ID_RAZER_MOUSE_BUNGEE_V3_CHROMA:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, ZERO_LED, (struct razer_rgb *)&buf[0]);
                    report.transaction_id.id = 0x1F;
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, ZERO_LED, (struct razer_rgb *)&buf[0], (struct razer_rgb *)&buf[3]);
                    report.transaction_id.id = 0x1F;
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, ZERO_LED);
                    report.transaction_id.id = 0x1F;
                    break;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_FIREFLY:
        case USB_DEVICE_ID_RAZER_CORE:
        case USB_DEVICE_ID_RAZER_CHROMA_MUG:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                    report.transaction_id.id = 0x3F;
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    report.transaction_id.id = 0x3F;
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
                    report.transaction_id.id = 0x3F;
                    break;
            }
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(dev, &report);
}


