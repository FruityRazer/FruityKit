//
//  FruityRazer.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

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
                let hwShortName = currentDevice.shortName.dropLast(3).appending("_sw")
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
