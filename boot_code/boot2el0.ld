ENTRY(_start)
SECTIONS
{
 . = 0x80000000;
 
 .text : { *(.text) }

end = .;
}
