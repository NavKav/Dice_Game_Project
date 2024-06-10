//
// Created by navid on 18/03/2024.
//

#ifndef ARPG_STORYBOARD_OSDEPENDENCIES_H
#define ARPG_STORYBOARD_OSDEPENDENCIES_H

#if defined(_WIN32)
#define OS_WINDOWS
#elif defined(__linux__)
#define OS_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_MACOS
#else
    #error "Unsupported operating system"
#endif


#ifdef OS_WINDOWS
#include <iostream>
#include <winsock2.h>

inline void socketInitialisation() {
    WSADATA wsa;
    std::cout << "Initialising Winsock..." << std::endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cout << "Failed. Error Code: " << WSAGetLastError() << std::endl;
        exit(0);
    }
    std::cout << "Initialised." << std::endl;
}

inline std::string getSocketError() {
    return std::to_string( WSAGetLastError());
}

inline void closeSocket(SOCKET socket) {
    closesocket(socket);
    WSACleanup();
}

#elif defined(OS_LINUX) || defined(OS_MACOS)
#include <iostream>
inline void socketInitialisation() {
    std::cout << "Socket Initialised." << std::endl;
}

inline std::string getSocketError() {
    return strerror(errno);
}

inline void closeSocket(SOCKET socket) {
}

#else

#endif

#endif //ARPG_STORYBOARD_OSDEPENDENCIES_H
