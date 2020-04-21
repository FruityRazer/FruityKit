//
//  DeviceQuery.m
//  fruityrazer
//
//  Created by Eduardo Almeida on 07/07/18.
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

#import "DeviceQuery.h"

razer_device __DQ_DEVICES[] = {
    //  Headphones
    {
        .shortName = "manowar",
        .fullName = "Razer ManO' War",
        .usbId = 0x0A02,
        .synapse = synapse2,
        .type = headphones
    },
    //  Mice
    {
        .shortName = "mamba",
        .fullName = "Razer Mamba",
        .usbId = 0x0045,
        .synapse = synapse2,
        .type = mouse
    },
    //  Mousepads
    {
        .shortName = "firefly",
        .fullName = "Razer Firefly",
        .usbId = 0x0C00,
        .synapse = synapse2,
        .type = mousepad
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

razer_device_r dq_get_device_list() {
    razer_device_r ret = {
        .devices = (razer_device *)&__DQ_DEVICES,
        .length = sizeof(__DQ_DEVICES) / sizeof(razer_device)
    };
    
    return ret;
}

bool _dq_is_correct_device(IOUSBDeviceInterface **usb_dev, int device_id) {
    UInt16 product = -1;
    
    (*usb_dev)->GetDeviceProduct(usb_dev, &product);
    
    return (product == device_id);
}

bool dq_check_device_connected(int device_id) {
    CFMutableDictionaryRef matchingDict;
    io_iterator_t iter;
    kern_return_t kr;
    io_service_t usbDevice;
    
    /* set up a matching dictionary for the class */
    matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    if (matchingDict == NULL) {
        return NULL;
    }
    
    /* Now we have a dictionary, get an iterator.*/
    kr = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &iter);
    if (kr != KERN_SUCCESS) {
        return NULL;
    }
    
    /* iterate */
    while ((usbDevice = IOIteratorNext(iter))) {
        kern_return_t kr;
        IOCFPlugInInterface **plugInInterface = NULL;
        SInt32 score;
        HRESULT result;
        IOUSBDeviceInterface **dev = NULL;
        
        UInt16 vendor;
        UInt16 product;
        UInt16 release;
        
        kr = IOCreatePlugInInterfaceForService(usbDevice, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score);
        
        //Don’t need the device object after intermediate plug-in is created
        kr = IOObjectRelease(usbDevice);
        if ((kIOReturnSuccess != kr) || !plugInInterface)
            continue;
        
        //Now create the device interface
        result = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID650), (LPVOID *)&dev);
        
        //Don’t need the intermediate plug-in after device interface is created
        (*plugInInterface)->Release(plugInInterface);
        
        if (result || !dev)
            continue;
        
        //Check these values for confirmation
        kr = (*dev)->GetDeviceVendor(dev, &vendor);
        kr = (*dev)->GetDeviceProduct(dev, &product);
        kr = (*dev)->GetDeviceReleaseNumber(dev, &release);
        
        if (_dq_is_correct_device(dev, device_id)) {
            (void) (*dev)->Release(dev);
            
            IOObjectRelease(iter);
            
            return true;
        }
        
        (void) (*dev)->Release(dev);
    }
    
    return false;
}

IOUSBDeviceInterface** dq_get_device(int device_id) {
    CFMutableDictionaryRef matchingDict;
    io_iterator_t iter;
    kern_return_t kr;
    io_service_t usbDevice;
    
    /* set up a matching dictionary for the class */
    matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    if (matchingDict == NULL) {
        return NULL; // fail
    }
    
    /* Now we have a dictionary, get an iterator.*/
    kr = IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &iter);
    if (kr != KERN_SUCCESS) {
        return NULL;
    }
    
    /* iterate */
    while ((usbDevice = IOIteratorNext(iter))) {
        kern_return_t kr;
        IOCFPlugInInterface **plugInInterface = NULL;
        SInt32 score;
        HRESULT result;
        IOUSBDeviceInterface **dev = NULL;
        
        UInt16 vendor;
        UInt16 product;
        UInt16 release;
        
        kr = IOCreatePlugInInterfaceForService(usbDevice, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score);
        
        //Don’t need the device object after intermediate plug-in is created
        kr = IOObjectRelease(usbDevice);
        if ((kIOReturnSuccess != kr) || !plugInInterface)
            continue;
        
        //Now create the device interface
        result = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID650), (LPVOID *)&dev);
        
        //Don’t need the intermediate plug-in after device interface is created
        (*plugInInterface)->Release(plugInInterface);
        
        if (result || !dev)
            continue;
        
        //Check these values for confirmation
        kr = (*dev)->GetDeviceVendor(dev, &vendor);
        kr = (*dev)->GetDeviceProduct(dev, &product);
        kr = (*dev)->GetDeviceReleaseNumber(dev, &release);
        
        if (!_dq_is_correct_device(dev, device_id)) {
            (void) (*dev)->Release(dev);
            
            continue;
        }
        
        //Open the device to change its state
        kr = (*dev)->USBDeviceOpen(dev);
        if (kr != kIOReturnSuccess)  {
            (void) (*dev)->Release(dev);
            continue;
        }
        
        IOObjectRelease(iter);
        
        return dev;
    }
    
    IOObjectRelease(iter);
    
    return NULL;
}

void dq_close_device(IOUSBDeviceInterface **device) {
    (*device)->USBDeviceClose(device);
    (*device)->Release(device);
}
