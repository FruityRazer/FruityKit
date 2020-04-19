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

    func testHuntsmanElite_white() {
        let devices = FruityRazer.devices
        
        let huntsmanEliteHardware = devices.filter { $0.shortName == "huntsman_elite_hw" }[0]
        
        guard case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 2!")
            
            return
        }
        
        do {
            try driver.write(mode: .static(color: Color(hex: "#ffffff")))
        } catch {
            XCTFail("Unable to write to keyboard!")
        }
    }
}
