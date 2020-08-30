//
//  Device.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public enum DeviceType: Hashable {
    
    public enum KeyboardType {
        
        case normal
        case keypad
        case laptop
    }
    
    case keyboard(type: KeyboardType)
    case mouse
    case other(type: String)
}

public protocol Device {
    
    var shortName: String { get }
    var fullName: String { get }
    var type: DeviceType { get }
}
