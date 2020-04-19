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

    func testSpecialized_huntsmanElite_fakeWave() {
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
    
    func testSpecialized_huntsmanElite_fullWhite() {
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
        
        specializedDriver.write(mode: .rawRows(colors:
            [
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white],
                [.white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white, .white]
            ]
        ))
    }
    
    func testSpecialized_baseStation() {
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
