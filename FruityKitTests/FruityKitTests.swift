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
    
    func testHuntsmanEliteAsSynapse2() {
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
    
    func testHuntsmanEliteAsSpecializedSynapse3_fakeWave() {
        let devices = FruityRazer.devices
        
        let huntsmanEliteSoftware = devices.filter { $0.shortName == "huntsman_elite_sw" }[0]
        
        guard case let Driver.v3(driver: driver) = huntsmanEliteSoftware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 3!")
            
            return
        }
        
        guard let specializedDriver = driver as? RazerHuntsmanEliteHandle else {
            XCTFail("Not a specialized huntsman driver!")
            
            return
        }
        
        try! specializedDriver.fakeWave(color: Color(hex: "#FF0000"))
        try! specializedDriver.fakeWave(color: Color(hex: "#00FF00"))
        try! specializedDriver.fakeWave(color: Color(hex: "#0000FF"))
        try! specializedDriver.fakeWave(color: Color(hex: "#FFFFFF"))
    }
    
    func testHuntsmanEliteAsSpecializedSynapse3_someWhites() {
        let devices = FruityRazer.devices
        
        let huntsmanEliteSoftware = devices.filter { $0.shortName == "huntsman_elite_sw" }[0]
        
        guard case let Driver.v3(driver: driver) = huntsmanEliteSoftware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 3!")
            
            return
        }
        
        guard let specializedDriver = driver as? RazerHuntsmanEliteHandle else {
            XCTFail("Not a specialized huntsman driver!")
            
            return
        }
        
        specializedDriver.write(mode: .raw(colors: [.white, .white, .white, .white, .white]))
    }
    
    func testBaseStationAsSpecializedSynapse3() {
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
        
        specializedDriver.write(mode: .raw(colors: [
            .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white
        ]))
    }
}
