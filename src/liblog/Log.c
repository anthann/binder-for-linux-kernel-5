#include <log/log.h>

#include <stdarg.h>
#include <string.h>


int __android_log_print(android_LogPriority priority, const char *tag, const char *fmt, ...)
{
    UNUSED(priority);

    char buf[DEFAULT_LOG_BUFFER_LEN];
    sprintf(buf, "[%s]: ", tag);
    int tag_len = strlen(buf);

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf + tag_len, DEFAULT_LOG_BUFFER_LEN - tag_len, fmt, ap);

    return fprintf(stderr, "%s", buf);
}