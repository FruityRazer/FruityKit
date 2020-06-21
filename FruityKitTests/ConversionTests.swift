//
//  ConversionTests.swift
//  FruityKitTests
//
//  Created by Eduardo Almeida on 21/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import XCTest
@testable import FruityKit

class ConversionTests: XCTestCase {

    var huntsmanEliteHWDriver: Synapse2Handle {
        let devices = FruityRazer.devices
        
        let huntsmanEliteHardware = devices.filter { $0.shortName == "huntsman_elite_hw" }[0]
        
        guard case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 2!")
            
            fatalError()
        }
        
        return driver
    }
    
    func testSynapse2_doesNotCrashWhenSpeedIsGreaterThanUInt8Max() {
        XCTAssertFalse(huntsmanEliteHWDriver.write(mode: .reactive(speed: 100000000, color: .white)))
    }
    
    func testSynapse3_doesNotCrashWhenPassedInvalidColors() {
        let devices = FruityRazer.devices
        
        let baseStation = devices.filter { $0.shortName == "mamba_hyperflux" }[0]
        
        guard case let Driver.v3(driver: driver) = baseStation.driver else {
            XCTFail("Mamba Hyperflux not recognized as Synapse 3!")
            
            return
        }
        
        guard let specializedDriver = driver as? RazerMambaHyperfluxHandle else {
            XCTFail("Not a specialized mamba hyperflux driver!")
            
            return
        }
        
        XCTAssertTrue(specializedDriver.write(mode: .raw(colors: try! Color(hex: "#zzzzzz").repeated(14))))
    }
}
