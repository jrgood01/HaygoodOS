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

/*
    This is a tool for creating bootable media for custom operating systems
*/

#include "create_fat_boot_disk.h"
#include "utils.h"
#include <stdio.h>
#include <glib.h>

int error_flag = 0;
void throw_syntax_error(char* buffer, int start, int end) {
    error_flag = 1;
    char* error_msg;
    if (end - start < 30) {
        error_msg = (char*)malloc(sizeof(char) * (end - start + 1));
        strcpy(error_msg, buffer);
        printf("Syntax error: %s", error_msg);
    } else {
        error_msg = (char*)malloc(sizeof(char) * 30);
        strncpy(error_msg, buffer, 30);
        printf("Syntax error: %s...", error_msg);
    }
}

GHashTable* parse_file(const char* filename) {
    GHashTable* table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    FILE* f = fopen(filename, "r");
    int size = get_file_size(f);
    if(!f) {
        fprintf(stderr, "Could not find file %s\n", filename);
        return NULL;
    }
    char* buffer = (char*) malloc(size + 1);
    fread(buffer, size, 1, f);
    int start_ptr = 0;
    int index = 0;
    for (int i = 0; i < size + 1; i ++) {
        char c = buffer[i];
        if (c == ';') {
            char* parse_buffer = (char*) malloc(sizeof(char) * (index - start_ptr + 1));
            char* descriptor;
            char* value;
            strncpy(parse_buffer + start_ptr, buffer, index);
            for (int i = start_ptr; i < index; i ++) {
                if (buffer[i] == ':') {
                    descriptor = (char*)malloc(sizeof(char) * (i - start_ptr + 1));
                    value = (char*)malloc(sizeof(char) * (index - i + 1));
                    strncpy(descriptor + start_ptr, buffer, i);
                    strncpy(value  + (i - 1), buffer, index);
                    g_hash_table_insert(table, parse_buffer, parse_buffer);
                    continue;
                }
                if (i == index - 1) {
                    throw_syntax_error(buffer, start_ptr, index);
                }
            }
            free(parse_buffer);
        }
        index += 1;
        start_ptr = index;
    }

    free(buffer);
    fclose(f);
    return table;
}



int main(int argc, char **argv) {
    extended_boot_record_fat_32 test_br = create_extended_boot_record("build_utils/testcode", 22, 10, 34, 2, 0, 0xF8, 2, "TEST VOLUME", 'TEST ID', 0);
    char* format;
    char* output_name;
    char** input_files;

    int custom_boot_code = 1;

    if (argc != 2) {
        printf("Usage: %s descriptor_file\n", argv[0]);
        return 1;
    } 

    if (strcmp(argv[1], "-h") == 0) {
        printf("Usage: %s descriptor_file\n", argv[0]);
        printf("Configuration file specifiers:\n");
        printf("\tFORMAT: [FAT32, FAT16, FAT12]; (optional, default=FAT32)\n");
        printf("\tUSE_CUSTOM_BOOT_CODE: [true, false]; (optional, default=true)\n");
        printf("\tOUTPUT_NAME: ${output_file}; (required)\n");
        printf("\tINPUT_FILES: [${input_file_1, ${input_file_2}, ...] (required)\n");
        printf("\tBOOT_CODE: ${boot_code_file} (required if USE_CUSTOM_BOOT_CODE is true)\n");
        printf("\tKERNAL_FILE_NAME: ${kernal_file} (required if USE_CUSTOM_BOOT_CODE is flase)\n");
        return 1;
    }
    GHashTable* specs = parse_file(argv[1]);
    if (g_hash_table_contains(specs, "USE_CUSTOM_BOOTCODE")) {
        if(g_hash_table_lookup(specs, "USE_CUSTOM_BOOTCODE")!= "false" && g_hash_table_lookup(specs, "USE_CUSTOM_BOOTCODE") != "true") {
            printf("USE_CUSTOM_BOOTCODE must be either true or false\n");
            return 1;
        } 
        custom_boot_code = g_hash_table_lookup(specs, "USE_CUSTOM_BOOTCODE") == "0";
    }
    if (!g_hash_table_contains(specs, "FORMAT")) {
        printf("no format specified, defaulting to FAT32\n");
    } else {
        format = g_hash_table_lookup(specs, "FORMAT");
        if (!(strcmp(format, "FAT32") == 0 || strcmp(format, "FAT16") == 0) || strcmp(format, "FAT12") == 0) {
            printf("unsupported format %s\n", format);
            printf("Supported formats:\n FAT32\n  FAT16\n  FAT12\n");
            return 1;
        }
        printf("using format: %s\n", g_hash_table_lookup(specs, "FORMAT"));
    }
    if(!g_hash_table_contains(specs, "BOOTCODE")) {
        if (custom_boot_code) {
            printf("no boot code specified, but USE_CUSTOM_BOOT_CODE is true\n");
            return 1;
        }
    } else {
        if (!custom_boot_code) {
            printf("boot code specified, but USE_CUSTOM_BOOT_CODE is false\n");
            return 1;
        }
        printf("using bootcode: %s\n", g_hash_table_lookup(specs, "BOOTCODE"));
    }
    if(!g_hash_table_contains(specs, "KERNAL_FILE_NAME")) {
        if (!custom_boot_code) {
            printf("no kernal file specified, but USE_CUSTOM_BOOT_CODE is false\n");
            return 1;
        }
    } else {
        if (custom_boot_code) {
            printf("kernal file specified, but USE_CUSTOM_BOOT_CODE is true\n");
            return 1;
        }
        printf("using kernal file: %s\n", g_hash_table_lookup(specs, "KERNAL_FILE_NAME"));
    }
    if (error_flag) {
        return 1;
    }
    
}