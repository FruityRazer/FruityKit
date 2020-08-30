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

#include "razermouse_driver.h"
#include "razercommon.h"
#include "razerchromacommon.h"

#include "USBCommon.h"
#include "USBDeviceIdentifiers.h"

#pragma mark Getters

ssize_t razer_attr_read_mouse_dpi(IOUSBDeviceInterface **dev, char *buf) {
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    struct razer_report response = {0};
    unsigned short dpi_x;
    unsigned short dpi_y;

    // So far I think imperator uses varstore
    switch (product) {
    case USB_DEVICE_ID_RAZER_NAGA_HEX_RED:
    case USB_DEVICE_ID_RAZER_NAGA_HEX:
    case USB_DEVICE_ID_RAZER_NAGA_2012:
    case USB_DEVICE_ID_RAZER_ABYSSUS_1800:
    case USB_DEVICE_ID_RAZER_DEATHADDER_2013:
    case USB_DEVICE_ID_RAZER_DEATHADDER_1800:
        report = razer_chroma_misc_get_dpi_xy_byte();
        break;

    case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
        report = razer_chroma_misc_get_dpi_xy(NOSTORE);
        report.transaction_id.id = 0x1f;
        break;

    case USB_DEVICE_ID_RAZER_OROCHI_2013:
    case USB_DEVICE_ID_RAZER_IMPERATOR:
        report = razer_chroma_misc_get_dpi_xy(VARSTORE);
        break;

    case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
    case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
    case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
    case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
    case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
    case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
    case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
    case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
    case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
    case USB_DEVICE_ID_RAZER_BASILISK:
    case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
        report = razer_chroma_misc_get_dpi_xy(NOSTORE);
        report.transaction_id.id = 0x3f;
        break;

    default:
        report = razer_chroma_misc_get_dpi_xy(NOSTORE);
        break;
    }

    if (!razer_send_payload3(dev, &report, &response))
        return -1;

    // Byte, Byte for DPI not Short, Short
    if (product == USB_DEVICE_ID_RAZER_NAGA_HEX ||
        product == USB_DEVICE_ID_RAZER_NAGA_HEX_RED ||
        product == USB_DEVICE_ID_RAZER_NAGA_2012 ||
        product == USB_DEVICE_ID_RAZER_DEATHADDER_2013 ||
        product == USB_DEVICE_ID_RAZER_ABYSSUS_1800) { // NagaHex is crap uses only byte for dpi
        dpi_x = response.arguments[0];
        dpi_y = response.arguments[1];
    } else {
        dpi_x = (response.arguments[1] << 8) | (response.arguments[2] & 0xFF); // Apparently the char buffer is rubbish, as buf[1] somehow can equal FFFFFF80????
        dpi_y = (response.arguments[3] << 8) | (response.arguments[4] & 0xFF);
    }

    return sprintf(buf, "%u:%u\n", dpi_x, dpi_y);
}

#pragma mark -
#pragma mark Setters

/**
 * Write device file "mode_none"
 *
 * No effect is activated whenever this file is written to
 */
bool razer_mouse_attr_write_mode_none(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    switch (product) {
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
            report = razer_chroma_mouse_extended_matrix_effect_none(VARSTORE, BACKLIGHT_LED);
            break;
            
        default:
            report = razer_chroma_standard_matrix_effect_none(VARSTORE, BACKLIGHT_LED);
            break;
    }
    
    return razer_send_payload(dev, &report);
}

/**
 * Write device file "mode_custom"
 *
 * Sets the mouse to custom mode whenever the file is written to
 */
bool razer_mouse_attr_write_mode_custom(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = razer_chroma_standard_matrix_effect_custom_frame(NOSTORE);
    
    switch (product) {
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2: // TODO look into this think its extended effects
            report = razer_chroma_standard_matrix_effect_custom_frame(NOSTORE);
            report.transaction_id.id = 0x3f;
            break;
            
        case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_BASILISK:
        case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
            report = razer_chroma_extended_matrix_effect_custom_frame();
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_custom_frame();
            report.transaction_id.id = 0x1f;
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS:
            report = razer_chroma_standard_matrix_effect_custom_frame(NOSTORE);
            report.transaction_id.id = 0x80;
            break;
    }
    
    return razer_send_payload(dev, &report);
}

/**
 * Write device file "mode_static"
 *
 * Set the mouse to static mode when 3 RGB bytes are written
 */
bool razer_mouse_attr_write_mode_static(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    if (count == 3) {
        switch (product) {
            case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
                report = razer_chroma_mouse_extended_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                break;
                
            case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
                report = razer_chroma_mouse_extended_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                report.transaction_id.id = 0xff;
                break;
                
            case USB_DEVICE_ID_RAZER_NAGA_TRINITY:
                // Some sort of mode switcher required after initialization and before color switching
                report = get_razer_report3(0x0f, 0x02, 0x06);
                report.arguments[0] = 0x00;
                report.arguments[1] = 0x00;
                report.arguments[2] = 0x08;
                report.arguments[3] = 0x00;
                report.arguments[4] = 0x00;
                report.arguments[5] = 0x00;
                report.transaction_id.id = 0x1f;
                
                razer_send_payload(dev, &report);
                
                report = razer_naga_trinity_effect_static((struct razer_rgb*)&buf[0]);
                break;
                
            default:
                report = razer_chroma_standard_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                break;
        }
        
        return razer_send_payload(dev, &report);
    }
    
    return false;
}

/**
 * Write device file "logo_led_effect"
 */
bool razer_mouse_attr_write_logo_led_effect(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    unsigned char effect = (unsigned char)strtoul(buf, NULL, 10);
    struct razer_report report = razer_chroma_standard_set_led_effect(VARSTORE, LOGO_LED, effect);
    report.transaction_id.id = 0x3F;
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "logo_led_rgb"
 */
bool razer_mouse_attr_write_logo_led_rgb(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    struct razer_report report = {0};
    
    if(count == 3) {
        report = razer_chroma_standard_set_led_rgb(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0]);
        report.transaction_id.id = 0x3F;
        return razer_send_payload(usb_dev, &report);
    }
    
    return false;
}

/**
 * Write device file "mode_wave"
 *
 * When 1 is written (as a character, 0x31) the wave effect is displayed moving up the mouse
 * if 2 is written (0x32) then the wave effect goes down
 */
bool razer_mouse_attr_write_mode_wave(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    unsigned char direction = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = razer_chroma_standard_matrix_effect_wave(VARSTORE, BACKLIGHT_LED, direction);
    
    return razer_send_payload(dev, &report);
}

/**
 * Write device file "mode_spectrum"
 *
 * Spectrum effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_mode_spectrum(IOUSBDeviceInterface **dev)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    switch (product) {
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
            report = razer_chroma_mouse_extended_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            break;
            
        default:
            report = razer_chroma_standard_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
            break;
    }
    
    return razer_send_payload(dev, &report);
}

/**
 * Write device file "mode_reactive"
 *
 * Sets reactive mode when this file is written to. A speed byte and 3 RGB bytes should be written
 */
bool razer_mouse_attr_write_mode_reactive(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    if(count == 4) {
        unsigned char speed = (unsigned char)buf[0];
        
        switch (product) {
            case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
                report = razer_chroma_mouse_extended_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
                
            default:
                report = razer_chroma_standard_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
        }
        
        return razer_send_payload(dev, &report);
        
    }
    
    return false;
}

/**
 * Write device file "mode_breath"
 *
 * Sets breathing mode by writing 1, 3 or 6 bytes
 */
bool razer_mouse_attr_write_mode_breath(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    switch (product) { // TODO refactor to have 2 methods to split out the breathing crap
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
                    break;
            }
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
            }
            break;
    }
    
    return razer_send_payload(dev, &report);
}

/**
 * Write device file "set_charging_effect"
 *
 * Sets charging effect.
 */
bool razer_mouse_attr_write_set_charging_effect(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    struct razer_report report = {0};
    
    if(count == 1) {
        report = razer_chroma_misc_set_dock_charge_type(buf[0]);
        return razer_send_payload(dev, &report);
    } else {
        return false;
    }
}

/**
 * Write device file "set_charging_colour"
 *
 * Sets charging colour using 3 RGB bytes
 */
bool razer_mouse_attr_write_set_charging_colour(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    // First enable static charging effect
    struct razer_report report = razer_chroma_misc_set_dock_charge_type(0x01);
    razer_send_payload(dev, &report);
    
    
    if(count == 3) {
        report = razer_chroma_standard_set_led_rgb(NOSTORE, BATTERY_LED, (struct razer_rgb*)&buf[0]);
        return razer_send_payload(dev, &report);
    } else {
        return false;
    }
}

/**
 * Write device file "matrix_brightness"
 *
 * Sets the brightness to the ASCII number written to this file.
 */

bool razer_mouse_attr_write_matrix_brightness(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    unsigned char brightness = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = {0};
    
    switch(product) {
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS:
            report = razer_chroma_misc_set_dock_brightness(brightness);
            break;
            
        case USB_DEVICE_ID_RAZER_OROCHI_CHROMA:
            // Orochi sets brightness of scroll wheel apparently
            report = razer_chroma_standard_set_led_brightness(VARSTORE, SCROLL_WHEEL_LED, brightness);
            break;
            
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            report = razer_chroma_standard_set_led_brightness(VARSTORE, BACKLIGHT_LED, brightness);
            report.transaction_id.id = 0x3f;
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_brightness(VARSTORE, 0x00, brightness);
            report.transaction_id.id = 0x1F;
            break;
            
        case USB_DEVICE_ID_RAZER_NAGA_TRINITY:
            // Naga Trinity uses the LED 0x00 and Matrix Brightness
            report = razer_chroma_extended_matrix_brightness(VARSTORE, 0x00, brightness);
            break;
            
        default:
            report = razer_chroma_standard_set_led_brightness(VARSTORE, BACKLIGHT_LED, brightness);
            break;
    }
    
    return razer_send_payload(dev, &report);
}

/**
 * Write device file "set_low_battery_threshold"
 *
 * Sets the low battery blink threshold to the ASCII number written to this file.
 */
bool razer_mouse_attr_write_set_low_battery_threshold(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    unsigned char threshold = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = razer_chroma_misc_set_low_battery_threshold(threshold);
    
    return razer_send_payload(dev, &report);
}

/**
 * Write device file "scroll_mode_wave" (for extended mouse matrix effects)
 *
 * Wave effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_scroll_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    unsigned char direction = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, SCROLL_WHEEL_LED, direction);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, SCROLL_WHEEL_LED, direction);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "scroll_mode_spectrum" (for extended mouse matrix effects)
 *
 * Spectrum effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_scroll_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
            report = razer_chroma_mouse_extended_matrix_effect_spectrum(VARSTORE, SCROLL_WHEEL_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_BASILISK:
        case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, SCROLL_WHEEL_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, SCROLL_WHEEL_LED);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "scroll_mode_reactive" (for extended mouse matrix effects)
 *
 * Sets reactive mode when this file is written to. A speed byte and 3 RGB bytes should be written
 */
bool razer_mouse_attr_write_scroll_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    struct razer_report report = {0};
    
    if(count == 4) {
        unsigned char speed = (unsigned char)buf[0];
        
        switch(get_device_id(usb_dev)) {
            case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
                report = razer_chroma_mouse_extended_matrix_effect_reactive(VARSTORE, SCROLL_WHEEL_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
                
            case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_BASILISK:
            case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, SCROLL_WHEEL_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
                
            case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, SCROLL_WHEEL_LED, speed, (struct razer_rgb*)&buf[1]);
                report.transaction_id.id = 0x1f;
                break;
                
            default:
                return false;
        }
        
        return razer_send_payload(usb_dev, &report);
        
    }
    
    return false;
}

/**
 * Write device file "scroll_mode_breath" (for extended mouse matrix effects)
 *
 * Sets breathing mode by writing 1, 3 or 6 bytes
 */
bool razer_mouse_attr_write_scroll_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    struct razer_report report = {0};
    // TODO refactor main breathing matrix function, add in LED ID field and this nastiness goes away too!
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_single(VARSTORE, SCROLL_WHEEL_LED, (struct razer_rgb*)&buf[0]);
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_dual(VARSTORE, SCROLL_WHEEL_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_random(VARSTORE, SCROLL_WHEEL_LED);
                    break;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL_WHITE_EDITION:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_BASILISK:
        case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, SCROLL_WHEEL_LED, (struct razer_rgb*)&buf[0]);
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, SCROLL_WHEEL_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, SCROLL_WHEEL_LED);
                    break;
            }
            break;
    }
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            report.transaction_id.id = 0x3f;
            break;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "scroll_mode_static" (for extended mouse matrix effects)
 *
 * Set the mouse to static mode when 3 RGB bytes are written
 */
bool razer_mouse_attr_write_scroll_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    struct razer_report report = {0};
    
    if(count == 3) {
        
        switch(get_device_id(usb_dev)) {
            case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
            case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
                report = razer_chroma_mouse_extended_matrix_effect_static(VARSTORE, SCROLL_WHEEL_LED, (struct razer_rgb*)&buf[0]);
                break;
                
            case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL:
            case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL_WHITE_EDITION:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_BASILISK:
            case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, SCROLL_WHEEL_LED, (struct razer_rgb*)&buf[0]);
                break;
                
            case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, SCROLL_WHEEL_LED, (struct razer_rgb*)&buf[0]);
                report.transaction_id.id = 0x1f;
                break;
                
            default:
                return false;
        }
        
        return razer_send_payload(usb_dev, &report);
    }
    
    return false;
}

/**
 * Write device file "scroll_mode_none" (for extended mouse matrix effects)
 *
 * No effect is activated whenever this file is written to
 */
bool razer_mouse_attr_write_scroll_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            report = razer_chroma_mouse_extended_matrix_effect_none(VARSTORE, SCROLL_WHEEL_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL_WHITE_EDITION:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_BASILISK:
        case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
            report = razer_chroma_extended_matrix_effect_none(VARSTORE, SCROLL_WHEEL_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_none(VARSTORE, SCROLL_WHEEL_LED);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "logo_mode_wave" (for extended mouse matrix effects)
 *
 * Wave effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_logo_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    
    unsigned char direction = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, LOGO_LED, direction);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, LOGO_LED, direction);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    razer_send_payload(usb_dev, &report);
    return count;
}

/**
 * Write device file "logo_mode_spectrum" (for extended mouse matrix effects)
 *
 * Spectrum effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_logo_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            report = razer_chroma_mouse_extended_matrix_effect_spectrum(VARSTORE, LOGO_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_ABYSSUS_ELITE_DVA_EDITION:
        case USB_DEVICE_ID_RAZER_ABYSSUS_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_BASILISK:
        case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, LOGO_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, LOGO_LED);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "logo_mode_reactive" (for extended mouse matrix effects)
 *
 * Sets reactive mode when this file is written to. A speed byte and 3 RGB bytes should be written
 */
bool razer_mouse_attr_write_logo_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    
    struct razer_report report = {0};
    
    if(count == 4) {
        unsigned char speed = (unsigned char)buf[0];
        
        switch(get_device_id(usb_dev)) {
            case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
            case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
                report = razer_chroma_mouse_extended_matrix_effect_reactive(VARSTORE, LOGO_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
                
            case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_ABYSSUS_ELITE_DVA_EDITION:
            case USB_DEVICE_ID_RAZER_ABYSSUS_ESSENTIAL:
            case USB_DEVICE_ID_RAZER_BASILISK:
            case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, LOGO_LED, speed, (struct razer_rgb*)&buf[1]);
                break;
                
            case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, LOGO_LED, speed, (struct razer_rgb*)&buf[1]);
                report.transaction_id.id = 0x1f;
                break;
                
            default:
                return false;
        }
        
        return razer_send_payload(usb_dev, &report);
    }
    
    return false;
}

/**
 * Write device file "logo_mode_breath" (for extended mouse matrix effects)
 *
 * Sets breathing mode by writing 1, 3 or 6 bytes
 */
bool razer_mouse_attr_write_logo_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    
    struct razer_report report = {0};
    // TODO refactor main breathing matrix function, add in LED ID field and this nastiness goes away too!
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_single(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0]);
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_dual(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_mouse_extended_matrix_effect_breathing_random(VARSTORE, LOGO_LED);
                    break;
            }
            break;
            
        case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL_WHITE_EDITION:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_ABYSSUS_ELITE_DVA_EDITION:
        case USB_DEVICE_ID_RAZER_ABYSSUS_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_VIPER:
        case USB_DEVICE_ID_RAZER_VIPER_ULTIMATE_WIRED:
        case USB_DEVICE_ID_RAZER_VIPER_ULTIMATE_WIRELESS:
        case USB_DEVICE_ID_RAZER_BASILISK:
        case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0]);
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, LOGO_LED);
                    break;
            }
            break;
    }
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            report.transaction_id.id = 0x3f;
            break;
    }
    
    razer_send_payload(usb_dev, &report);
    return count;
}

/**
 * Write device file "logo_mode_static" (for extended mouse matrix effects)
 *
 * Set the mouse to static mode when 3 RGB bytes are written
 */
bool razer_mouse_attr_write_logo_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    
    struct razer_report report = {0};
    
    if(count == 3) {
        switch(get_device_id(usb_dev)) {
            case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
            case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
                report = razer_chroma_mouse_extended_matrix_effect_static(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0]);
                break;
                
            case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL:
            case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL_WHITE_EDITION:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
            case USB_DEVICE_ID_RAZER_ABYSSUS_ELITE_DVA_EDITION:
            case USB_DEVICE_ID_RAZER_ABYSSUS_ESSENTIAL:
            case USB_DEVICE_ID_RAZER_VIPER:
            case USB_DEVICE_ID_RAZER_VIPER_ULTIMATE_WIRED:
            case USB_DEVICE_ID_RAZER_VIPER_ULTIMATE_WIRELESS:
            case USB_DEVICE_ID_RAZER_BASILISK:
            case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0]);
                break;
                
            case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, LOGO_LED, (struct razer_rgb*)&buf[0]);
                report.transaction_id.id = 0x1f;
                break;
                
            default:
                return false;
        }
        
        return razer_send_payload(usb_dev, &report);
    }
    
    return false;
}

/**
 * Write device file "logo_mode_none" (for extended mouse matrix effects)
 *
 * No effect is activated whenever this file is written to
 */
bool razer_mouse_attr_write_logo_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_NAGA_CHROMA:
        case USB_DEVICE_ID_RAZER_NAGA_HEX_V2:
            report = razer_chroma_mouse_extended_matrix_effect_none(VARSTORE, LOGO_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_DEATHADDER_ELITE:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_DEATHADDER_ESSENTIAL_WHITE_EDITION:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_MAMBA_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_ABYSSUS_ELITE_DVA_EDITION:
        case USB_DEVICE_ID_RAZER_ABYSSUS_ESSENTIAL:
        case USB_DEVICE_ID_RAZER_VIPER:
        case USB_DEVICE_ID_RAZER_VIPER_ULTIMATE_WIRED:
        case USB_DEVICE_ID_RAZER_VIPER_ULTIMATE_WIRELESS:
        case USB_DEVICE_ID_RAZER_BASILISK:
        case USB_DEVICE_ID_RAZER_DEATHADDER_V2:
            report = razer_chroma_extended_matrix_effect_none(VARSTORE, LOGO_LED);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_none(VARSTORE, LOGO_LED);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

bool razer_mouse_attr_write_side_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side)
{
    
    unsigned char direction = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, side, direction);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_wave(VARSTORE, side, direction);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "left_mode_wave" (for extended mouse matrix effects)
 *
 * Wave effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_left_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_wave(usb_dev, buf, count, LEFT_SIDE_LED);
}

/**
 * Write device file "right_mode_wave" (for extended mouse matrix effects)
 *
 * Wave effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_right_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_wave(usb_dev, buf, count, RIGHT_SIDE_LED);
}

bool razer_mouse_attr_write_side_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side)
{
    
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, side);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_spectrum(VARSTORE, side);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "left_mode_spectrum" (for extended mouse matrix effects)
 *
 * Spectrum effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_left_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_spectrum(usb_dev, buf, count, LEFT_SIDE_LED);
}

/**
 * Write device file "right_mode_spectrum" (for extended mouse matrix effects)
 *
 * Spectrum effect mode is activated whenever the file is written to
 */
bool razer_mouse_attr_write_right_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_spectrum(usb_dev, buf, count, RIGHT_SIDE_LED);
}

bool razer_mouse_attr_write_side_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side)
{
    
    struct razer_report report = {0};
    
    if(count == 4) {
        unsigned char speed = (unsigned char)buf[0];
        
        switch(get_device_id(usb_dev)) {
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, side, speed, (struct razer_rgb*)&buf[1]);
                break;
                
            case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
                report = razer_chroma_extended_matrix_effect_reactive(VARSTORE, side, speed, (struct razer_rgb*)&buf[1]);
                report.transaction_id.id = 0x1f;
                break;
                
            default:
                return false;
        }
        
        return razer_send_payload(usb_dev, &report);
    }
    
    return false;
}

/**
 * Write device file "left_mode_reactive" (for extended mouse matrix effects)
 *
 * Sets reactive mode when this file is written to. A speed byte and 3 RGB bytes should be written
 */
bool razer_mouse_attr_write_left_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_reactive(usb_dev, buf, count, LEFT_SIDE_LED);
}

/**
 * Write device file "right_mode_reactive" (for extended mouse matrix effects)
 *
 * Sets reactive mode when this file is written to. A speed byte and 3 RGB bytes should be written
 */
bool razer_mouse_attr_write_right_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_reactive(usb_dev, buf, count, RIGHT_SIDE_LED);
}

bool razer_mouse_attr_write_side_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side)
{
    
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            switch(count) {
                case 3: // Single colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_single(VARSTORE, side, (struct razer_rgb*)&buf[0]);
                    break;
                    
                case 6: // Dual colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_dual(VARSTORE, side, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
                    break;
                    
                default: // "Random" colour mode
                    report = razer_chroma_extended_matrix_effect_breathing_random(VARSTORE, side);
                    break;
            }
            break;
    }
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            report.transaction_id.id = 0x3f;
            break;
    }
    
    razer_send_payload(usb_dev, &report);
    return count;
}

/**
 * Write device file "left_mode_breath" (for extended mouse matrix effects)
 *
 * Sets breathing mode by writing 1, 3 or 6 bytes
 */
bool razer_mouse_attr_write_left_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_breath(usb_dev, buf, count, LEFT_SIDE_LED);
}

/**
 * Write device file "right_mode_breath" (for extended mouse matrix effects)
 *
 * Sets breathing mode by writing 1, 3 or 6 bytes
 */
bool razer_mouse_attr_write_right_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_breath(usb_dev, buf, count, RIGHT_SIDE_LED);
}

bool razer_mouse_attr_write_side_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side)
{
    
    struct razer_report report = {0};
    
    if(count == 3) {
        switch(get_device_id(usb_dev)) {
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
            case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, side, (struct razer_rgb*)&buf[0]);
                break;
            case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
                report = razer_chroma_extended_matrix_effect_static(VARSTORE, side, (struct razer_rgb*)&buf[0]);
                report.transaction_id.id = 0x1f;
                break;
        }
        
        return razer_send_payload(usb_dev, &report);
    }
    
    return false;
}

/**
 * Write device file "left_mode_static" (for extended mouse matrix effects)
 *
 * Set the mouse to static mode when 3 RGB bytes are written
 */
bool razer_mouse_attr_write_left_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_static(usb_dev, buf, count, LEFT_SIDE_LED);
}

/**
 * Write device file "right_mode_static" (for extended mouse matrix effects)
 *
 * Set the mouse to static mode when 3 RGB bytes are written
 */
bool razer_mouse_attr_write_right_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_static(usb_dev, buf, count, RIGHT_SIDE_LED);
}

bool razer_mouse_attr_write_side_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count, int side)
{
    
    struct razer_report report = {0};
    
    switch(get_device_id(usb_dev)) {
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_TE_WIRED:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_RECEIVER:
        case USB_DEVICE_ID_RAZER_LANCEHEAD_WIRELESS_WIRED:
            report = razer_chroma_extended_matrix_effect_none(VARSTORE, side);
            break;
            
        case USB_DEVICE_ID_RAZER_MAMBA_ELITE:
            report = razer_chroma_extended_matrix_effect_none(VARSTORE, side);
            report.transaction_id.id = 0x1f;
            break;
            
        default:
            return false;
    }
    
    return razer_send_payload(usb_dev, &report);
}

/**
 * Write device file "left_mode_none" (for extended mouse matrix effects)
 *
 * No effect is activated whenever this file is written to
 */
bool razer_mouse_attr_write_left_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_none(usb_dev, buf, count, LEFT_SIDE_LED);
}

/**
 * Write device file "right_mode_none" (for extended mouse matrix effects)
 *
 * No effect is activated whenever this file is written to
 */
bool razer_mouse_attr_write_right_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, size_t count)
{
    return razer_mouse_attr_write_side_mode_none(usb_dev, buf, count, RIGHT_SIDE_LED);
}
