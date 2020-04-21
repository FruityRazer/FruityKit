//
//  Synapse2.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public struct Synapse2Handle: SynapseHandle {
    
    public enum Mode {
        case wave(direction: Direction)
        case spectrum
        case reactive(speed: Int, color: Color)
        case `static`(color: Color)
        case breath(color: Color)
    }
    
    public let usbId: Int32
    
    public func read() {
        
    }
    
    public func write(mode: Mode) {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        razer_set_device_mode(deviceInterface, 0x00, 0x00)
        
        switch mode {
        case .wave(let direction):
            let ptr = UnsafeMutablePointer<Int8>.allocate(capacity: 1)
            ptr.pointee = Int8(direction.rawValue)
            
            razer_attr_write_mode_wave(deviceInterface, ptr, 1)
            
        case .spectrum:
            razer_attr_write_mode_spectrum(deviceInterface)
            
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
            
            razer_attr_write_mode_reactive(deviceInterface, ptr, 4)
            
        case .`static`(let color):
            let ptr = UnsafeRawPointer(color.cArray).assumingMemoryBound(to: Int8.self)
            
            defer {
                ptr.deallocate()
            }
            
            razer_attr_write_mode_static(deviceInterface, ptr, 3)
            
        case .breath(let color):
            let ptr = UnsafeRawPointer(color.cArray).assumingMemoryBound(to: Int8.self)
            
            defer {
                ptr.deallocate()
            }
            
            razer_attr_write_mode_breath(deviceInterface, ptr, 3)
        }
    }
}
