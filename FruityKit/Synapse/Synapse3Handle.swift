//
//  Synapse3.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public class Synapse3Handle: SynapseHandle {
    
    public enum Mode: Hashable {
        case off
        case raw(colors: [Color])
        case rawRows(colors: [[Color]])
    }
    
    public let usbId: Int32
    
    init(usbId: Int32) {
        self.usbId = usbId
    }
    
    public func read() {
        fatalError("This function should be overidden.")
    }
        
    public func write(mode: Mode) -> Bool {
        fatalError("This function should be overidden.")
    }
}

extension Synapse3Handle: Hashable {
    public static func == (lhs: Synapse3Handle, rhs: Synapse3Handle) -> Bool {
        return true
    }
    
    public func hash(into hasher: inout Hasher) {
        hasher.combine(usbId)
    }
}
