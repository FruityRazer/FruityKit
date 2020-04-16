//
//  Synapse3.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

enum Synapse3Mode {
    case raw
}

protocol Synapse3Device {
    func write(mode: Synapse3Mode)
}

extension Synapse3Device {
    
}
