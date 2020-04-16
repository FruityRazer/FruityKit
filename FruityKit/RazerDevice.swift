//
//  RazerDevice.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public struct RazerDevice: Device {
    public let shortName: String
    public let fullName: String
    public let type: DeviceType
    
    public let driver: Driver
}

extension RazerDevice {
    enum InitializationError: Error {
        case invalidSynapseVersion
    }
    
    init(device: razer_device) throws {
        shortName = String(cString: device.shortName)
        fullName = String(cString: device.fullName)
        
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
        
        switch device.synapse.rawValue {
        case 2:
            driver = .v2(driver: Synapse2Handle(usbId: Int32(device.usbId)))
        case 3:
            driver = .v3(driver: Synapse3Handle(usbId: Int32(device.usbId)))
        default:
            throw InitializationError.invalidSynapseVersion
        }
    }
    
    
}
