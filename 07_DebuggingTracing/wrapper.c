#define _GNU_SOURCE

#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>

typedef int (*orig_unlinkat_t)(int, const char *, int);

int unlinkat(int dirfd, const char *pathname, int flags) {
    if (strstr(pathname, "FIX") != NULL) {
        errno = EPERM;
        return -1;
    }

    return ((orig_unlinkat_t) dlsym(RTLD_NEXT, "unlinkat"))(dirfd, pathname, flags);
}
