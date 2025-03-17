extern "C" {
    fn get_cpu_usage() -> f64;
}

use imgui::*;
use sdl2::event::Event;
use std::time::Duration;

fn main() -> Result<(), String> {
    let sdl_context = sdl2::init()?;
    let video = sdl_context.video()?;

    // Configure OpenGL before creating the window
    let gl_attr = video.gl_attr();
    gl_attr.set_context_profile(sdl2::video::GLProfile::Core);
    gl_attr.set_context_version(3, 3); // Use OpenGL 3.3 for compatibility-fixed the bug..woop woop!!

    let window = video
        .window("PulseHub", 800, 600)
        .opengl()
        .position_centered()
        .build()
        .map_err(|e| e.to_string())?;

    // Load the OpenGL context
    let _gl_context = window.gl_create_context()?;
    window.gl_make_current(&_gl_context)?;

    let mut imgui = Context::create();
    imgui.set_ini_filename(None);

    let mut imgui_sdl2 = imgui_sdl2::ImguiSdl2::new(&mut imgui, &window);
    let renderer = imgui_opengl_renderer::Renderer::new(&mut imgui, |s| {
        video.gl_get_proc_address(s) as _
    });

    let mut event_pump = sdl_context.event_pump()?;
    'running: loop {
        for event in event_pump.poll_iter() {
            imgui_sdl2.handle_event(&mut imgui, &event);
            if let Event::Quit { .. } = event {
                break 'running;
            }
        }

        imgui_sdl2.prepare_frame(imgui.io_mut(), &window, &event_pump.mouse_state());

        let ui = imgui.frame();
        ui.window("System Monitor")
            .size([300.0, 100.0], Condition::FirstUseEver)
            .build(|| {
                let cpu = unsafe { get_cpu_usage() };
                ui.text(format!("CPU Usage: {:.1}%", cpu));
            });

        imgui_sdl2.prepare_render(ui, &window);
        renderer.render(&mut imgui);

        window.gl_swap_window(); // Swap buffers to display the frame
        std::thread::sleep(Duration::from_millis(100));
    }
    Ok(())
}