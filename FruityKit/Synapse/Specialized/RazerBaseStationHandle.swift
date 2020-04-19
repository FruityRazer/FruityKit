//
//  RazerBaseStationHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 17/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public final class RazerBaseStationHandle: Synapse3Handle {
    
    override public func write(mode: Mode) {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: 78)
        parts.initialize(to: 0)
        
        guard case let Mode.raw(colors) = mode else {
            return
        }
        
        for i in 0..<14 {
            let current: UnsafeMutablePointer<UInt8>
            
            if i < colors.count {
                current = colors[i].cArray
            } else {
                current = Color.black.cArray
            }
            
            parts.advanced(by: i).pointee = current.pointee
            parts.advanced(by: i + 1).pointee = current.advanced(by: 1).pointee
            parts.advanced(by: i + 2).pointee = current.advanced(by: 2).pointee
        }
        
        razer_base_station_pre(deviceInterface)
        razer_base_station_set_colors(deviceInterface,
                                      UnsafeMutableRawPointer(parts).assumingMemoryBound(to: Int8.self))
    }
}
