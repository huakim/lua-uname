//#include <iostream>

#ifdef _WIN32

#include <WinSock2.h>
#include <Windows.h>

#define UTSNAME_MAXLENGTH 256

struct utsname {
    char sysname [UTSNAME_MAXLENGTH]; // name of this implementation of the operating system
    char nodename[UTSNAME_MAXLENGTH]; // name of this node within an implementation - dependent communications network
    char release [UTSNAME_MAXLENGTH]; // current release level of this implementation
    char version [UTSNAME_MAXLENGTH]; // current version level of this release
    char machine [UTSNAME_MAXLENGTH]; // name of the hardware type on which the system is running
};

int uname(struct utsname *name) {
    OSVERSIONINFO versionInfo;
    SYSTEM_INFO sysInfo;

    // Get Windows version info
    ZeroMemory(&versionInfo, sizeof(OSVERSIONINFO));
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&versionInfo);

    // Get hardware info
    ZeroMemory(&sysInfo, sizeof(SYSTEM_INFO));
    GetSystemInfo(&sysInfo);

    // Set implementation name
    strcpy(name->sysname, "Windows");
    itoa(versionInfo.dwBuildNumber, name->release, 10);
    sprintf(name->version, "%i.%i", versionInfo.dwMajorVersion, versionInfo.dwMinorVersion);

    // Set hostname
    if (gethostname(name->nodename, UTSNAME_MAXLENGTH) != 0) {
        return WSAGetLastError();
    }

    // Set processor architecture
    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            strcpy(name->machine, "x86_64");
            break;
        case PROCESSOR_ARCHITECTURE_IA64:
            strcpy(name->machine, "ia64");
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            strcpy(name->machine, "x86");
            break;
        case PROCESSOR_ARCHITECTURE_UNKNOWN:
        default:
            strcpy(name->machine, "unknown");
    }

    return 0;
}

#else
#include <sys/utsname.h>
#endif

#include <lua.h>
#include <lauxlib.h>
#include "compat-5.3.h"

static struct utsname * get_uname(){
    struct utsname * u = (struct utsname*) malloc(sizeof(struct utsname));
    uname(u);
    return u;
}

int lua_uname(lua_State *L){
    struct utsname * u = get_uname();

    lua_createtable(L, 0, 5);
    int c = lua_gettop(L);
    lua_pushstring(L, u->sysname);
    lua_setfield(L, c, "sysname");
    lua_pushstring(L, u->nodename);
    lua_setfield(L, c, "nodename");
    lua_pushstring(L, u->release);
    lua_setfield(L, c, "release");
    lua_pushstring(L, u->version);
    lua_setfield(L, c, "version");
    lua_pushstring(L, u->machine);
    lua_setfield(L, c, "machine");
    return 1;
}

static const struct luaL_Reg functions [] = {
    {"uname", lua_uname},
    {NULL, NULL}
};

int luaopen_uname(lua_State *L) {
    luaL_newlib(L, functions);
    return 1;
}

/*
int main(int argc, char ** argv){
    struct utsname *u = new struct utsname[1];
    uname(u);
    cout<<u->sysname<<endl;
    cout<<u->nodename<<endl;
    cout<<u->release<<endl;
    cout<<u->version<<endl;
    cout<<u->machine<<endl;
}
*/
