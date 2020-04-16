//
//  Device.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

enum DeviceType {
    case keyboard
    case mouse
    case other(type: String)
}

protocol Device {
    var shortName: String { get }
    var fullName: String { get }
    var usbId: Int { get }
    var type: DeviceType { get }
}


