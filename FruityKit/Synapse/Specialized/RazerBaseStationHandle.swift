//
//  RazerBaseStationHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 17/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public final class RazerBaseStationHandle: RazerSoftwareSingleRowHandle {
    
    init(usbId: Int32) {
        super.init(usbId: usbId) { deviceInterface, colors in
            razer_base_station_pre(deviceInterface)
            razer_base_station_set_colors(deviceInterface, colors)
        }
    }
}
