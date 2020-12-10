//
//  RazerHuntsmanEliteHandle.swift
//  FruityKit
//

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * Should you need to contact me, the author, you can do so by
 * e-mail - Eduardo Almeida <hello [_at_] edr [_dot_] io>
 */

import Foundation

public final class RazerHuntsmanHandle: Synapse3Handle {
    
    override public func write(mode: Mode) -> Bool {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        switch mode {
        case .off:
            for rowIdx in 0..<9 {
                let capacity = 26 * 3
                
                let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: capacity)
                parts.initialize(to: 0)
                
                defer {
                    parts.deinitialize(count: capacity)
                    parts.deallocate()
                }
                
                for keyIdx in 0..<26 {
                    let current: UnsafeMutablePointer<UInt8> = Color.black.cArray
                    
                    defer {
                        current.deinitialize(count: 3)
                        current.deallocate()
                    }
                    
                    let base = keyIdx * 3
                    
                    parts.advanced(by: base).pointee = current.pointee
                    parts.advanced(by: base + 1).pointee = current.advanced(by: 1).pointee
                    parts.advanced(by: base + 2).pointee = current.advanced(by: 2).pointee
                }
                
                _ = parts.withMemoryRebound(to: Int8.self, capacity: capacity) {
                    razer_huntsman_set_row_raw(deviceInterface,
                                               Int8(rowIdx),
                                               $0,
                                               Int32(25))
                }
            }
            
        case .raw:
            return false
            
        case .rawRows(let rows):
            for rowIdx in 0..<rows.count {
                let capacity = rows[rowIdx].count * 3
                
                let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: capacity)
                parts.initialize(to: 0)
                
                defer {
                    parts.deinitialize(count: capacity)
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
                
                _ = parts.withMemoryRebound(to: Int8.self, capacity: capacity) {
                    razer_huntsman_set_row_raw(deviceInterface,
                                               Int8(rowIdx),
                                               $0,
                                               Int32(rows[rowIdx].count))
                }
            }
        }
        
        return true
    }
}
