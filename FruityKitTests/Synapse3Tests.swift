//
//  Synapse3Tests.swift
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
@testable import FruityKit

extension RazerHuntsmanHandle {
    
    func fakeWave(color: Color) {
        let deviceInterface = dq_get_device(usbId)
        
        defer {
            dq_close_device(deviceInterface)
        }
        
        var rgb = color.razerRGB
        
        razer_huntsman_fake_wave_one_run(deviceInterface, &rgb)
    }
}

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
