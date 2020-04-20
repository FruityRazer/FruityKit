//
//  RazerSoftwareSingleRowHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 20/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

import IOKit.usb.IOUSBLib

public class RazerSoftwareSingleRowHandle: Synapse3Handle {
    
    typealias CommitFunction = (UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, UnsafeMutablePointer<Int8>) -> ()
    
    let commitFunction: CommitFunction
    
    init(usbId: Int32, commitFunction: @escaping CommitFunction) {
        self.commitFunction = commitFunction
        
        super.init(usbId: usbId)
    }
    
    override public func write(mode: Mode) {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        let parts = UnsafeMutablePointer<UInt8>.allocate(capacity: 78)
        parts.initialize(to: 0)
        
        defer {
            parts.deallocate()
        }
        
        guard case let Mode.raw(colors) = mode else {
            return
        }
        
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
        
        commitFunction(deviceInterface, UnsafeMutableRawPointer(parts).assumingMemoryBound(to: Int8.self))
    }
}
