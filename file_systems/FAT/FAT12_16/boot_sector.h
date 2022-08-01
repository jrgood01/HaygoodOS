#include "extended_boot_record_fat_12_16.h"
#include "../bios_parameter_block.h"
typedef struct {
    bios_parameter_block bpb;
    extended_boot_record_fat_12_16 ebr;
}__attribute__((packed)) fat16_boot_sector;
