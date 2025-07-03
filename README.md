# 🔧 C Functions Extension Library

A simple C library providing **extended utility functions** built on top of standard headers.  
Includes easy-to-use memory allocation, URL launching, web server setup, and file operations — all in a lightweight DLL for use in **MinGW-based Windows projects**.

---

## 📦 Included Functions

**void error(char** ***msg);**

**void open_url(char** ***url);**

**void open_file(char** ***filename);**

**void** *****xmalloc(size_t size);****

**void urlreq();**

**void create_web_server(int port);**

**void send_host_message(SOCKET client_fd);**

---
# Function Implimentation is in the functions.c file.

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

