/*
Copyright 2022 Jacob R. Haygood

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "create_fat_boot_disk.h"
#include "utils.h"
#include <stdio.h>

extended_boot_record_fat_32 create_extended_boot_record(char* boot_code_file_path, uint32_t sectors_per_fat,
    uint8_t root_cluster_number, uint16_t fsinfo_sector_number, uint16_t backup_boot_sector_number, 
    uint8_t drive_number, uint8_t signature, uint32_t volume_id, char* volume_label, char* identifier, 
    int* error_flag) {

    extended_boot_record_fat_32 *ebr = (bios_parameter_block*) malloc(sizeof(bios_parameter_block));
    FILE* boot_code = fopen(boot_code_file_path, "r");
    int boot_code_size = get_file_size(boot_code);

    if (boot_code_size > 420) {
        printf("Error: bootocde is %d bytes long. Maximum for FAT32 is 420 bytes", boot_code_size);
       *error_flag = 1;
    }

    uint8_t* boot_code_buffer = (uint8_t*) calloc(420, sizeof(uint8_t));
    uint8_t* identifier_buffer = (uint8_t*) calloc(8, sizeof(uint8_t));
    uint8_t* volume_label_buffer = (uint8_t*) calloc(11, sizeof(uint8_t));

    for (int i = 0; i < 11; i ++) {
        if (volume_label_buffer[i] == '\0') {
            break;
        }
        volume_label_buffer[i] = volume_label[i];
    }

    for (int i = 0; i < 8; i ++) {
        if (identifier_buffer[i] == '\0') {
            break;
        }
        identifier_buffer[i] = identifier[i];
    }

    fread(boot_code_buffer, boot_code_size, 1, boot_code);

    ebr->sectors_per_fat = sectors_per_fat;
    ebr->flags = 0;
    ebr->root_cluster_number = root_cluster_number;
    ebr->fsinfo_sector_number = fsinfo_sector_number;
    memset(ebr->reserved, 0, sizeof(ebr->reserved));
    ebr->drive_number = drive_number;
    ebr->reserved2 = 0;
    ebr->signature = signature;
    ebr->volume_id = volume_id;
    strcpy(ebr->volume_label, volume_label_buffer);
    strcpy(ebr->identifier, identifier_buffer);
    strcpy(ebr->boot_code, boot_code_buffer);
    ebr->boot_signature[0] = 0x55; //Magic number low
    ebr->boot_signature[1] = 0xAA; //Magic number high
}