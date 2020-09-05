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
    
    //  MARK: - Driver Instances
    
    lazy var basiliskDriver: Synapse2Handle = {
        let devices = FruityRazer.devices
        
        let huntsmanEliteHardware = devices.filter { $0.shortName == "basilisk" }[0]
        
        guard case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver else {
            XCTFail("Basilisk not recognized as Synapse 2!")
            
            fatalError()
        }
        
        return driver
    }()
    
    lazy var huntsmanEliteHWDriver: Synapse2Handle = {
        let devices = FruityRazer.devices
        
        let huntsmanEliteHardware = devices.filter { $0.shortName == "huntsman_elite_hw" }[0]
        
        guard case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 2!")
            
            fatalError()
        }
        
        return driver
    }()
    
    //  MARK: - Tests for Razer Huntsman Elite
    
    func testHuntsmanElite_wave() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .wave(direction: .right)))
    }
    
    func testHuntsmanElite_spectrum() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .spectrum))
    }
    
    func testHuntsmanElite_reactive() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .reactive(speed: 1, color: .white)))
    }
    
    func testHuntsmanElite_static() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .static(color: .white)))
    }
    
    func testHuntsmanElite_breath() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .breath(color: .white)))
    }
    
    func testHuntsmanElite_starlight() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .starlight(speed: 100,
                                                                   color1: .white,
                                                                   color2: .red)))
    }
    
    //  MARK: - Tests for Razer Basilisk
    
    func testBasilisk_wave() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertFalse(basiliskDriver.write(mode: .wave(direction: .right)))
    }
    
    func testBasilisk_spectrum() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(basiliskDriver.write(mode: .spectrum))
    }
    
    func testBasilisk_reactive() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(basiliskDriver.write(mode: .reactive(speed: 1, color: .white)))
    }
    
    func testBasilisk_static() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(basiliskDriver.write(mode: .static(color: .white)))
    }
    
    func testBasilisk_breath() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(basiliskDriver.write(mode: .breath(color: .white)))
    }
    
    func testBasilisk_starlight() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertFalse(basiliskDriver.write(mode: .starlight(speed: 100,
                                                             color1: .white,
                                                             color2: .red)))
    }
}
