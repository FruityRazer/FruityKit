//
//  Color.swift
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

/// A struct representing a color.
public struct Color: Hashable {
    
    public enum InitializationError: Error {
        case invalidHexData
        case invalidHexLength
    }
    
    /// The red component of the color.
    public let r: UInt8
    
    /// The green component of the color.
    public let g: UInt8
    
    /// The blue component of the color.
    public let b: UInt8
    
    /// Creates a color with specified components.
    ///
    /// - Parameters:
    ///     - red: The red component of the color.
    ///     - green: The green component of the color.
    ///     - blue: The blue component of the color.
    public init(red: UInt8, green: UInt8, blue: UInt8) {
        r = red
        g = green
        b = blue
    }
    
    private static func parseHex(from string: String) throws -> String {
        switch string.count {
        case 6:
            return string
            
        case 7:
            guard string.first! == "#" else {
                throw InitializationError.invalidHexData
            }
            return String(string.dropFirst())
            
        default:
            throw InitializationError.invalidHexLength
        }
    }
    
    /// Creates a color from a hex string.
    ///
    /// - Parameters:
    ///     - hex: The hex string representing the color.
    public init(hex: String) throws {
        let cleantHex = try Color.parseHex(from: hex)
        
        let redComponent = cleantHex[cleantHex.startIndex..<cleantHex.index(cleantHex.startIndex, offsetBy: 2)]
        let greenComponent = cleantHex[cleantHex.index(cleantHex.startIndex, offsetBy: 2)..<cleantHex.index(cleantHex.startIndex, offsetBy: 4)]
        let blueComponent = cleantHex[cleantHex.index(cleantHex.startIndex, offsetBy: 4)..<cleantHex.index(cleantHex.startIndex, offsetBy: 6)]
        
        r = UInt8(strtoul(String(redComponent), nil, 16))
        g = UInt8(strtoul(String(greenComponent), nil, 16))
        b = UInt8(strtoul(String(blueComponent), nil, 16))
    }
    
    var cArray: UnsafeMutablePointer<UInt8> {
        let ptr = UnsafeMutablePointer<UInt8>.allocate(capacity: 3)
        
        ptr.pointee = r
        ptr.advanced(by: 1).pointee = g
        ptr.advanced(by: 2).pointee = b
        
        return ptr
    }
    
    var razerRGB: razer_rgb {
        razer_rgb(r: r, g: g, b: b)
    }
}

public extension Color {
    
    static var black: Color {
        Color(red: 0, green: 0, blue: 0)
    }
    
    static var white: Color {
        Color(red: 255, green: 255, blue: 255)
    }
}
