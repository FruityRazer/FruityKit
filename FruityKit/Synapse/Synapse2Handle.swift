//
//  Synapse2.swift
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

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////  TODO: Investigate the `speed` parameter on both `reactive`  //////
//////  and `starlight`. It doesn't appear to be doing anything     //////
//////  (and, worse, appears to need to be 1 on reactive).          //////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

import Foundation

public class Synapse2Handle: SynapseHandle {
    
    public enum Mode {
        case breath(color: Color)
        case reactive(speed: Int, color: Color)
        case spectrum
        case starlight(speed: Int, color1: Color, color2: Color)
        case `static`(color: Color)
        case wave(direction: Direction)
    }
    
    public enum BasicMode {
        case breath
        case reactive
        case spectrum
        case starlight
        case `static`
        case wave
        
        init(mode: Mode) {
            switch mode {
            case .breath:
                self = .breath
            case .reactive:
                self = .reactive
            case .spectrum:
                self = .spectrum
            case .starlight:
                self = .starlight
            case .static:
                self = .static
            case .wave:
                self = .wave
            }
        }
    }
    
    init(usbId: Int32) {
        self.usbId = usbId
    }
    
    public let usbId: Int32
    
    public var supportedModes: [BasicMode] {
        assertionFailure("This class must be overidden.")
        
        return []
    }
    
    public func read() {
        fatalError("Not implemented.")
    }
    
    public func write(mode: Mode) -> Bool {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        //  razer_set_device_mode(deviceInterface, 0x00, 0x00)
        
        switch mode {
        case .wave(let direction):
            let ptr = UnsafeMutablePointer<Int8>.allocate(capacity: 1)
            
            defer {
                ptr.deinitialize(count: 1)
                ptr.deallocate()
            }
            
            ptr.pointee = Int8(direction.rawValue)
            
            return write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: ptr, count: 1)
            
        case .spectrum:
            return write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: nil, count: 0)
            
        case .reactive(let speed, let color):
            if speed > UInt8.max {
                return false
            }
            
            let colorPtr = color.cArray
            
            let capacity = 4
            
            let ptr = UnsafeMutablePointer<UInt8>.allocate(capacity: capacity)
            
            defer {
                ptr.deinitialize(count: capacity)
                ptr.deallocate()
            }
            
            ptr.pointee = UInt8(speed)
            ptr.advanced(by: 1).pointee = colorPtr.pointee
            ptr.advanced(by: 2).pointee = colorPtr.advanced(by: 1).pointee
            ptr.advanced(by: 3).pointee = colorPtr.advanced(by: 2).pointee
            
            return ptr.withMemoryRebound(to: Int8.self, capacity: capacity) {
                write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: $0, count: capacity)
            }
            
        case .`static`(let color), .breath(let color):
            let capacity = 3
            
            return color.cArray.withMemoryRebound(to: Int8.self, capacity: capacity) {
                write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: $0, count: capacity)
            }
            
        case .starlight(let speed, let color1, let color2):
            if speed > UInt8.max {
                return false
            }
            
            let color1Ptr = color1.cArray
            let color2Ptr = color2.cArray
            
            let capacity = 7
            
            let ptr = UnsafeMutablePointer<UInt8>.allocate(capacity: capacity)
            
            defer {
                ptr.deinitialize(count: capacity)
                ptr.deallocate()
            }
            
            ptr.pointee = UInt8(speed)
            ptr.advanced(by: 1).pointee = color1Ptr.pointee
            ptr.advanced(by: 2).pointee = color1Ptr.advanced(by: 1).pointee
            ptr.advanced(by: 3).pointee = color1Ptr.advanced(by: 2).pointee
            ptr.advanced(by: 4).pointee = color2Ptr.pointee
            ptr.advanced(by: 5).pointee = color2Ptr.advanced(by: 1).pointee
            ptr.advanced(by: 6).pointee = color2Ptr.advanced(by: 2).pointee
            
            return ptr.withMemoryRebound(to: Int8.self, capacity: capacity) {
                write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: $0, count: capacity)
            }
        }
    }
    
    func write(mode: BasicMode, deviceInterface: UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, data: UnsafePointer<Int8>!, count: Int) -> Bool {
        assertionFailure("This class must be overidden.")
        
        return false
    }
}

extension Synapse2Handle: Hashable {
    
    public static func == (lhs: Synapse2Handle, rhs: Synapse2Handle) -> Bool {
        return lhs.usbId == rhs.usbId
    }
    
    public func hash(into hasher: inout Hasher) {
        return hasher.combine(ObjectIdentifier(self))
    }
}
