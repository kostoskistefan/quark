#ifndef X_UTILITIES_H
#define X_UTILITIES_H

#include <string>
#include <vector>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

typedef struct xcb_config_t
{
    xcb_screen_t* screen;
    xcb_connection_t* connection;
    xcb_ewmh_connection_t* ewmhConnection;
} xcb_config_t;

typedef struct application_t
{
    uint32_t id;
    std::string icon;
    std::string command;
} application_t;

class XUtilities
{
    public:
        XUtilities();
        ~XUtilities();

        std::vector<application_t> get_running_applications();

    private:
        xcb_config_t config;

        void connect();
        void initialize_screen();
        void initialize_ewmh();

        xcb_atom_t get_atom(std::string name);
        void *get_window_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type);

        std::vector<xcb_window_t> get_window_ids();
};

#endif // X_UTILITIES_H
