//
//  Synapse3Tests.swift
//  FruityKitTests
//
//  Created by Eduardo Almeida on 19/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import XCTest
@testable import FruityKit

class Synapse3Tests: XCTestCase {

    func testSpecialized_huntsmanElite_fakeWave() throws {
        let devices = FruityRazer.devices
        
        let huntsmanEliteSoftware = devices.filter { $0.shortName == "huntsman_elite_sw" }[0]
        
        guard case let Driver.v3(driver: driver) = huntsmanEliteSoftware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 3!")
            
            return
        }
        
        guard let specializedDriver = driver as? RazerHuntsmanHandle else {
            XCTFail("Not a specialized huntsman driver!")
            
            return
        }
        
        try XCTSkipIf(!driver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        try! specializedDriver.fakeWave(color: Color(hex: "#FF0000"))
        try! specializedDriver.fakeWave(color: Color(hex: "#00FF00"))
        try! specializedDriver.fakeWave(color: Color(hex: "#0000FF"))
        try! specializedDriver.fakeWave(color: Color(hex: "#FFFFFF"))
    }
    
    func testSpecialized_huntsmanElite_fullWhite() throws {
        let devices = FruityRazer.devices
        
        let huntsmanEliteSoftware = devices.filter { $0.shortName == "huntsman_elite_sw" }[0]
        
        guard case let Driver.v3(driver: driver) = huntsmanEliteSoftware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 3!")
            
            return
        }
        
        guard let specializedDriver = driver as? RazerHuntsmanHandle else {
            XCTFail("Not a specialized huntsman driver!")
            
            return
        }
        
        try XCTSkipIf(!driver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        let rowArray: [Color] = Color.white.repeated(24)
        let fullArray: [[Color]] = rowArray.repeated(9)
        
        XCTAssertTrue(specializedDriver.write(mode: .rawRows(colors: fullArray)))
    }
    
    func testSpecialized_baseStation() throws {
        let devices = FruityRazer.devices
        
        let baseStation = devices.filter { $0.shortName == "base_station" }[0]
        
        guard case let Driver.v3(driver: driver) = baseStation.driver else {
            XCTFail("Base Station not recognized as Synapse 3!")
            
            return
        }
        
        guard let specializedDriver = driver as? RazerBaseStationHandle else {
            XCTFail("Not a specialized base station driver!")
            
            return
        }
        
        try XCTSkipIf(!driver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(specializedDriver.write(mode: .raw(colors: try! Color(hex: "#00FF00").repeated(14))))
    }
    
    func testSpecialized_mambaHyperflux() throws {
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
        
        try XCTSkipIf(!driver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(specializedDriver.write(mode: .raw(colors: try! Color(hex: "#00FF00").repeated(14))))
    }
}
