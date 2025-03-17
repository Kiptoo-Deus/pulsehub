use cmake::Config;

fn main() {
    let dst = Config::new("cpp")
        .build_target("system_monitor")
        .build();

    // Link to system_monitor.lib
    println!("cargo:rustc-link-search=native={}/build/lib/Debug", dst.display());
    println!("cargo:rustc-link-lib=dylib=system_monitor");

    // Link to SDL2.lib from vcpkg
    println!("cargo:rustc-link-search=native=C:/vcpkg/installed/x64-windows/lib");
    println!("cargo:rustc-link-lib=SDL2");
}