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
            .static,
            .wave
        ]
    }
    
    override func write(mode: BasicMode, deviceInterface: UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, data: UnsafePointer<Int8>!, count: Int) -> Bool {
        switch mode {
        case .breath:
            
            let scrollResult = razer_mouse_attr_write_scroll_mode_breath(deviceInterface, data, count)
            let logoResult = razer_mouse_attr_write_logo_mode_breath(deviceInterface, data, count)
            
            if scrollResult || logoResult {
                return true
            }
            
            //  Set mode to "pulsate" on legacy devices
            
            let effectResult = razer_mouse_attr_write_logo_led_effect(deviceInterface, "2", 1)
            let colorResult = razer_mouse_attr_write_mode_static(deviceInterface, data, 3)
            
            return effectResult || colorResult
            
        case .reactive:
            
            let scrollResult = razer_mouse_attr_write_scroll_mode_reactive(deviceInterface, data, count)
            let logoResult = razer_mouse_attr_write_logo_mode_reactive(deviceInterface, data, count)
            
            if scrollResult || logoResult {
                return true
            }
            
            //  Set mode to "scroll" on legacy devices
            
            let effectResult = razer_mouse_attr_write_logo_led_effect(deviceInterface, "4", 1)
            let colorResult = razer_mouse_attr_write_mode_static(deviceInterface, data, 3)
            
            return effectResult || colorResult
            
        case .spectrum:
            
            let scrollResult = razer_mouse_attr_write_scroll_mode_spectrum(deviceInterface, data, count)
            let logoResult = razer_mouse_attr_write_logo_mode_spectrum(deviceInterface, data, count)
            
            return scrollResult || logoResult
            
        case .starlight:
            
            return false
            
        case .static:
            
            let scrollResult = razer_mouse_attr_write_scroll_mode_static(deviceInterface, data, 3)
            let logoResult = razer_mouse_attr_write_logo_mode_static(deviceInterface, data, 3)
            
            if scrollResult || logoResult {
                return true
            }
            
            let effectResult = razer_mouse_attr_write_logo_led_effect(deviceInterface, "0", 1)
            let colorResult = razer_mouse_attr_write_mode_static(deviceInterface, data, 3)
            
            return effectResult || colorResult
            
        case .wave:
            
            let scrollResult = razer_mouse_attr_write_scroll_mode_wave(deviceInterface, data, count)
            let logoResult = razer_mouse_attr_write_logo_mode_wave(deviceInterface, data, count)
            
            return scrollResult || logoResult
        }
    }
}
