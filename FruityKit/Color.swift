//
//  Color.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public struct Color: Hashable {
    
    public enum InitializationError: Error {
        case invalidHexData
        case invalidHexLength
    }
    
    let r: UInt8
    let g: UInt8
    let b: UInt8
    
    public init(red: UInt8, green: UInt8, blue: UInt8) {
        r = red
        g = green
        b = blue
    }
    
    public init(hex: String) throws {
        guard hex.count == 6 || hex.count == 7 else {
            throw InitializationError.invalidHexLength
        }
        
        let cleantHex: String
        
        if hex.count == 7 {
            guard hex.first! == "#" else {
                throw InitializationError.invalidHexData
            }
            
            cleantHex = String(hex.dropFirst())
        } else {
            cleantHex = hex
        }
        
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
        return razer_rgb(r: r, g: g, b: b)
    }
}

extension Color {
    
    static var black: Color {
        Color(red: 0, green: 0, blue: 0)
    }
    
    static var white: Color {
        Color(red: 255, green: 255, blue: 255)
    }
}
