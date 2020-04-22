//
//  RazerDevice.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public struct RazerDevice: Device, Hashable {
    
    public let shortName: String
    public let fullName: String
    public let type: DeviceType
    
    public let driver: Driver
}

extension RazerDevice {
    
    init(device: razer_device) {
        shortName = String(cString: device.shortName)
        fullName = String(cString: device.fullName)
        
        switch device.type.rawValue {
        case 0:
            type = .other(type: "headphones")
        case 1:
            type = .keyboard(type: .normal)
        case 2:
            type = .keyboard(type: .keypad)
        case 3:
            type = .keyboard(type: .laptop)
        case 4:
            type = .other(type: "misc_basestation")
        case 5:
            type = .other(type: "misc_hyperflux")
        case 6:
            type = .mouse
        case 7:
            type = .other(type: "mousepad")
        default:
            type = .other(type: "unknown")
        }
        
        driver = Driver.handle(for: device)
    }
}

public extension RazerDevice {
    
    var connected: Bool {
        switch driver {
        case .v2(driver: let d):
            return d.connected
        case .v3(driver: let d):
            return d.connected
        }
    }
}
