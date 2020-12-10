//
//  FruityKit.swift
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

import FruityKit.FruityKitC

public struct FruityRazer {
    
    public static var devices: [RazerDevice] {
        let deviceList = dq_get_device_list()
        
        return (0..<deviceList.length).compactMap { i -> RazerDevice? in
            let device = deviceList.devices.advanced(by: Int(i)).pointee
            
            return RazerDevice(device: device)
        }
    }
    
    public static var connectedDevices: [RazerDevice] {
        devices.filter { $0.connected }
    }
    
    public static var groupedDevices: [VersionedRazerDevice] {
        devices.reduce(into: []) { result, currentDevice in
            if currentDevice.shortName.contains("_hw") {
                return
            } else if currentDevice.shortName.contains("_sw") {
                let hwShortName = currentDevice.shortName.dropLast(3).appending("_hw")
                
                guard let hwDevice = devices.first(where: { $0.shortName == hwShortName }) else {
                    preconditionFailure("Found `_sw` device without no `_hw` counterpart!")
                }
                
                result.append(.both(v2: hwDevice, v3: currentDevice))
            } else {
                switch currentDevice.driver.synapseVersion {
                case 2:
                    result.append(.v2(currentDevice))
                case 3:
                    result.append(.v3(currentDevice))
                default:
                    preconditionFailure("`synapseVersion` must be either 2 or 3!")
                }
            }
        }
    }
    
    public static var groupedConnectedDevices: [VersionedRazerDevice] {
        return groupedDevices.filter { $0.connected }
    }
}
