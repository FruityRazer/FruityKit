//
//  ConversionTests.swift
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
    
    func testSynapse3_doesNotCrashWhenPassedInvalidColors() throws {
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
        
        XCTAssertTrue(specializedDriver.write(mode: .raw(colors: try! Color(hex: "#zzzzzz").repeated(14))))
    }
}
