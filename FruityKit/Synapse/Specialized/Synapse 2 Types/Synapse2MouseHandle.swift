//
//  Synapse2MouseHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 14/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

final class Synapse2MouseHandle: Synapse2Handle {
    
    override var supportedModes: [Mode.Basic] {
        [
            .breath,
            .reactive,
            .spectrum,
            .static,
            .wave
        ]
    }
    
    override func write(mode: Mode.Basic, deviceInterface: DeviceInterface, data: UnsafePointer<Int8>!, count: Int) -> Bool {
        switch mode {
        case .breath:
            return runClosures(sequence: [
                { razer_mouse_attr_write_scroll_mode_breath(deviceInterface, data, count) },
                { razer_mouse_attr_write_logo_mode_breath(deviceInterface, data, count) },
                { razer_mouse_attr_write_left_mode_breath(deviceInterface, data, 3) },
                { razer_mouse_attr_write_right_mode_breath(deviceInterface, data, 3) },
                { razer_mouse_attr_write_logo_led_effect(deviceInterface, "2", 1) },
                { razer_mouse_attr_write_mode_static(deviceInterface, data, 3) },
            ])
            
        case .reactive:
            return runClosures(sequence: [
                { razer_mouse_attr_write_scroll_mode_reactive(deviceInterface, data, count) },
                { razer_mouse_attr_write_logo_mode_reactive(deviceInterface, data, count) },
                { razer_mouse_attr_write_left_mode_reactive(deviceInterface, data, 3) },
                { razer_mouse_attr_write_right_mode_reactive(deviceInterface, data, 3) },
                { razer_mouse_attr_write_logo_led_effect(deviceInterface, "4", 1) },
                { razer_mouse_attr_write_mode_static(deviceInterface, data, 3) }
            ])
            
        case .spectrum:
            return runClosures(sequence: [
                { razer_mouse_attr_write_scroll_mode_spectrum(deviceInterface, data, count) },
                { razer_mouse_attr_write_logo_mode_spectrum(deviceInterface, data, count) },
                { razer_mouse_attr_write_left_mode_spectrum(deviceInterface, data, 3) },
                { razer_mouse_attr_write_right_mode_spectrum(deviceInterface, data, 3) },
            ])
            
        case .starlight:
            return false
            
        case .static:
            return runClosures(sequence: [
                { razer_mouse_attr_write_scroll_mode_static(deviceInterface, data, 3) },
                { razer_mouse_attr_write_logo_mode_static(deviceInterface, data, 3) },
                { razer_mouse_attr_write_left_mode_static(deviceInterface, data, 3) },
                { razer_mouse_attr_write_right_mode_static(deviceInterface, data, 3) },
                { razer_mouse_attr_write_logo_led_effect(deviceInterface, "0", 1) },
                { razer_mouse_attr_write_mode_static(deviceInterface, data, 3) }
            ])
            
        case .wave:
            return runClosures(sequence: [
                { razer_mouse_attr_write_scroll_mode_wave(deviceInterface, data, count) },
                { razer_mouse_attr_write_logo_mode_wave(deviceInterface, data, count) },
                { razer_mouse_attr_write_left_mode_wave(deviceInterface, data, count) },
                { razer_mouse_attr_write_right_mode_wave(deviceInterface, data, count) },
            ])
        }
    }
    
    override func read(setting: Synapse2Handle.Setting.Basic, deviceInterface: DeviceInterface) -> (data: UnsafePointer<Int8>, count: Int)? {
        switch setting {
        case .dpi:
            let capacity = 32
            
            let ptr = UnsafeMutablePointer<Int8>.allocate(capacity: capacity)
            
            ptr.initialize(repeating: 0, count: capacity)
            
            guard razer_attr_read_mouse_dpi(deviceInterface, ptr) != -1 else { return nil }
            
            return (UnsafePointer(ptr), capacity)
        }
    }
}
