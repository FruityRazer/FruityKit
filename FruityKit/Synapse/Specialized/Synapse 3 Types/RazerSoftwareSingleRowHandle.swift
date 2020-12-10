//
//  RazerSoftwareSingleRowHandle.swift
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

import IOKit.usb.IOUSBLib

public class RazerSoftwareSingleRowHandle: Synapse3Handle {
    
    typealias CommitFunction = (UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, UnsafeMutablePointer<Int8>) -> ()
    
    let commitFunction: CommitFunction
    
    init(usbId: Int32, commitFunction: @escaping CommitFunction) {
        self.commitFunction = commitFunction
        
        super.init(usbId: usbId)
    }
    
    override public func write(mode: Mode) -> Bool {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        let capacity = 78
        
        let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: capacity)
        parts.initialize(to: 0)
        
        defer {
            parts.deinitialize(count: capacity)
            parts.deallocate()
        }
        
        switch mode {
        case .off:
            for i in 0..<13 {
                let current: UnsafeMutablePointer<UInt8> = Color.black.cArray
                
                defer {
                    current.deallocate()
                }
                
                let base = i * 3
                
                parts.advanced(by: base).pointee = Color.black.cArray.pointee
                parts.advanced(by: base + 1).pointee = Color.black.cArray.advanced(by: 1).pointee
                parts.advanced(by: base + 2).pointee = Color.black.cArray.advanced(by: 2).pointee
            }
            
        case .raw(colors: let colors):
            for i in 0..<colors.count {
                let current: UnsafeMutablePointer<UInt8>
                
                defer {
                    current.deallocate()
                }
                
                if i < colors.count {
                    current = colors[i].cArray
                } else {
                    current = Color.black.cArray
                }
                
                let base = i * 3
                
                parts.advanced(by: base).pointee = current.pointee
                parts.advanced(by: base + 1).pointee = current.advanced(by: 1).pointee
                parts.advanced(by: base + 2).pointee = current.advanced(by: 2).pointee
            }
            
        case .rawRows(_):
            return false
        }
        
        parts.withMemoryRebound(to: Int8.self, capacity: capacity) {
            commitFunction(deviceInterface, $0)
        }
        
        return true
    }
}
