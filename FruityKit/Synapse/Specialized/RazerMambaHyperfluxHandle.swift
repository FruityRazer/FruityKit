//
//  RazerMambaHyperfluxHandle.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 20/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

public final class RazerMambaHyperfluxHandle: RazerSoftwareSingleRowHandle {
    
    init(usbId: Int32) {
        super.init(usbId: usbId) { deviceInterface, colors in
            razer_hyperflux_set_colors(deviceInterface, colors);
        }
    }
}
