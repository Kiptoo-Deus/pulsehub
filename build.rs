use cmake::Config;

fn main() {
    let dst = Config::new("cpp")
        .build_target("system_monitor")
        .build();

    // Point directly to cpp/build/lib/Debug instead of the 'out' folder
    println!("cargo:rustc-link-search=native={}/build/lib/Debug", dst.display());
    println!("cargo:rustc-link-lib=dylib=system_monitor");
}