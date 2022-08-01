ENTRY(main);
OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x7C00;
    .master_boot_record : {
        output/obj/boot.o(.master_boot_record)
    }
}