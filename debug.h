/*
 * debug.h
 *
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#define LOG_WARN(msg) fprintf(stdout, "[WARN] " msg "\n");
#define LOG_ERR(msg) fprintf(stderr, "[ERROR] " msg "\n"); exit(-1);
#define LOG_ERR_PTR(msg) fprintf(stderr, "[ERROR] " msg ": "); perror(""); exit(-1);
#define LOG_INFO(msg, args...) fprintf(stdout, "[INFO] " msg args); fprintf(stdout, "\n");

#endif /* DEBUG_H_ */
