#include "../../types.h"
typedef struct{
    uint32_t signature;
    uint8_t reserved[480];
    uint32_t last_free_cluster;
    uint32_t cluster_search_start;
    uint8_t reserved2[12];
    uint32_t sector_signature;
}__attribute__((packed)) fs_info;