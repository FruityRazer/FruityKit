//
//  RazerHuntsmanEliteHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 17/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public final class RazerHuntsmanEliteHandle: Synapse3Handle {
    
    override public func write(mode: Mode) {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        guard case let Mode.raw(colors) = mode else {
            return
        }
        
        for row in 0..<8 {
            for i in (row * 25)..<max(colors.count, (row * 25) + 25) {
                let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: 78)
                parts.initialize(to: 0)
                
                let current: UnsafeMutablePointer<UInt8>
                
                if i < colors.count {
                    current = colors[i].cArray
                } else {
                    current = Color.black.cArray
                }
                
                parts.advanced(by: i % 25).pointee = current.pointee
                parts.advanced(by: (i + 1) % 25).pointee = current.advanced(by: 1).pointee
                parts.advanced(by: (i + 2) % 25).pointee = current.advanced(by: 2).pointee
                
                razer_huntsman_set_row_raw(deviceInterface, Int8(row), UnsafeMutableRawPointer(parts).assumingMemoryBound(to: Int8.self), 25)
            }
        }
    }
}

extension RazerHuntsmanEliteHandle {
    
     func fakeWave(color: Color) {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        var rgb = color.razerRGB
        
        razer_huntsman_fake_wave_one_run(deviceInterface, &rgb)
    }
}
