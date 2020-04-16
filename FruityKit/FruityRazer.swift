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
        
        return (0..<deviceList.length).compactMap { i -> RazerDevice in
            let device = deviceList.devices.advanced(by: Int(i)).pointee
            //  wrong
            return try! RazerDevice(device: device)
        }
    }
    
//    public static var synapse2devices: [Synapse2Device] {
//        
//    }
}


