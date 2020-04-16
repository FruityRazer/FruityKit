//
//  Device.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public enum DeviceType {
    case keyboard
    case mouse
    case other(type: String)
}

public enum Driver {
    case v2(driver: Synapse2Handle)
    case v3(driver: Synapse3Handle)
}

public protocol Device {
    var shortName: String { get }
    var fullName: String { get }
    var type: DeviceType { get }
    
    var driver: Driver { get }
}


