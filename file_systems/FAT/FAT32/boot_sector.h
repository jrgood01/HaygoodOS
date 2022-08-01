#include "extended_boot_record_fat_32.h"
#include "../bios_parameter_block.h"

typedef struct {
    bios_parameter_block bpb;
    extended_boot_record_fat_32 ebr;
}__attribute__((packed)) fat32_boot_sector;