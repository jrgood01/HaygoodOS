#include "../../types.h"

#ifndef EXTENDED_BOOT_RECORD_FAT_32_H
#define EXTENDED_BOOT_RECORD_FAT_32_H
typedef struct {
    uint32_t sectors_per_fat;
    uint16_t flags;
    uint8_t version[2];
    uint32_t root_cluster_number;
    uint16_t fsinfo_sector_number;
    uint16_t backup_boot_sector_number;
    uint8_t reserved[12];
    uint8_t drive_number;
    uint8_t reserved2;
    uint8_t signature;
    uint32_t volume_id;
    uint8_t volume_label[11];
    uint8_t identifier[8];
    uint8_t boot_code[420];
    uint8_t boot_signature[2];
}__attribute__((packed)) extended_boot_record_fat_32;

#endif EXTENDED_BOOT_RECORD_FAT_32_H