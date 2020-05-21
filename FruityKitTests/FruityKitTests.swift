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
        XCTAssertEqual(FruityRazer.connectedDevices.count, 5)
        
        XCTAssertEqual(FruityRazer.connectedDevices.filter { $0.driver.synapseVersion == 2 } .count, 2)
        XCTAssertEqual(FruityRazer.connectedDevices.filter { $0.driver.synapseVersion == 3 } .count, 3)
    }
    
    func testGroupedDeviceEnumeration() {
        XCTAssertEqual(FruityRazer.groupedConnectedDevices.count, 4)
        
        XCTAssertEqual(FruityRazer.groupedConnectedDevices.filter { guard case VersionedRazerDevice.v2 = $0 else { return false }; return true }.count, 1)
        XCTAssertEqual(FruityRazer.groupedConnectedDevices.filter { guard case VersionedRazerDevice.v3 = $0 else { return false }; return true }.count, 2)
        XCTAssertEqual(FruityRazer.groupedConnectedDevices.filter { guard case VersionedRazerDevice.both = $0 else { return false }; return true }.count, 1)
    }
    
    func testSynapseDriverAssignment() {
        let devices = FruityRazer.devices
        
        let mamba = devices.filter { $0.shortName == "mamba" }[0]
        let huntsmanEliteHardware = devices.filter { $0.shortName == "huntsman_elite_hw" }[0]
        let huntsmanEliteSoftware = devices.filter { $0.shortName == "huntsman_elite_sw" }[0]
        
        if case Driver.v3(driver: _) = mamba.driver {
            XCTFail("Mamba not recognized as Synapse 2!")
        }
        
        if case Driver.v3(driver: _) = huntsmanEliteHardware.driver {
            XCTFail("Huntsman Elite (HW) not recognized as Synapse 2!")
        }
        
        if case Driver.v2(driver: _) = huntsmanEliteSoftware.driver {
            XCTFail("Huntsman Elite (SW) not recognized as Synapse 3!")
        }
    }
}
