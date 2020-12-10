//
//  FruityKitTests.swift
//  FruityKitTests
//

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * Should you need to contact me, the author, you can do so by
 * e-mail - Eduardo Almeida <hello [_at_] edr [_dot_] io>
 */

import XCTest
import FruityKit

class FruityKitTests: XCTestCase {

    func testDeviceEnumeration() throws {
        try XCTSkipIf(FruityRazer.connectedDevices.count != 4, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertEqual(FruityRazer.connectedDevices.filter { $0.driver.synapseVersion == 2 } .count, 1)
        XCTAssertEqual(FruityRazer.connectedDevices.filter { $0.driver.synapseVersion == 3 } .count, 3)
    }
    
    func testGroupedDeviceEnumeration() throws {
        try XCTSkipIf(FruityRazer.groupedConnectedDevices.count != 3, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertEqual(FruityRazer.groupedConnectedDevices.filter { guard case VersionedRazerDevice.v2 = $0 else { return false }; return true }.count, 0)
        XCTAssertEqual(FruityRazer.groupedConnectedDevices.filter { guard case VersionedRazerDevice.v3 = $0 else { return false }; return true }.count, 2)
        XCTAssertEqual(FruityRazer.groupedConnectedDevices.filter { guard case VersionedRazerDevice.both = $0 else { return false }; return true }.count, 1)
    }
    
    func testGroupedDeviceAssignment() {
        FruityRazer.groupedDevices.filter { guard case VersionedRazerDevice.both = $0 else { return false }; return true } .forEach {
            guard case let VersionedRazerDevice.both(v2: v2, v3: v3) = $0 else {
                XCTFail("Dual driver device somehow stopped being a dual driver device!")
                
                return
            }
            
            XCTAssertEqual(v2.shortName, $0.shortName + "_hw")
            XCTAssertEqual(v3.shortName, $0.shortName + "_sw")
        }
    }
    
    func testHuntsmanTEAsGroupedDevice() {
        XCTAssertEqual(FruityRazer.groupedDevices.filter { $0.fullName == "Razer Huntsman TE" }.count, 1)
    }
    
    func testSynapseDriverAssignment() {
        let devices = FruityRazer.devices
        
        let mamba = devices.filter { $0.shortName == "mamba_wired" }[0]
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
