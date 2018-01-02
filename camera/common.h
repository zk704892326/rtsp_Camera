#ifndef COMMON_H
#define COMMON_H

#define DB_PATH   "camera.db"
#define IMG_DIR   "images"

typedef struct Settings_t {
    struct {
        QString url;
        bool enable;
    } videos[2];
    struct {
        QString ip;
        int port;
    } motors[2];
    bool cruise;
} Settings_t;

#endif // COMMON_H

