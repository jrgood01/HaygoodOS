#include "../../types.h"
#ifndef EXTENDED_BOOT_RECORD_FAT_12_16_H
#define EXTENDED_BOOT_RECORD_FAT_12_16_H
typedef struct {
    uint8_t drive_number;
    uint8_t reserved;
    uint8_t signature;
    uint32_t volume_id;
    uint8_t volume_label[11];
    uint8_t identifier[8];
    uint8_t boot_code[448];
    uint8_t boot_signature[2];
}__attribute__((packed)) extended_boot_record_fat_12_16;

#endif EXTENDED_BOOT_RECORD_FAT_12_16_H