extern "C" {
    fn get_cpu_usage() -> f64;
}

fn main() {
    let cpu = unsafe { get_cpu_usage() };
    println!("CPU Usage from C++: {}%", cpu);
}