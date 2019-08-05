/* Compatibility header for libtool on Windows. */

#ifndef LTDL_H
#define LTDL_H 1

#include <Windows.h>

typedef HMODULE lt_dlhandle;
typedef void* lt_ptr;

int lt_dlinit()
{
    return 0;
}

const char* lt_dlerror()
{
    DWORD dLastError = GetLastError();
	LPTSTR strErrorMessage = NULL;

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL,
        dLastError,
        0,
        (LPTSTR)&strErrorMessage,
        0,
        NULL
    );
    return strErrorMessage;
}

void lt_dlerrorfree(const char * msg)
{
	if (msg) LocalFree((HLOCAL)msg);
}

lt_dlhandle lt_dlopen(char* p)
{
    return LoadLibrary(p);
}

void* lt_dlsym(lt_dlhandle hndl, const char* s)
{
    return (void*)GetProcAddress(hndl, (LPCSTR)s);
}

#endif /* !LTDL_H */
