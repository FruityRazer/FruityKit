//
//  Driver.swift
//  FruityKit
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
