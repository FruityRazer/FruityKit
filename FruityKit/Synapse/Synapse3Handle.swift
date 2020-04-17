//
//  Synapse3.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public class Synapse3Handle: SynapseHandle {
    
    public enum Mode {
        case raw(colors: [Color])
    }
    
    public let usbId: Int32
    
    init(usbId: Int32) {
        self.usbId = usbId
    }
    
    public func read() {
        
    }
        
    public func write(mode: Mode) {
        
    }
}
