//
//  Synapse.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation
import IOKit

public protocol SynapseHandle {
    
    associatedtype SynapseMode
    
    var usbId: Int32 { get }
    
    var connected: Bool { get }
    
    func read()
    func write(mode: SynapseMode) -> Bool
}

extension SynapseHandle {
    
    public var connected: Bool {
        dq_check_device_connected(Int32(usbId))
    }
}
