//
//  RazerHuntsmanHandle+Extensions.swift
//  FruityKitTests
//
//  Created by Eduardo Almeida on 10/12/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

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
