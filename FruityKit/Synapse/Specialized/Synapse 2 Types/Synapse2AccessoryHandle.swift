//
//  Synapse2AccessoryHandle.swift
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

final class Synapse2AccessoryHandle: Synapse2Handle {
    
    override var supportedModes: [BasicMode] {
        [
            .breath,
            .spectrum,
            .static,
            .wave
        ]
    }
    
    override var speedSupported: Bool { true }
    
    override func write(mode: BasicMode, deviceInterface: UnsafeMutablePointer<UnsafeMutablePointer<IOUSBDeviceInterface>?>?, data: UnsafePointer<Int8>!, count: Int, additionalData: Int32? = nil) -> Bool {
        switch mode {
        case .breath:
            return razer_accessory_attr_write_mode_breath(deviceInterface, data, count) == count
        case .spectrum:
            return razer_accessory_attr_write_mode_spectrum(deviceInterface, data, count) == count
        case .static:
            return razer_accessory_attr_write_mode_static(deviceInterface, data, count) == count
        case .wave:
            guard let additionalData = additionalData else { return false }
            
            return razer_accessory_attr_write_mode_wave(deviceInterface, data, count, Int32(additionalData)) == count
        case .reactive, .starlight:
            return false
        }
    }
}
