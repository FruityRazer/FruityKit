//
//  RazerDevice.swift
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

public struct RazerDevice: Device, HasDriver, Hashable {
    
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
        case 8:
            type = .other(type: "accessory")
        default:
            type = .other(type: "unknown")
        }
        
        driver = Driver.handle(for: device, type: type)
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
