;Copyright 2022 Jacob R. Haygood

;Licensed under the Apache License, Version 2.0 (the "License");
;you may not use this file except in compliance with the License.
;You may obtain a copy of the License at

;    http://www.apache.org/licenses/LICENSE-2.0

;Unless required by applicable law or agreed to in writing, software
;distributed under the License is distributed on an "AS IS" BASIS,
;WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;See the License for the specific language governing permissions and
;limitations under the License.

;subroutine to print a string
;Accepts:
; *char char_ptr: pointer to char to print

;This is the master boot record for the operating system
;the magic number: 0x55AA is used to tell the bios this is a bootable medium
;bit 0xAA is at location 0x01FE and bit 0x55 is at location 0x01FF
;when the bios loads this code we are most likely in 16bit real mode
;the goal of this snippit is to setup the boot record for the disk and
;load the kernal into memory

[ORG 0x7C00] ;bios loads this code at 0x7C00
[BITS 16] ;start in 16 bit real mode

jmp boot
.oem db 'HOS1.0  '
.bytes_per_sector dw 512
.sectors_per_cluster db 4
.reserved_sectors db 1
.number_of_fats db 2
.root_dir_entries db 2
.total_sectors dw 0 ;more than 65535 sectors
.padding db 0
.sectors_per_fat db 4
.sectors_per_track db 63 

.boot

times 510 - ($-$$) dw 0
.magic dw 0x55AA ;Magic number to signal to bios this is bootable
