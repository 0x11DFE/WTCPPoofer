#include "inc.cpp"

class Util {
    struct handle_data {
        unsigned long process_id;
        HWND window_handle;
    };

    static BOOL is_main_window(HWND handle) {
        return GetWindow(handle, GW_OWNER) == (HWND) nullptr && IsWindowVisible(handle);
    }

    static BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam) {
        handle_data &data = *(handle_data *) lParam;
        unsigned long process_id = 0;
        GetWindowThreadProcessId(handle, &process_id);
        if (data.process_id != process_id || !is_main_window(handle)) return TRUE;

        data.window_handle = handle;
        return FALSE;
    }

    /***
     * Enumerate windows from a process_id in order to get the process handle
     * @param process_id
     * @return HANDLE
     */
public:
    static HWND find_main_window(unsigned long process_id) {
        handle_data data{};
        data.process_id = process_id;
        data.window_handle = nullptr;
        EnumWindows(enum_windows_callback, (LPARAM) &data);
        return data.window_handle;
    }
};