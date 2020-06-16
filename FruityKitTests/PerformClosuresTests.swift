//
//  PerformClosuresTests.swift
//  FruityKitTests
//
//  Created by Eduardo Almeida on 16/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

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
