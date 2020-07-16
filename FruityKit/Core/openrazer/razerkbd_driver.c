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

#include "razerkbd_driver.h"
#include "razerchromacommon.h"
#include "razercommon.h"

#include "USBCommon.h"
#include "USBDeviceIdentifiers.h"



/**
 * Write device file "mode_pulsate"
 *
 * The brightness oscillates between fully on and fully off generating a pulsing effect
 */
bool razer_kbd_attr_write_mode_pulsate(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    struct razer_report report = razer_chroma_standard_set_led_effect(VARSTORE, BACKLIGHT_LED, 0x02);
    razer_send_payload(usb_dev, &report);
    
    return (report.status == RAZER_CMD_SUCCESSFUL);
}

/**
 * Write device file "mode_none"
 *
 * No keyboard effect is activated whenever this file is written to
 */
bool razer_kbd_attr_write_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    struct razer_report report;
    razer_chroma_standard_matrix_effect_none(VARSTORE, BACKLIGHT_LED);
    
    razer_send_payload(usb_dev, &report);
    
    return (report.status == RAZER_CMD_SUCCESSFUL);
}

/**
 * Write device file "mode_wave"
 *
 * When 1 is written (as a character, 0x31) the wave effect is displayed moving left across the keyboard
 * if 2 is written (0x32) then the wave effect goes right
 *
 * For the extended its 0x00 and 0x01
 */
bool razer_kbd_attr_write_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    unsigned char direction = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report;
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_ORNATA:
        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
        case USB_DEVICE_ID_RAZER_HUNTSMAN:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, BACKLIGHT_LED, direction);
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_V2:
            report = razer_chroma_standard_matrix_effect_wave(VARSTORE, BACKLIGHT_LED, direction);
            report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
            break;
            
        case USB_DEVICE_ID_RAZER_TARTARUS_V2:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, BACKLIGHT_LED, direction);
            report.transaction_id.id = 0x1F;
            break;
            
        default:
            report = razer_chroma_standard_matrix_effect_wave(VARSTORE, BACKLIGHT_LED, direction);
            break;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "mode_spectrum"
 *
 * Specrum effect mode is activated whenever the file is written to
 */
bool razer_kbd_attr_write_mode_spectrum(IOUSBDeviceInterface **usb_dev) {
    struct razer_report report;
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_ORNATA:
        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
        case USB_DEVICE_ID_RAZER_HUNTSMAN:
        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            report.transaction_id.id = 0x1F;
            break;
            
        case USB_DEVICE_ID_RAZER_ANANSI:
            report = razer_chroma_standard_set_led_state(VARSTORE, BACKLIGHT_LED, ON);
            razer_send_payload(usb_dev, &report);
            report = razer_chroma_standard_set_led_effect(VARSTORE, BACKLIGHT_LED, LED_SPECTRUM_CYCLING);
            break;
            
        case USB_DEVICE_ID_RAZER_TARTARUS_V2:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            report.transaction_id.id = 0x1F;  // TODO move to a usb_device variable
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_V2:
            report = razer_chroma_standard_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
            break;
            
        default:
            report = razer_chroma_standard_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            break;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "mode_reactive"
 *
 * Sets reactive mode when this file is written to. A speed byte and 3 RGB bytes should be written
 */
bool razer_kbd_attr_write_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    struct razer_report report;
    
    if(count == 4) {
        unsigned char speed = (unsigned char)buf[0];
        
        switch(get_device_id(usb_dev)) {
            case USB_DEVICE_ID_RAZER_ORNATA:
            case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
            case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
            case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
            case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
            case USB_DEVICE_ID_RAZER_HUNTSMAN:
            case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
                
            case USB_DEVICE_ID_RAZER_TARTARUS_V2:
            case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
                report.transaction_id.id = 0x1F;
                break;
                
            case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_V2:
                report = razer_chroma_standard_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
                report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
                break;
            default:
                report = razer_chroma_standard_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
        }
        
        return razer_send_payload(usb_dev, &report);
        
    }
    
    return false;
}

/**
 * Write device file "mode_static"
 *
 * Set the keyboard to mode when 3 RGB bytes are written
 */
bool razer_kbd_attr_write_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    struct razer_report report;
    
    switch(get_device_id(usb_dev)) {
            
        case USB_DEVICE_ID_RAZER_TARTARUS_V2:
            report = razer_chroma_extended_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
            return razer_send_payload(usb_dev, &report);
            
        case USB_DEVICE_ID_RAZER_ORBWEAVER:
        case USB_DEVICE_ID_RAZER_DEATHSTALKER_EXPERT:
            report = razer_chroma_standard_set_led_effect(VARSTORE, BACKLIGHT_LED, 0x00);
            return razer_send_payload(usb_dev, &report);
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_STEALTH:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_STEALTH_EDITION:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2012:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2013: // Doesn't need any parameters as can only do one type of static
            report = razer_chroma_standard_set_led_effect(VARSTORE, LOGO_LED, 0x00);
            return razer_send_payload(usb_dev, &report);
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_OVERWATCH:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA:
        case USB_DEVICE_ID_RAZER_DEATHSTALKER_CHROMA:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_X_CHROMA:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_X_CHROMA_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2016:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_X_ULTIMATE:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_MID_2017:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2017:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_2019:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2019:
        case USB_DEVICE_ID_RAZER_BLADE_QHD:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_2018:
        case USB_DEVICE_ID_RAZER_BLADE_2018_MERCURY:
        case USB_DEVICE_ID_RAZER_BLADE_2018_BASE:
        case USB_DEVICE_ID_RAZER_BLADE_2019_ADV:
        case USB_DEVICE_ID_RAZER_BLADE_2019_BASE:
        case USB_DEVICE_ID_RAZER_BLADE_MID_2019_MERCURY:
        case USB_DEVICE_ID_RAZER_BLADE_STUDIO_EDITION_2019:
        case USB_DEVICE_ID_RAZER_BLADE_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_2017:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_2017_FULLHD:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_2019:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_LATE_2019:
        case USB_DEVICE_ID_RAZER_TARTARUS:
        case USB_DEVICE_ID_RAZER_TARTARUS_CHROMA:
            if(count == 3) {
                report = razer_chroma_standard_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                return razer_send_payload(usb_dev, &report);
            } else {
                return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_V2:
        case USB_DEVICE_ID_RAZER_ORBWEAVER_CHROMA:
            if(count == 3) {
                report = razer_chroma_standard_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
                return razer_send_payload(usb_dev, &report);
            } else {
                return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_LITE:
        case USB_DEVICE_ID_RAZER_ORNATA:
        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
        case USB_DEVICE_ID_RAZER_HUNTSMAN:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
            if(count == 3) {
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                return razer_send_payload(usb_dev, &report);
            } else {
                return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
            if(count == 3) {
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                report.transaction_id.id = 0x1F;
                return razer_send_payload(usb_dev, &report);
            } else {
                return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_ANANSI:
            if(count == 3) {
                report = razer_chroma_standard_set_led_state(VARSTORE, BACKLIGHT_LED, ON);
                if (!razer_send_payload(usb_dev, &report))
                    return false;
                
                report = razer_chroma_standard_set_led_effect(VARSTORE, BACKLIGHT_LED, LED_STATIC);
                if (!razer_send_payload(usb_dev, &report))
                    return false;
                
                report = razer_chroma_standard_set_led_rgb(VARSTORE, BACKLIGHT_LED, (struct razer_rgb *) &buf[0]);
                return razer_send_payload(usb_dev, &report);
            } else
                return false;
            break;
            
        default:
            return false;
            
    }
    
    return false;
}

/**
 * Write device file "mode_starlight"
 *
 * Starlight keyboard effect is activated whenever this file is written to (for bw2016)
 *
 * Or if an Ornata
 * 7 bytes, speed, rgb, rgb
 * 4 bytes, speed, rgb
 * 1 byte, speed
 */
bool razer_kbd_attr_write_mode_starlight(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    struct razer_rgb rgb1 = {.r = 0x00, .g = 0xFF, .b = 0x00};
    struct razer_report report;
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_ORNATA:
            if(count == 4) {
                report = razer_chroma_extended_matrix_effect_starlight_single(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1]);
                return razer_send_payload(usb_dev, &report);
            } else {
                return false;
            }
            break;
            
            
        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
        case USB_DEVICE_ID_RAZER_HUNTSMAN:
        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
            if(count == 7) {
                report = razer_chroma_extended_matrix_effect_starlight_dual(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1], (struct razer_rgb*)&buf[4]);
                return razer_send_payload(usb_dev, &report);
            } else if(count == 4) {
                report = razer_chroma_extended_matrix_effect_starlight_single(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1]);
                return razer_send_payload(usb_dev, &report);
            } else if(count == 1) {
                report = razer_chroma_extended_matrix_effect_starlight_random(VARSTORE, BACKLIGHT_LED, buf[0]);
                return razer_send_payload(usb_dev, &report);
            } else {
                return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
            if (count == 7) {
                report = razer_chroma_extended_matrix_effect_starlight_dual(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1], (struct razer_rgb*)&buf[4]);
            } else if(count == 4) {
                report = razer_chroma_extended_matrix_effect_starlight_single(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1]);
            } else if(count == 1) {
                report = razer_chroma_extended_matrix_effect_starlight_random(VARSTORE, BACKLIGHT_LED, buf[0]);
            } else {
                return false;
            }
            report.transaction_id.id = 0x1F;
            
            return razer_send_payload(usb_dev, &report);
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_V2:
            if(count == 7) {
                report = razer_chroma_standard_matrix_effect_starlight_dual(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1], (struct razer_rgb*)&buf[4]);
                report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
            } else if(count == 4) {
                report = razer_chroma_standard_matrix_effect_starlight_single(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1]);
                report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
            } else if(count == 1) {
                report = razer_chroma_standard_matrix_effect_starlight_random(VARSTORE, BACKLIGHT_LED, buf[0]);
                report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
            } else {
                return false;
            }
            
            return razer_send_payload(usb_dev, &report);
            
            
        default: // BW2016 can do normal starlight
            report = razer_chroma_standard_matrix_effect_starlight_single(VARSTORE, BACKLIGHT_LED, 0x01, &rgb1);
            
            return razer_send_payload(usb_dev, &report);
    }
    
    return false;
}

/**
 * Write device file "mode_breath"
 */
bool razer_kbd_attr_write_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    struct razer_report report;
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_LITE:
        case USB_DEVICE_ID_RAZER_ORNATA:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                    return razer_send_payload(usb_dev, &report);
                    
                default:
                    return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_TARTARUS_V2:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                    return razer_send_payload(usb_dev, &report);
                    
                case 6: // Dual colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    return razer_send_payload(usb_dev, &report);
                    
                case 1: // "Random" colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
                    return razer_send_payload(usb_dev, &report);
                    
                default:
                    return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
        case USB_DEVICE_ID_RAZER_HUNTSMAN:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                    return razer_send_payload(usb_dev, &report);
                    
                case 6: // Dual colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    return razer_send_payload(usb_dev, &report);
                    
                case 1: // "Random" colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
                    return razer_send_payload(usb_dev, &report);
                    
                default:
                    return false;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
            if (count == 3) { // Single colour mode
                report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
            } else if (count == 6) { // Dual colour mode
                report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
            } else if (count == 1) { // "Random" colour mode
                report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
            } else {
                return false;
            }
            report.transaction_id.id = 0x1F;
            return razer_send_payload(usb_dev, &report);
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_V2:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
                    break;
                    // TODO move default to case 1:. Then default: printk(warning). Also remove pointless buffer
            }
            
            report.transaction_id.id = 0x3F;  // TODO move to a usb_device variable
            
            return razer_send_payload(usb_dev, &report);
            
            break;
            
            
        default:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                    
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_standard_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
                    break;
                    // TODO move default to case 1:. Then default: printk(warning). Also remove pointless buffer
            }
            
            return razer_send_payload(usb_dev, &report);
            
            break;
    }
    
    return (report.status == RAZER_CMD_SUCCESSFUL);
}

/**
 * Write device file "set_brightness"
 *
 * Sets the brightness to the ASCII number written to this file.
 */
bool razer_kbd_attr_write_set_brightness(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count) {
    unsigned char brightness = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report;
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_LITE:
        case USB_DEVICE_ID_RAZER_ORNATA:
        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
        case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
        case USB_DEVICE_ID_RAZER_HUNTSMAN:
        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
            report = razer_chroma_extended_matrix_brightness(VARSTORE, BACKLIGHT_LED, brightness);
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
            report = razer_chroma_extended_matrix_brightness(VARSTORE, BACKLIGHT_LED, brightness);
            report.transaction_id.id = 0x1F;
            break;
            
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_STEALTH:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_STEALTH_EDITION:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2012:
        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2013:
            report = razer_chroma_standard_set_led_brightness(VARSTORE, LOGO_LED, brightness);
            break;
            
        case USB_DEVICE_ID_RAZER_NOSTROMO:
        default:
            if (is_blade_laptop(usb_dev)) {
                report = razer_chroma_misc_set_blade_brightness(brightness);
            } else {
                report = razer_chroma_standard_set_led_brightness(VARSTORE, BACKLIGHT_LED, brightness);
            }
            break;
    }
    
    return razer_send_payload(usb_dev, &report);
}
