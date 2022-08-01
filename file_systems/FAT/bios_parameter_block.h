#include "../types.h"

#ifndef BIOS_PARAMETER_BLOCK_H
#define BIOS_PARAMETER_BLOCK_H
typedef struct {
    uint8_t* boot_code_jmp[3];
    uint8_t* oem_identifier[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t number_of_fats;
    uint16_t root_entries;
    uint16_t total_sectors;
    uint8_t media_descriptor;
    uint16_t sectors_per_fat;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sectors;
    uint32_t large_sector_count;
} bios_parameter_block;

#endif BIOS_PARAMETER_BLOCK_H