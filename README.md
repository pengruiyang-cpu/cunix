Cunix kernel
============

# Versions
`0.362s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;`Boot` read `loader` from `boot-device`, then it jumps to it.  
&nbsp;&nbsp;&nbsp;&nbsp;Loader doesn't load anything, it just enable long-mode and paging.  
&nbsp;&nbsp;&nbsp;&nbsp;Loader defines temporary page table at `0x70000` (0x0000:0x7000),  
&nbsp;&nbsp;&nbsp;&nbsp;it uses `2MB` page to make 0-12 MB memory to `0x0000 - 0xc0000`.  


`0.385s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;rebuild `boot` and `loader`.  


`0.391s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;loader` forgot open A20 line, so `0.385` and `0.362` just can
&nbsp;&nbsp;&nbsp;&nbsp;use 1MB memory like real-mode.  


`0.432s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;make directory `include/`, and add segment.inc, but it doesn't work. :-)  


`0.451s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;`boot` can load 8 sectors (4KB) of loader (not 1 sector).  


`0.466s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;rebuild `boot`


`0.487s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;`loader` let FS can access 4GB memory in real-mode. because 
&nbsp;&nbsp;&nbsp;&nbsp;`loader` loaded GDT and load a data-segment to fs, then disable
&nbsp;&nbsp;&nbsp;&nbsp;protect-mode. 


`0.484s-boot`:
&nbsp;&nbsp;&nbsp;&nbsp;let `readdisk.inc` smaller, but we just can use CHS or LBA, not both. 


`0.509s-kernel`: 
&nbsp;&nbsp;&nbsp;&nbsp;load kernel to 0x8200-0x9200 for 4KB, kernel.asm display 'K' to screen. 

`0.556s-int`: 
&nbsp;&nbsp;&nbsp;&nbsp;init IDT at 0x0000-0x1000, and set all handler at ignore_int, but it do nothing.

`0.619s-boot`: 
&nbsp;&nbsp;&nbsp;&nbsp;load 180KB of disk, not 4KB. 
