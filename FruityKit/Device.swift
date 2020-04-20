//
//  Device.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public enum DeviceType {
    
    public enum KeyboardType {
        case normal
        case keypad
        case laptop
    }
    
    case keyboard(type: KeyboardType)
    case mouse
    case other(type: String)
}

public enum Driver {
    
    case v2(driver: Synapse2Handle)
    case v3(driver: Synapse3Handle)
}

public protocol Device {
    
    var shortName: String { get }
    var fullName: String { get }
    var type: DeviceType { get }
    
    var driver: Driver { get }
}

extension Driver {
    
    static func handle(for device: razer_device) -> Driver {
        guard device.synapse.rawValue == 3 else {
            return .v2(driver: Synapse2Handle(usbId: Int32(device.usbId)))
        }
        
        switch String(cString: device.shortName) {
        case "base_station":
            return .v3(driver: RazerBaseStationHandle(usbId: Int32(device.usbId)))
        case "huntsman_elite_sw":
            return .v3(driver: RazerHuntsmanEliteHandle(usbId: Int32(device.usbId)))
        case "mamba_hyperflux":
            return .v3(driver: RazerMambaHyperfluxHandle(usbId: Int32(device.usbId)))
        default:
            return .v3(driver: Synapse3Handle(usbId: Int32(device.usbId)))
        }
    }
}

public extension Driver {
    
    var synapseVersion: Int {
        if case Driver.v2 = self {
            return 2
        }

        return 3
    }
}
