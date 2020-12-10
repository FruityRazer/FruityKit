//
//  PerformClosuresTests.swift
//  FruityKitTests
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

import XCTest
@testable import FruityKit

class PerformClosuresTests: XCTestCase {
    
    func testPerformWithMixedValuesReturnsTrue() {
        //  Given
        let sequence: [() -> Bool] = [
            { true },
            { false },
            { true },
            { false },
        ]
        
        //  When
        let result = runClosures(sequence: sequence)
        
        //  Then
        XCTAssertTrue(result)
    }
    
    func testPerformWithAllTrueValuesReturnsTrue() {
        //  Given
        let sequence: [() -> Bool] = [
            { true },
            { true },
            { true },
            { true },
        ]
        
        //  When
        let result = runClosures(sequence: sequence)
        
        //  Then
        XCTAssertTrue(result)
    }
    
    func testPerformWithAllFalseValuesReturnsFalse() {
        //  Given
        let sequence: [() -> Bool] = [
            { false },
            { false },
            { false },
            { false },
        ]
        
        //  When
        let result = runClosures(sequence: sequence)
        
        //  Then
        XCTAssertFalse(result)
    }
}
