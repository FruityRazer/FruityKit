//
//  PerformClosures.swift
//  FruityKit
//
//  Created by Eduardo Almeida on 16/06/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation

func runClosures(sequence: [() -> Bool], secondsBetweenClosures: TimeInterval = 0.15) -> Bool {
    return sequence.reduce(nil) {
        if $0 != nil {
            Thread.sleep(forTimeInterval: secondsBetweenClosures)
        }
        
        return $1() == true ? true : ($0 ?? false)
    } ?? false
}
