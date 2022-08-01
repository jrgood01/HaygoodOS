#include "../file_systems/FAT/FAT32/boot_sector.h"
#include "../file_systems/FAT/FAT32/extended_boot_record_fat_32.h"
#include "../file_systems/FAT/FAT32/fs_info.h"
#include "../file_systems/FAT/FAT12_16/boot_sector.h"
#include "../file_systems/FAT/FAT12_16/extended_boot_record_fat_12_16.h"
#include "../file_systems/FAT/bios_parameter_block.h"
#include "../file_systems/fs_type.h"

extended_boot_record_fat_32 create_extended_boot_record(char* boot_code_file_path, uint32_t sectors_per_fat,
    uint8_t root_cluster_number, uint16_t fsinfo_sector_number, uint16_t backup_boot_sector_number, 
    uint8_t drive_number, uint8_t signature, uint32_t volume_id, char* volume_label, char* identifier, 
    int* error_flag);