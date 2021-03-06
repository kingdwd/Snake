#ifndef SNAKESETTINGS_H
#define SNAKESETTINGS_H
#include <config.h>
#include <quasarapp.h>

#define SERVER_ADDRESS "SERVER_ADDRESS"
#define SERVER_ADDRESS_PORT "SERVER_ADDRESS_PORT"
#define THEME "THEME_GUI"

#define SERVER_ADDRESS_DEFAULT "quasarapp.ddns.net"
//#define SERVER_ADDRESS_DEFAULT "127.0.0.1"
#define SERVER_ADDRESS_DEFAULT_PORT DEFAULT_SNAKE_PORT
#define THEME_DEFAULT 0

using Settings = QuasarAppUtils::Settings;

#endif // SNAKESETTINGS_H
