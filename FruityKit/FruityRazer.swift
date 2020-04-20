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
}

extension RazerDevice {
    
    var connected: Bool {
        switch driver {
        case .v2(driver: let d):
            return d.connected
        case .v3(driver: let d):
            return d.connected
        }
    }
}
