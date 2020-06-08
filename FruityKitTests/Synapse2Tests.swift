//
//  Synapse2Tests.swift
//  FruityKitTests
//
//  Created by Eduardo Almeida on 19/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import XCTest
@testable import FruityKit

class Synapse2Tests: XCTestCase {
    
    var huntsmanEliteHWDriver: Synapse2Handle {
        let devices = FruityRazer.devices
        
        let huntsmanEliteHardware = devices.filter { $0.shortName == "huntsman_elite_hw" }[0]
        
        guard case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 2!")
            
            fatalError()
        }
        
        return driver
    }
    
    func testHuntsmanElite_wave() {
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .wave(direction: .right)))
    }
    
    func testHuntsmanElite_spectrum() {
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .spectrum))
    }
    
    func testHuntsmanElite_reactive() {
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .reactive(speed: 100, color: .white)))
    }
    
    func testHuntsmanElite_static() {
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .static(color: .white)))
    }
    
    func testHuntsmanElite_breath() {
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .breath(color: .white)))
    }
}
