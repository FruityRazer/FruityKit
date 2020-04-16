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

razer_device __DQ_DEVICES_SYNAPSE_2[] = {
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
        .fullName = "Razer BlackWidow Ultimate 2012",
        .usbId = 0x0,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "blackwidow_stealth",
        .fullName = "Razer BlackWidow Stealth",
        .usbId = 0x0,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "anansi",
        .fullName = "Razer Anansi",
        .usbId = 0x0,
        .synapse = synapse2,
        .type = keyboard
    },
    {
        .shortName = "nostromo",
        .fullName = "Razer Nostromo",
        .usbId = 0x0,
        .synapse = synapse2,
        .type = keyboard
    },
    //  ...
    {
        .shortName = "huntsman_elite_hw",
        .fullName = "Razer Huntsman Elite",
        .usbId = 0x0226,
        .synapse = synapse2,
        .type = keyboard
    },
};

razer_device __DQ_DEVICES_SYNAPSE_3[] = {
    {
        .shortName = "hyperflux",
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

razer_device __DQ_DEVICES[] = {
    
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
