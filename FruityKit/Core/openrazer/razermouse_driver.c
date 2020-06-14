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

    return razer_send_payload(dev, &report, NULL);
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

    return razer_send_payload(dev, &report, NULL);
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

            razer_send_payload(dev, &report, NULL);

            report = razer_naga_trinity_effect_static((struct razer_rgb*)&buf[0]);
            break;

        default:
            report = razer_chroma_standard_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
            break;
        }

        return razer_send_payload(dev, &report, NULL);
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

    return razer_send_payload(dev, &report, NULL);
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

    return razer_send_payload(dev, &report, NULL);
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

        return razer_send_payload(dev, &report, NULL);

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

    return razer_send_payload(dev, &report, NULL);
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
        return razer_send_payload(dev, &report, NULL);
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
    razer_send_payload(dev, &report, NULL);


    if(count == 3) {
        report = razer_chroma_standard_set_led_rgb(NOSTORE, BATTERY_LED, (struct razer_rgb*)&buf[0]);
        return razer_send_payload(dev, &report, NULL);
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
    
    return razer_send_payload(dev, &report, NULL);
}

/**
 * Write device file "set_low_battery_threshold"
 *
 * Sets the low battery blink threshold to the ASCII number written to this file.
 */
bool razer_mouse_attr_write_set_low_battery_threshold(IOUSBDeviceInterface **dev, const char *buf, size_t count)
{
    UInt16 product = -1;
    (*dev)->GetDeviceProduct(dev, &product);
    
    unsigned char threshold = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = razer_chroma_misc_set_low_battery_threshold(threshold);

    return razer_send_payload(dev, &report, NULL);
}
