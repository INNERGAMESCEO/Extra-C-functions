#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifdef BUILDING_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

DLL_EXPORT void error(char *msg);
DLL_EXPORT void open_url(char *url);
DLL_EXPORT void open_file(char *filename);
DLL_EXPORT void *xmalloc(size_t size);
DLL_EXPORT void urlreq();
DLL_EXPORT void create_web_server(int port);
DLL_EXPORT void send_host_message(SOCKET client_fd);

#endif
