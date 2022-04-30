//
//  Device.swift
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

/// An enum representing a device type.
public enum DeviceType: Hashable {
    
    public enum KeyboardType {
        case normal
        case keypad
        case laptop
    }
    
    case keyboard(type: KeyboardType)
    case kraken
    case mouse
    case mousepad
    case accessory
    case other(type: String)
}

/// A protocol that all devices conform to.
public protocol Device {
    
    /// The short name of the device, used internally.
    var shortName: String { get }
    
    /// The full name of the device, to be presented to the user.
    var fullName: String { get }
    
    /// The type of the device.
    var type: DeviceType { get }
}
