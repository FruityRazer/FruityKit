//
//  RazerHuntsmanEliteHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 17/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public final class RazerHuntsmanEliteHandle: Synapse3Handle {
    
    override public func write(mode: Mode) -> Bool {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        switch mode {
        case .off:
            for rowIdx in 0..<9 {
                let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: 26*3)
                parts.initialize(to: 0)
                
                defer {
                    parts.deallocate()
                }
                
                for keyIdx in 0..<26 {
                    let current: UnsafeMutablePointer<UInt8> = Color.black.cArray
                    
//                    defer {
//                        current.deallocate()
//                    }
                    
                    let base = keyIdx * 3
                    
                    parts.advanced(by: base).pointee = current.pointee
                    parts.advanced(by: base + 1).pointee = current.advanced(by: 1).pointee
                    parts.advanced(by: base + 2).pointee = current.advanced(by: 2).pointee
                }
                
                razer_huntsman_set_row_raw(deviceInterface,
                                           Int8(rowIdx),
                                           UnsafeMutableRawPointer(parts).assumingMemoryBound(to: Int8.self),
                                           Int32(25))
            }
            
        case .raw:
            return false
            
        case .rawRows(let rows):
            for rowIdx in 0..<rows.count {
                let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: rows[rowIdx].count * 3)
                parts.initialize(to: 0)
                
                defer {
                    parts.deallocate()
                }
                
                for keyIdx in 0..<rows[rowIdx].count {
                    let current: UnsafeMutablePointer<UInt8>
                    
                    defer {
                        current.deallocate()
                    }
                    
                    if rows.count > rowIdx && rows[rowIdx].count > keyIdx {
                        current = rows[rowIdx][keyIdx].cArray
                    } else {
                        current = Color.black.cArray
                    }
                    
                    let base = keyIdx * 3
                    
                    parts.advanced(by: base).pointee = current.pointee
                    parts.advanced(by: base + 1).pointee = current.advanced(by: 1).pointee
                    parts.advanced(by: base + 2).pointee = current.advanced(by: 2).pointee
                }
                
                razer_huntsman_set_row_raw(deviceInterface,
                                           Int8(rowIdx),
                                           UnsafeMutableRawPointer(parts).assumingMemoryBound(to: Int8.self),
                                           Int32(rows[rowIdx].count))
            }
        }
        
        return true
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
