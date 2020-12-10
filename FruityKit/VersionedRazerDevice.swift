//
//  VersionedRazerDevice.swift
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

public enum VersionedRazerDevice: Device, Hashable {
    
    case v2(RazerDevice)
    case v3(RazerDevice)
    case both(v2: RazerDevice, v3: RazerDevice)
    
    private var device: Device {
        switch self {
        case let .v2(device),
             let .v3(device),
             let .both(v2: device, v3: _):
            return device
        }
    }
    
    public var shortName: String {
        switch self {
        case let .v2(device), let .v3(device):
            return device.shortName
        case let .both(v2: device, v3: _):
            return String(device.shortName.dropLast(3))
        }
    }
    
    public var fullName: String {
        device.fullName
    }
    
    public var type: DeviceType {
        device.type
    }
    
    public var connected: Bool {
        switch self {
        case .v2(let device):
            return device.connected
        case .v3(let device):
            return device.connected
        case .both(let device, _):
            return device.connected
        }
    }
}
