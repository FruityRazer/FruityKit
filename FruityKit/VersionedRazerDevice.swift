//
//  VersionedRazerDevice.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 22/05/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

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
        device.shortName
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
