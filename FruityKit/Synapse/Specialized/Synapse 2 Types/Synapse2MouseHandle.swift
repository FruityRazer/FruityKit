//
//  Synapse2MouseHandle.swift
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
    
    override func write(mode: BasicMode, deviceInterface: UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, data: UnsafePointer<Int8>!, count: Int, additionalData: Int32? = nil) -> Bool {
        switch mode {
        case .breath:
            
            return runClosures(sequence: [
                { razer_attr_write_scroll_mode_breath(deviceInterface, data, count) == count },
                { razer_attr_write_logo_mode_breath(deviceInterface, data, count) == count },
                { razer_attr_write_left_mode_breath(deviceInterface, data, 3) == 3 },
                { razer_attr_write_right_mode_breath(deviceInterface, data, 3) == 3 },
                { razer_attr_write_logo_led_effect(deviceInterface, "2", 1) == 1 },
                { razer_attr_write_mode_static(deviceInterface, data, 3) == 3 },
            ])
            
        case .reactive:
            
            return runClosures(sequence: [
                { razer_attr_write_scroll_mode_reactive(deviceInterface, data, count) == count },
                { razer_attr_write_logo_mode_reactive(deviceInterface, data, count) == count },
                { razer_attr_write_left_mode_reactive(deviceInterface, data, 3) == 3 },
                { razer_attr_write_right_mode_reactive(deviceInterface, data, 3) == 3 },
                { razer_attr_write_logo_led_effect(deviceInterface, "4", 1) == 1 },
                { razer_attr_write_mode_static(deviceInterface, data, 3) == 3 }
            ])
            
        case .spectrum:
            
            return runClosures(sequence: [
                { razer_attr_write_scroll_mode_spectrum(deviceInterface, data, count) == count },
                { razer_attr_write_logo_mode_spectrum(deviceInterface, data, count) == count },
                { razer_attr_write_left_mode_spectrum(deviceInterface, data, 3) == 3 },
                { razer_attr_write_right_mode_spectrum(deviceInterface, data, 3) == 3 },
            ])
            
        case .starlight:
            
            return false
            
        case .static:
            
            return runClosures(sequence: [
                { razer_attr_write_scroll_mode_static(deviceInterface, data, 3) == 3 },
                { razer_attr_write_logo_mode_static(deviceInterface, data, 3) == 3 },
                { razer_attr_write_left_mode_static(deviceInterface, data, 3) == 3 },
                { razer_attr_write_right_mode_static(deviceInterface, data, 3) == 3 },
                { razer_attr_write_logo_led_effect(deviceInterface, "0", 1) == 1 },
                { razer_attr_write_mode_static(deviceInterface, data, 3) == 3 }
            ])
            
        case .wave:
            
            return runClosures(sequence: [
                { razer_attr_write_scroll_mode_wave(deviceInterface, data, count) == count },
                { razer_attr_write_logo_mode_wave(deviceInterface, data, count) == count },
                { razer_attr_write_left_mode_wave(deviceInterface, data, count) == count },
                { razer_attr_write_right_mode_wave(deviceInterface, data, count) == count },
            ])
        }
    }
}
