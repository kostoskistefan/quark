#include "x_utilities.h"
#include <cstdio>
#include <algorithm>
#include <xcb/xproto.h>

XUtilities::XUtilities()
{
    connect();
    initialize_screen();
    initialize_ewmh();
}

XUtilities::~XUtilities()
{
    xcb_ewmh_connection_wipe(config.ewmhConnection);
    xcb_flush(config.connection);
    xcb_disconnect(config.connection);
}

void XUtilities::connect()
{
    this->config.connection = xcb_connect(NULL, NULL);

    if (xcb_connection_has_error(this->config.connection))
    {
        fprintf(stderr, "Failed to open display");
        exit(EXIT_FAILURE);
    }
}

void XUtilities::initialize_screen()
{
    this->config.screen =
        xcb_setup_roots_iterator(
                xcb_get_setup(this->config.connection)).data;

    if (!this->config.screen)
    {
        fprintf(stderr, "Failed to acquire screen");
        exit(EXIT_FAILURE);
    }
}

void XUtilities::initialize_ewmh()
{
    this->config.ewmhConnection = new xcb_ewmh_connection_t;

    xcb_intern_atom_cookie_t *ewmh_atoms =
        xcb_ewmh_init_atoms(
                this->config.connection, 
                this->config.ewmhConnection);

    int ewmhConnection_successful = 
        xcb_ewmh_init_atoms_replies(
                this->config.ewmhConnection,
                ewmh_atoms,
                NULL);

    if (!ewmhConnection_successful)
    {
        fprintf(stderr, "Failed to initialize EWMH atoms");
        exit(EXIT_FAILURE);
    }
}

xcb_atom_t XUtilities::get_atom(std::string name)
{
    xcb_intern_atom_cookie_t cookie = 
        xcb_intern_atom(
                this->config.connection,
                true,
                name.length(),
                name.c_str());

    xcb_intern_atom_reply_t *reply =
        xcb_intern_atom_reply(
                this->config.connection,
                cookie,
                NULL);

    if (reply)
    {
        xcb_atom_t atom = reply->atom;

        free(reply);

        return atom;
    }

    return XCB_ATOM_NONE;
}

void *XUtilities::get_window_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type)
{
    if (property == XCB_ATOM_NONE)
        return nullptr;

    xcb_get_property_cookie_t cookie =
        xcb_get_property(
                this->config.connection,
                0,
                window,
                property,
                type,
                0, 1024);

    xcb_get_property_reply_t *reply =
        xcb_get_property_reply(
                this->config.connection,
                cookie,
                NULL);

    if (reply)
    {
        int length = xcb_get_property_value_length(reply);

        if (length == 0)
        {
            free(reply);

            return nullptr;
        }

        void *value = xcb_get_property_value(reply);

        free(reply);

        return value;
    }

    return nullptr;
}

std::vector<xcb_window_t> XUtilities::get_window_ids()
{
    xcb_get_property_cookie_t clientListCookie = 
        xcb_ewmh_get_client_list(
                this->config.ewmhConnection, 
                0);

    xcb_ewmh_get_windows_reply_t reply;

    int status = xcb_ewmh_get_client_list_reply(
            this->config.ewmhConnection,
            clientListCookie,
            &reply,
            nullptr);

    if (status)
    {
        std::vector<xcb_window_t> windowIDs(
                &reply.windows[0],
                &reply.windows[reply.windows_len]);

        xcb_atom_t wmDesktop = get_atom("_NET_WM_DESKTOP");
        xcb_atom_t wmWindowType = get_atom("_NET_WM_WINDOW_TYPE");
        xcb_atom_t wmWindowTypeDock = get_atom("_NET_WM_WINDOW_TYPE_DOCK");

        for (auto iterator = windowIDs.begin(); iterator != windowIDs.end();)
        {
            uint32_t *wmDesktopData = 
                (uint32_t *) get_window_property(
                        *iterator,
                        wmDesktop,
                        XCB_ATOM_CARDINAL);

            xcb_atom_t *wmWindowTypeData = 
                (xcb_atom_t *) get_window_property(
                        *iterator, 
                        wmWindowType, 
                        XCB_ATOM_ATOM);

            bool windowIsValid = 
                *wmDesktopData == 0 &&
                *wmWindowTypeData != wmWindowTypeDock;

            if (windowIsValid)
                iterator++;

            else    
                iterator = windowIDs.erase(iterator);
        }

        return windowIDs;
    }

    return {};
}

std::vector<application_t> XUtilities::get_running_applications()
{
    std::vector<xcb_window_t> windowIDs = get_window_ids();

    std::vector<application_t> applications;

    for (auto id : windowIDs)
    {
        application_t application = {
            .id = id,
            .icon = "",
            .command = ""
        };

        applications.push_back(application);
    }

    /* for (auto id : applications) */
    /* printf("0x%.8x\n", id.id); */

    return applications;
}
