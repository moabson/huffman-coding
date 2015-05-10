/*
 * debug.h
 *
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#define LOG_WARN(msg) printf("[WARN] " msg "\n");
#define LOG_ERR(msg) printf("[ERROR] " msg "\n"); exit(EXIT_FAILURE);
#define LOG_INFO(msg) printf("[INFO] " msg "\n");

#endif /* DEBUG_H_ */
