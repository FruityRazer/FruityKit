//
//  DeviceQuery+Devices.h
//  FruityKit
//
//  Created by Eduardo Almeida on 14/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
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

#ifndef DeviceQuery_Devices_h
#define DeviceQuery_Devices_h

typedef enum razer_synapse_version {
    synapse2 = 2,
    synapse3 = 3
} razer_synapse_version;

typedef enum device_type {
    headphones,
    keyboard,
    keypad,
    laptop,
    misc_basestation,
    misc_hyperflux,
    mouse,
    mousepad
} razer_device_type;

typedef struct razer_device {
    const char *shortName;
    const char *fullName;
    UInt32 usbId;
    razer_synapse_version synapse;
    razer_device_type type;
} razer_device;

razer_device __DQ_DEVICES[] = {
    //  Mice
    {
        .shortName = "orochi_2011",
        .fullName = "Razer Orochi (2011)",
        .usbId = 0x0013,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_3_5g",
        .fullName = "Razer Deathadder 3.5G",
        .usbId = 0x0016,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "abyssus_1800",
        .fullName = "Razer Abyssus (1800 DPI)",
        .usbId = 0x0020,
        .synapse = synapse2,
        .type = mouse
    },{
        .shortName = "mamba_2012_wired",
        .fullName = "Razer Mamba (2012)",
        .usbId = 0x0024,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "mamba_2012_wireless",
        .fullName = "Razer Mamba Wireless (2012)",
        .usbId = 0x0025,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "naga_2012",
        .fullName = "Razer Naga (2012)",
        .usbId = 0x002E,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "imperator",
        .fullName = "Razer Imperator",
        .usbId = 0x002F,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "ouroboros",
        .fullName = "Razer Ouroboros",
        .usbId = 0x0032,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "taipan",
        .fullName = "Razer Taipan",
        .usbId = 0x0034,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "naga_hex_red",
        .fullName = "Razer Naga Hex Red",
        .usbId = 0x0036,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_2013",
        .fullName = "Razer Deahtadder (2013)",
        .usbId = 0x0037,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_1800",
        .fullName = "Razer Deathadder (1800 DPI)",
        .usbId = 0x0038,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "orochi_2013",
        .fullName = "Razer Orochi (2013)",
        .usbId = 0x0039,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "naga_2014",
        .fullName = "Razer Naga (2014)",
        .usbId = 0x0040,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "naga_hex",
        .fullName = "Razer Naga Hex",
        .usbId = 0x0041,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "abyssus",
        .fullName = "Razer Abyssus",
        .usbId = 0x0042,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_chroma",
        .fullName = "Razer Deathadder Chroma",
        .usbId = 0x0043,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "mamba_wired",
        .fullName = "Razer Mamba",
        .usbId = 0x0044,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "mamba_wireless",
        .fullName = "Razer Mamba Wireless",
        .usbId = 0x0045,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "mamba_wired_te",
        .fullName = "Razer Mamba (TE)",
        .usbId = 0x0046,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "orochi_chroma",
        .fullName = "Razer Orochi Chroma",
        .usbId = 0x0048,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "diamondback_chroma",
        .fullName = "Razer Diamondback Chroma",
        .usbId = 0x004C,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "naga_hex_v2",
        .fullName = "Razer Naga Hex V2",
        .usbId = 0x0050,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "naga_hex_chroma",
        .fullName = "Razer Naga Hex Chroma",
        .usbId = 0x0053,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_3500",
        .fullName = "Razer Deathadder (3500 DPI)",
        .usbId = 0x0054,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "lancehead_wired",
        .fullName = "Razer Lancehead",
        .usbId = 0x0059,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "lancehead_wireless",
        .fullName = "Razer Lancehead Wireless",
        .usbId = 0x005A,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "abyssus_v2",
        .fullName = "Razer Abyssus V2",
        .usbId = 0x005B,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_elite",
        .fullName = "Razer Deathadder Elite",
        .usbId = 0x005C,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "abyssus_2000",
        .fullName = "Razer Abyssus (2000 DPI)",
        .usbId = 0x005E,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "lancehead_te_wired",
        .fullName = "Razer Lancehead TE",
        .usbId = 0x0060,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "basilisk",
        .fullName = "Razer Basilisk",
        .usbId = 0x0064,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "naga_trinity",
        .fullName = "Razer Naga Trinity",
        .usbId = 0x0067,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "abyssus_elite_dva",
        .fullName = "Razer Abyssus Elite (D.Va)",
        .usbId = 0x006A,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "abyssus_essential",
        .fullName = "Razer Abyssus Essential",
        .usbId = 0x006B,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "mamba_elite",
        .fullName = "Razer Mamba Elite",
        .usbId = 0x006C,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_essential",
        .fullName = "Razer Deathadder Essential",
        .usbId = 0x006E,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "lancehead_wireless_receiver",
        .fullName = "Razer Lancehead Wireless (Receiver)",
        .usbId = 0x006F,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "lancehead_wireless_wired",
        .fullName = "Razer Lancehead Wireless (Wired)",
        .usbId = 0x0070,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_essential_white",
        .fullName = "Razer Deathadder Essential (White)",
        .usbId = 0x0071,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "mamba_wireless_receiver",
        .fullName = "Razer Mamba Wireless (Receiver)",
        .usbId = 0x0072,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "mamba_wireless_wired",
        .fullName = "Razer Mamba Wireless (Wired)",
        .usbId = 0x0073,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "viper",
        .fullName = "Razer Viper",
        .usbId = 0x0078,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "viper_ultimate_wired",
        .fullName = "Razer Viper Ultimate",
        .usbId = 0x007A,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "viper_ultimate_wireless",
        .fullName = "Razer Viper Ultimate (Wireless)",
        .usbId = 0x007B,
        .synapse = synapse2,
        .type = mouse
    },
    {
        .shortName = "deathadder_v2",
        .fullName = "Razer Deathadder V2",
        .usbId = 0x0084,
        .synapse = synapse2,
        .type = mouse
    },
    //  Keyboards
    //  ...
    {
        .shortName = "blackwidow_ultimate_2012",
        .fullName = "Razer BlackWidow Ultimate (2012)",
        .usbId = 0x010D,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_stealth_edition",
        .fullName = "Razer BlackWidow Stealth Edition",
        .usbId = 0x010E,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "anansi",
        .fullName = "Razer Anansi",
        .usbId = 0x010F,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "nostromo",
        .fullName = "Razer Nostromo",
        .usbId = 0x0111,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "orbweaver",
        .fullName = "Razer Orbweaver",
        .usbId = 0x0113,
        .synapse = synapse2,
        .type = keypad
    },
    {
        .shortName = "blackwidow_ultimate_2013",
        .fullName = "Razer BlackWidow Ultimate (2013)",
        .usbId = 0x011A,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_stealth",
        .fullName = "Razer BlackWidow Stealth",
        .usbId = 0x011B,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "tartarus",
        .fullName = "Razer Tartarus",
        .usbId = 0x0201,
        .synapse = synapse2,
        .type = keypad
    },
    {
        .shortName = "deathstalker_expert",
        .fullName = "Razer Deathstalker Expert",
        .usbId = 0x0202,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_chroma",
        .fullName = "Razer BlackWidow Chroma",
        .usbId = 0x0203,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "deathstalker_chroma",
        .fullName = "Razer Deathstalker Chroma",
        .usbId = 0x0204,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blade_stealth",
        .fullName = "Razer Blade Stealth",
        .usbId = 0x0205,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "orbweaver_chroma",
        .fullName = "Razer Orbweaver Chroma",
        .usbId = 0x0207,
        .synapse = synapse2,
        .type = keypad
    },
    {
        .shortName = "tartarus_chroma",
        .fullName = "Razer Tartarus Chroma",
        .usbId = 0x0208,
        .synapse = synapse2,
        .type = keypad
    },
    {
        .shortName = "blackwidow_chroma_te",
        .fullName = "Razer BlackWidow Chroma TE",
        .usbId = 0x0209,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blade_qhd",
        .fullName = "Razer Blade QHD",
        .usbId = 0x020F,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_pro_2016",
        .fullName = "Razer Blade Pro (Late 2016)",
        .usbId = 0x0210,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blackwidow_overwatch",
        .fullName = "Razer BlackWidow Overwatch",
        .usbId = 0x0211,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_ultimate_2016",
        .fullName = "Razer BlackWidow Ultimate (2016)",
        .usbId = 0x0214,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_x_chroma",
        .fullName = "Razer BlackWidow X Chroma",
        .usbId = 0x0216,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_x_ultimate",
        .fullName = "Razer BlackWidow X Ultimate",
        .usbId = 0x0217,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_x_chroma_te",
        .fullName = "Razer BlackWidow X Chroma TE",
        .usbId = 0x021A,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "ornata_chroma",
        .fullName = "Razer Ornata Chroma",
        .usbId = 0x021E,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "ornata",
        .fullName = "Razer Ornata",
        .usbId = 0x021F,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blade_stealth_2016",
        .fullName = "Razer Blade Stealth (Late 2016)",
        .usbId = 0x0220,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blackwidow_chroma_v2",
        .fullName = "Razer BlackWidow Chroma V2",
        .usbId = 0x0221,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blade_2016",
        .fullName = "Razer Blade (Late 2016)",
        .usbId = 0x224,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_pro_2017",
        .fullName = "Razer Blade Pro (2017)",
        .usbId = 0x225,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "huntsman_elite_hw",
        .fullName = "Razer Huntsman Elite",
        .usbId = 0x0226,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "huntsman",
        .fullName = "Razer Huntsman",
        .usbId = 0x0227,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_elite",
        .fullName = "Razer BlackWidow Elite",
        .usbId = 0x0228,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "cynosa_chroma",
        .fullName = "Razer Cynosa Chroma",
        .usbId = 0x022A,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "tartarus_V2",
        .fullName = "Razer Tartarus V2",
        .usbId = 0x022B,
        .synapse = synapse2,
        .type = keypad
    },
    {
        .shortName = "blade_stealth_mid_2017",
        .fullName = "Razer Blade Stealth (Mid 2017)",
        .usbId = 0x022D,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_pro_2017_fhd",
        .fullName = "Razer Pro (2017 FHD)",
        .usbId = 0x022F,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_stealth_late_2017",
        .fullName = "Razer Blade Stealth (Late 2017)",
        .usbId = 0x0232,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_2018",
        .fullName = "Razer Blade (2018)",
        .usbId = 0x0233,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_pro_2019",
        .fullName = "Razer Blade Pro (2019)",
        .usbId = 0x0233,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "bladewidow_lite",
        .fullName = "Razer BlackWidow Lite",
        .usbId = 0x0235,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "bladewidow_essential",
        .fullName = "Razer BlackWidow Essential",
        .usbId = 0x0237,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blade_stealth_2019",
        .fullName = "Razer Blade Stealth (2019)",
        .usbId = 0x0239,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_2019_adv",
        .fullName = "Razer Blade (2019) Advanced",
        .usbId = 0x023A,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_2019_base",
        .fullName = "Razer Blade (2019)",
        .usbId = 0x023B,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_2019_mercury",
        .fullName = "Razer Blade (2019) Mercury",
        .usbId = 0x0240,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blackwidow_2019",
        .fullName = "Razer BlackWidow (2019)",
        .usbId = 0x0241,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "huntsman_te",
        .fullName = "Razer Huntsman TE",
        .usbId = 0x0243,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blade_mid_2019_mercury",
        .fullName = "Razer Blade (Mid 2019) Mercury",
        .usbId = 0x0245,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_2019",
        .fullName = "Razer Blade (2019)",
        .usbId = 0x0246,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_stealth_late_2019",
        .fullName = "Razer Blade Stealth (Late 2019)",
        .usbId = 0x024A,
        .synapse = synapse2,
        .type = laptop
    },
    {
        .shortName = "blade_pro_late2019",
        .fullName = "Razer Blade Pro (Late 2019)",
        .usbId = 0x024C,
        .synapse = synapse2,
        .type = laptop
    },
    
    {
        .shortName = "blade_studio_2019",
        .fullName = "Razer Blade Studio Edition (2019)",
        .usbId = 0x024D,
        .synapse = synapse2,
        .type = laptop
    },
    //  ...
    {
        .shortName = "mamba_hyperflux",
        .fullName = "Razer Mamba Hyperflux",
        .usbId = 0x0068,
        .synapse = synapse3,
        .type = misc_hyperflux
    },
    {
        .shortName = "huntsman_elite_sw",
        .fullName = "Razer Huntsman Elite",
        .usbId = 0x0226,
        .synapse = synapse3,
        .type = keyboard
    },
    {
        .shortName = "base_station",
        .fullName = "Razer Base Station Chroma",
        .usbId = 0x0F08,
        .synapse = synapse3,
        .type = misc_basestation
    },
};

#endif /* DeviceQuery_Devices_h */
