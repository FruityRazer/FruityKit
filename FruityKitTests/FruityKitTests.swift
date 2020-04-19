//
//  FruityKitTests.swift
//  FruityKitTests
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import XCTest
@testable import FruityKit

class FruityKitTests: XCTestCase {

    func testDeviceEnumeration() {
        let devices = FruityRazer.devices
        
        let mamba = devices.filter { $0.shortName == "mamba" }[0]
        let huntsmanEliteHardware = devices.filter { $0.shortName == "huntsman_elite_hw" }[0]
        
        if case let Driver.v2(driver: driver) = mamba.driver {
            XCTAssertFalse(driver.connected)
        } else {
            XCTFail("Mamba not recognized as Synapse 2!")
        }
        
        if case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver {
            XCTAssertTrue(driver.connected)
        } else {
            XCTFail("Huntsman Elite not recognized as Synapse 2!")
        }
    }
}
