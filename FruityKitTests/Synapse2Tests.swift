//
//  Synapse2Tests.swift
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

class Synapse2Tests: XCTestCase {
    
    var huntsmanEliteHWDriver: Synapse2Handle {
        let devices = FruityRazer.devices
        
        let huntsmanEliteHardware = devices.filter { $0.shortName == "huntsman_elite_hw" }[0]
        
        guard case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver else {
            XCTFail("Huntsman Elite not recognized as Synapse 2!")
            
            fatalError()
        }
        
        return driver
    }
    
    var basiliskDriver: Synapse2Handle {
        let devices = FruityRazer.devices
        
        let huntsmanEliteHardware = devices.filter { $0.shortName == "basilisk" }[0]
        
        guard case let Driver.v2(driver: driver) = huntsmanEliteHardware.driver else {
            XCTFail("Basilisk not recognized as Synapse 2!")
            
            fatalError()
        }
        
        return driver
    }
    
    func testHuntsmanElite_wave_unacceptablySlowSpeed() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .wave(speed: .unacceptablySlow, direction: .right)))
    }
    
    func testHuntsmanElite_wave_defaultSpeed() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .wave(speed: .default, direction: .right)))
    }
    
    func testHuntsmanElite_wave_unacceptablyFastSpeed() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .wave(speed: .unacceptablyFast, direction: .right)))
    }
    
    func testHuntsmanElite_spectrum() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .spectrum))
    }
    
    func testHuntsmanElite_reactive() throws {
        try XCTSkipIf(!huntsmanEliteHWDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .reactive(speed: .default, color: .white)))
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
        
        XCTAssertTrue(huntsmanEliteHWDriver.write(mode: .starlight(speed: .unacceptablyFast,
                                                                   color1: .white,
                                                                   color2: .red)))
    }
    
    func testBasilisk_wave() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertFalse(basiliskDriver.write(mode: .wave(speed: .default, direction: .right)))
    }
    
    func testBasilisk_spectrum() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(basiliskDriver.write(mode: .spectrum))
    }
    
    func testBasilisk_reactive() throws {
        try XCTSkipIf(!basiliskDriver.connected, SkippedTestMessage.hardwareConfigurationUnsupported)
        
        XCTAssertTrue(basiliskDriver.write(mode: .reactive(speed: .default, color: .white)))
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
        
        XCTAssertFalse(basiliskDriver.write(mode: .starlight(speed: .default,
                                                             color1: .white,
                                                             color2: .red)))
    }
}
