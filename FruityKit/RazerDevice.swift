//
//  RazerDevice.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

struct RazerDevice: Device {
    let shortName: String
    let fullName: String
    let usbId: Int
    let type: DeviceType
}

extension RazerDevice {
    init(device: razer_device) {
        shortName = String(cString: device.shortName)
        fullName = String(cString: device.fullName)
        usbId = Int(device.usbId)
        
        switch device.type.rawValue {
        case 0:
            type = .other(type: "headphones")
        case 1:
            type = .keyboard
        case 2:
            type = .mouse
        case 3:
            type = .other(type: "misc_basestation")
        case 4:
            type = .other(type: "misc_hyperflux")
        case 5:
            type = .other(type: "mousepad")
        default:
            type = .other(type: "unknown")
        }
    }
    
    var connected: Bool {
        dq_check_device_connected(Int32(usbId))
    }
}
