// swift-tools-version:5.7
// GRDB 6.24.0 + SQLCipher (TerraCrypt fork)
// Based on commit 344878c from groue/GRDB.swift

import Foundation
import PackageDescription

var swiftSettings: [SwiftSetting] = [
    .define("SQLITE_ENABLE_FTS5"),
    .define("SQLITE_HAS_CODEC"),
    .define("GRDBCIPHER"),
]
var cSettings: [CSetting] = [
    .define("SQLITE_HAS_CODEC"),
    .define("GRDBCIPHER"),
]

let package = Package(
    name: "GRDB",
    defaultLocalization: "en",
    platforms: [
        .iOS(.v13),
        .macOS(.v10_15),
        .tvOS(.v13),
        .watchOS(.v7),
    ],
    products: [
        .library(name: "GRDB", targets: ["GRDB"]),
        .library(name: "GRDB-dynamic", type: .dynamic, targets: ["GRDB"]),
    ],
    dependencies: [
        .package(url: "https://github.com/sqlcipher/SQLCipher.swift.git", from: "4.10.0"),
    ],
    targets: [
        .target(
            name: "CSQLite",
            dependencies: [
                .product(name: "SQLCipher", package: "SQLCipher.swift"),
            ],
            path: "Sources/CSQLite",
            publicHeadersPath: ".",
            cSettings: [
                .define("SQLITE_HAS_CODEC"),
            ]),
        .target(
            name: "GRDB",
            dependencies: ["CSQLite"],
            path: "GRDB",
            resources: [.copy("PrivacyInfo.xcprivacy")],
            cSettings: cSettings,
            swiftSettings: swiftSettings),
        .testTarget(
            name: "GRDBTests",
            dependencies: ["GRDB"],
            path: "Tests",
            exclude: [
                "CocoaPods",
                "Crash",
                "CustomSQLite",
                "GRDBTests/getThreadsCount.c",
                "Info.plist",
                "Performance",
                "SPM",
                "generatePerformanceReport.rb",
                "parsePerformanceTests.rb",
            ],
            resources: [
                .copy("GRDBTests/Betty.jpeg"),
                .copy("GRDBTests/InflectionsTests.json"),
                .copy("GRDBTests/Issue1383.sqlite"),
            ],
            cSettings: cSettings,
            swiftSettings: swiftSettings)
    ],
    swiftLanguageVersions: [.v5]
)
