//
//  Synapse2.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

enum Synapse2Mode {
    case wave(direction: Direction)
    case spectrum
    case reactive(speed: Int, color: Color)
    case `static`(color: Color)
    case breath(color: Color)
}

protocol Synapse2Device: Device {
    func read()
    func write(mode: Synapse2Mode)
}

extension Synapse2Device {
    func write(_ mode: Synapse2Mode, for device: razer_device) {
        let deviceInterface = dq_get_device(Int32(device.usbId))
        
        razer_set_device_mode(deviceInterface, 0x00, 0x00)
        
        switch mode {
        case .wave(let direction):
            razer_attr_write_mode_wave(deviceInterface, UnsafePointer<Int8>(bitPattern: direction.rawValue), 1)
        case .spectrum:
            razer_attr_write_mode_spectrum(deviceInterface)
        case .reactive(_, _):
//            razer_attr_write_mode_reactive(deviceInterface, color, 4)
            ()
        case .`static`(let color):
            razer_attr_write_mode_static(deviceInterface, color.rgbArray, 3)
        case .breath(let color):
            razer_attr_write_mode_breath(deviceInterface, color.rgbArray, 3)
        }
    }
}
