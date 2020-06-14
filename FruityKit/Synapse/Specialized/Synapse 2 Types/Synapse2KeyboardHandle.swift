//
//  Synapse2KeyboardHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 14/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

final class Synapse2KeyboardHandle: Synapse2Handle {
    
    override func write(mode: BasicMode, deviceInterface: UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, data: UnsafePointer<Int8>!, count: Int) -> Bool {
        switch mode {
        case .breath:
            return razer_kbd_attr_write_mode_breath(deviceInterface, data, count) != 0
        case .reactive:
            return razer_kbd_attr_write_mode_reactive(deviceInterface, data, count) != 0
        case .spectrum:
            return razer_kbd_attr_write_mode_spectrum(deviceInterface) != 0
        case .starlight:
            return razer_kbd_attr_write_mode_starlight(deviceInterface, data, count) != 0
        case .static:
            return razer_kbd_attr_write_mode_static(deviceInterface, data, count) != 0
        case .wave:
            return razer_kbd_attr_write_mode_wave(deviceInterface, data, count) != 0
        }
    }
}
