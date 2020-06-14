//
//  Synapse2.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

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
    
    enum BasicMode {
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
    
    public func read() {
        fatalError("Not implemented.")
    }
    
    public func write(mode: Mode) -> Bool {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        razer_set_device_mode(deviceInterface, 0x00, 0x00)
        
        switch mode {
        case .wave(let direction):
            let ptr = UnsafeMutablePointer<Int8>.allocate(capacity: 1)
            ptr.pointee = Int8(direction.rawValue)
            
            return write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: ptr, count: 1)
            
        case .spectrum:
            return write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: nil, count: 0)
            
        case .reactive(let speed, let color):
            let colorPtr = color.cArray
            
            let intermediatePtr = UnsafeMutablePointer<UInt8>.allocate(capacity: 4)
            
            defer {
                intermediatePtr.deallocate()
            }
            
            intermediatePtr.pointee = UInt8(speed)
            intermediatePtr.advanced(by: 1).pointee = colorPtr.pointee
            intermediatePtr.advanced(by: 2).pointee = colorPtr.advanced(by: 1).pointee
            intermediatePtr.advanced(by: 3).pointee = colorPtr.advanced(by: 2).pointee
            
            let ptr = UnsafeRawPointer(intermediatePtr).assumingMemoryBound(to: Int8.self)
            
            //  No need to deallocate `ptr` since we aren't allocating anything, just
            //  changing the type of `intermediatePtr`.
            
            return write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: ptr, count: 4)
            
        case .`static`(let color), .breath(let color):
            let ptr = UnsafeRawPointer(color.cArray).assumingMemoryBound(to: Int8.self)
            
            defer {
                ptr.deallocate()
            }
            
            return write(mode: BasicMode(mode: mode), deviceInterface: deviceInterface, data: ptr, count: 3)
            
        case .starlight(let speed, let color1, let color2):
            return false
        }
    }
    
    func write(mode: BasicMode, deviceInterface: UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, data: UnsafePointer<Int8>!, count: Int) -> Bool {
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
