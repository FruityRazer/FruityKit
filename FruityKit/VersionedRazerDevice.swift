//
//  VersionedRazerDevice.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 22/05/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public enum VersionedRazerDevice {
    
    case v2(RazerDevice)
    case v3(RazerDevice)
    case both(v2: RazerDevice, v3: RazerDevice)
    
    internal var connected: Bool {
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
