#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

#define WRITER_SUCCESS_CODE 0
#define WRITER_ERROR_CODE 1

int write_data_to_file(const char *filename, const char *data) {
    int ret_code = WRITER_SUCCESS_CODE;
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        syslog(LOG_ERR, "Error opening file for writing: %m");
        return ret_code = WRITER_ERROR_CODE;
    }
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        syslog(LOG_ERR, "Error writing to file: %m");
        ret_code = WRITER_ERROR_CODE;
    }
    if (close(fd) == -1) {
        syslog(LOG_ERR, "Error closing file: %m");
        ret_code = WRITER_ERROR_CODE;
    }
    return ret_code;
}

int main(int argc, char *argv[]) {
    int ret_code = WRITER_SUCCESS_CODE;
    openlog("writer", LOG_USER, LOG_USER);

    if (argc < 3) {
        syslog(LOG_ERR, "Usage: %s <file> <text>", argv[0]);
        closelog();
        return ret_code = WRITER_ERROR_CODE;
    }

    const char *filename = argv[1];
    const char *text = argv[2];

    syslog(LOG_INFO, "Writing %s to %s", text, filename);
    ret_code = write_data_to_file(filename, text);
    if (ret_code == WRITER_SUCCESS_CODE) {
        syslog(LOG_INFO, "Data written to %s successfully.", filename);
    }

    closelog();
    return ret_code;
}