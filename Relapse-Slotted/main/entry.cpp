#include <includes.h>

//#define menu_debug

inline DWORD dwMode;
auto main() -> int {

#ifdef menu_debug
    screen_width = CALL(&get_system_metrics_spoofed, (SM_CXSCREEN));
    screen_height = CALL(&get_system_metrics_spoofed, (SM_CYSCREEN));
    SonyDriverHelper::api::Init();

    std::thread([]() { menu.key_loop(); }).detach();

    render.start_directx();
    render.init();
#else

    CALL(&SetConsoleTitleA, ("Relapse-Private"));

    //if (utils.is_fortnite_open()) {
    //    console.clear();
    //    std::cout << std::endl;
    //    console.print_slow("Fortnite is open please close before opening loader...", 30, true, true, 2);
    //    Sleep(5000);
    //    __fastfail(0x4c);
    //}

    if (!Driver.find_driver()) {
        console.clear();
        std::cout << std::endl;
        console.print_slow(("Driver not loaded..."), 30, true, true, 2);

        console.clear();
        std::cout << std::endl;
        console.print_slow(("Driver loaded!"), 30, true, true, 3);

        CALL(&show_window_spoofed, GetConsoleWindow(), SW_SHOW);
        Sleep(1000);
    }

    screen_width = CALL(&get_system_metrics_spoofed, SM_CXSCREEN);
    screen_height = CALL(&get_system_metrics_spoofed, SM_CYSCREEN);

    SonyDriverHelper::api::Init();

    CALL(&MessageBoxA, nullptr, ("Click 'ok' in lobby..."), ("Waiting..."), MB_OK);
    Sleep(1000);

    if (!utils.is_fortnite_open()) {
        console.clear();
        std::cout << std::endl;
        console.print_slow(("Fortnite not open..."), 30, true, true, 2);
        Sleep(5000);
        __fastfail(0x4c);
    }

    process_id = Driver.find_process(("FortniteClient-Win64-Shipping.exe"));
    BaseAddr = Driver.find_image();
    auto cr3 = Driver.fetch_cr3();

    if (!process_id) {
        console.clear();
        std::cout << std::endl;
        console.print_slow(("Fortnite not found... (") + std::to_string(Driver.find_process(("FortniteClient-Win64-Shipping.exe"))) + ")", 30, true, true, 2);
        Sleep(5000);
        __fastfail(0x4c);
    }

    if (!strings.debug.enable) {
        CALL(&show_window_spoofed, CALL(&GetConsoleWindow), SW_HIDE);
    }

    std::thread([]() { visuals.actor_loop(); }).detach();
    std::thread([]() { get_camera_info(); }).detach();
    std::thread([]() { menu.key_loop(); }).detach();

    render.start_directx();
    render.init();

    return 0;
#endif
}