# 🔧 C Functions Extension Library

A simple C library providing **extended utility functions** built on top of standard headers.  
Includes easy-to-use memory allocation, URL launching, web server setup, and file operations — all in a lightweight DLL for use in **MinGW-based Windows projects**.

---

## 📦 Included Functions

void error(char *msg);
void open_url(char *url);
void open_file(char *filename);
void *xmalloc(size_t size);
void urlreq();
void create_web_server(int port);
void send_host_message(SOCKET client_fd);

---

## 🧠 Function Implementations

// error()
void error(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

// xmalloc()
void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        error("Memory allocation failed");
    }
    return ptr;
}

// open_url()
void open_url(char *url) {
    size_t len = strlen(url);
    if (len > 0 && url[len - 1] == '\n') url[len - 1] = '\0';
    char full_url[300];
    if (strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) {
        snprintf(full_url, sizeof(full_url), "https://%s", url);
    } else {
        snprintf(full_url, sizeof(full_url), "%s", url);
    }
#if defined(_WIN32) || defined(_WIN64)
    char cmd[400];
    snprintf(cmd, sizeof(cmd), "start \"\" \"%s\"", full_url);
    system(cmd);
#elif defined(__APPLE__)
    char cmd[400];
    snprintf(cmd, sizeof(cmd), "open \"%s\"", full_url);
    system(cmd);
#else
    char cmd[400];
    snprintf(cmd, sizeof(cmd), "xdg-open \"%s\"", full_url);
    system(cmd);
#endif
}

// urlreq()
void urlreq(){
    char url[256];
    printf("Enter a URL to open: ");
    if (fgets(url, sizeof(url), stdin) == NULL) {
        error("Failed to read URL");
    }
    open_url(url);
}

// create_web_server()
void create_web_server(int port) {
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return;
    }
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return;
    }
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(server_fd);
        WSACleanup();
        return;
    }
    if (listen(server_fd, 5) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(server_fd);
        WSACleanup();
        return;
    }
    printf("Web server running on http://localhost:%d/\n", port);
    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
        if (client_fd == INVALID_SOCKET) {
            printf("Accept failed\n");
            continue;
        }
        char buffer[1024];
        send_host_message(client_fd);
        recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>Hello, World!</h1></body></html>\r\n";
        send(client_fd, response, (int)strlen(response), 0);
        closesocket(client_fd);
    }
    closesocket(server_fd);
    WSACleanup();
}

// send_host_message()
void send_host_message(SOCKET client_fd) {
    char msg[1024];
    printf("Enter message to send to client: ");
    if (fgets(msg, sizeof(msg), stdin) != NULL) {
        size_t len = strlen(msg);
        if (len > 0 && msg[len - 1] == '\n') msg[len - 1] = '\0';
        send(client_fd, msg, (int)strlen(msg), 0);
    }
}

// open_file()
void open_file(char *filename) {
    char rorw[2];
    printf("Read or write to file (r/w)?: %s\n", filename);
    scanf("%1s", rorw);
    getchar(); // consume leftover newline
    if (rorw[0] != 'r' && rorw[0] != 'w') {
        error("Invalid option, please enter 'r' or 'w'");
    }
    if (rorw[0] == 'r') {
        FILE *f1 = fopen(filename, "r");
        if (f1 == NULL) {
            error("Failed to open file for reading");
        }
        printf("Reading from file: %s\n", filename);
        char line[256];
        while (fgets(line, sizeof(line), f1) != NULL) {
            printf("%s", line);
            Sleep(10000);
        }
        fclose(f1);
    } else {
        FILE *f1 = fopen(filename, "w");
        if (f1 == NULL) {
            error("Failed to open file for writing");
        }
        printf("What do you want to write to the file?: %s\n", filename);
        char line[256];
        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (strcmp(line, "exit\n") == 0) break;
            fputs(line, f1);
        }
        fclose(f1);
    }
}

---

## 🛠️ Compilation

gcc main.c -L. -lfunct -o example.exe

- Make sure you have funct.dll and libfunct.a in the same directory.
- Place functions.h where your main.c can include it.

---

## 📁 Example Directory Layout

/project-folder
├── main.c
├── functions.h
├── funct.dll
├── libfunct.a
├── example.exe
