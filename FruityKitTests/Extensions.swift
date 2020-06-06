//
//  Extensions.swift
//  FruityKitTests
//
//  Created by Eduardo Almeida on 20/04/2020.
//  Copyright © 2020 Eduardo Almeida. All rights reserved.
//

import Foundation
import FruityKit

//  MARK: Extensions -

protocol Repeatable {
    func repeated<T>(_ times: Int) -> [T]
}

extension Repeatable {
    func repeated<T>(_ times: Int) -> [T] {
        (0...times).map { _ in self as! T }
    }
}

//  MARK: - Protocol Conformances -

extension Array: Repeatable {}
extension Color: Repeatable {}
