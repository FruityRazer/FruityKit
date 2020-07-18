//
//  Driver.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 14/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public protocol HasDriver {
    
    var driver: Driver { get }
}

public enum Driver: Hashable {
    
    case v2(driver: Synapse2Handle)
    case v3(driver: Synapse3Handle)
}

extension Driver {
    
    static func handle(for device: razer_device, type: DeviceType) -> Driver {
        guard device.synapse.rawValue == 3 else {
            switch type {
            case .keyboard:
                return .v2(driver: Synapse2KeyboardHandle(usbId: Int32(device.usbId)))
            case .mouse:
                return .v2(driver: Synapse2MouseHandle(usbId: Int32(device.usbId)))
            default:
                return .v2(driver: Synapse2Handle(usbId: Int32(device.usbId)))
            }
        }
        
        switch String(cString: device.shortName) {
        case "base_station":
            return .v3(driver: RazerBaseStationHandle(usbId: Int32(device.usbId)))
        case "huntsman_sw",
             "huntsman_te_sw",
             "huntsman_elite_sw",
             "huntsman_mini":
            return .v3(driver: RazerHuntsmanHandle(usbId: Int32(device.usbId)))
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
