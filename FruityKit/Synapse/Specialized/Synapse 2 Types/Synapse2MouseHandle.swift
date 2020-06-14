//
//  Synapse2MouseHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 14/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

final class Synapse2MouseHandle: Synapse2Handle {
    
    override var supportedModes: [BasicMode] {
        [
            .breath,
            .reactive,
            .spectrum,
            .starlight,
            .wave
        ]
    }
    
    override func write(mode: BasicMode, deviceInterface: UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, data: UnsafePointer<Int8>!, count: Int) -> Bool {
        switch mode {
        case .breath:
            return razer_mouse_attr_write_mode_breath(deviceInterface, data, count)
        case .reactive:
            return razer_mouse_attr_write_mode_reactive(deviceInterface, data, count)
        case .spectrum:
            return razer_mouse_attr_write_mode_spectrum(deviceInterface)
        case .starlight:
            assertionFailure("Starlight is unsupported on mice.")
            return false
        case .static:
            return razer_mouse_attr_write_mode_static(deviceInterface, data, count)
        case .wave:
            return razer_mouse_attr_write_mode_wave(deviceInterface, data, count)
        }
    }
}
