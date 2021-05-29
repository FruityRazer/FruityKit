//
//  Speed.swift
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

public enum Speed: Int {
    
    case unacceptablySlow = 0xFF
    case slowest = 0xD9
    case slower = 0xB9
    case slow = 0x90
    
    case `default` = 0x70
    
    case fast = 0x55
    case faster = 0x40
    case fastest = 0x25
    case unacceptablyFast = 0x10
}

//  TODO: For FruityUI.

extension Speed {
    
    var stringValue: String {
        switch self {
        case .unacceptablySlow:
            return "Unacceptably Slow"
        case .slowest:
            return "Slowest"
        case .slower:
            return "Slower"
        case .slow:
            return "Slow"
        case .default:
            return "Default"
        case .fast:
            return "Fast"
        case .faster:
            return "Faster"
        case .fastest:
            return "Fastest"
        case .unacceptablyFast:
            return "Unacceptably Fast"
        }
    }
}
