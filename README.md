Cunix kernel
============

# Versions
`0.362s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;`Boot` read `loader` from `boot-device`, then it jumps to it. <br/>
&nbsp;&nbsp;&nbsp;&nbsp;Loader doesn't load anything, it just enable long-mode and paging. <br/> 
&nbsp;&nbsp;&nbsp;&nbsp;Loader defines temporary page table at `0x70000` (0x0000:0x7000), <br/>
&nbsp;&nbsp;&nbsp;&nbsp;it uses `2MB` page to make 0-12 MB memory to `0x0000 - 0xc0000`. <br/>


`0.385s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;rebuild `boot` and `loader`. <br/>


`0.391s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;`loader` forgot open A20 line, so `0.385` and `0.362` just can <br/>
&nbsp;&nbsp;&nbsp;&nbsp;use 1MB memory like real-mode. <br/>


`0.432s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;make directory `include/`, and add segment.inc, but it doesn't work. :-)  <br/>


`0.451s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;`boot` can load 8 sectors (4KB) of loader (not 1 sector).  <br/>


`0.466s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;rebuild `boot` <br/>
    

`0.487s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;`loader` let FS can access 4GB memory in real-mode. because <br/>
&nbsp;&nbsp;&nbsp;&nbsp;`loader` loaded GDT and load a data-segment to fs, then disable <br/>
&nbsp;&nbsp;&nbsp;&nbsp;protect-mode. <br/>


`0.484s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;let `readdisk.inc` smaller, but we just can use CHS or LBA, not both. <br/>


`0.509s-kernel`:   
&nbsp;&nbsp;&nbsp;&nbsp;load kernel to 0x8200-0x9200 for 4KB, kernel.asm display 'K' to screen. <br/>

`0.556s-int`:  
&nbsp;&nbsp;&nbsp;&nbsp;init IDT at 0x0000-0x1000, and set all handler at `ignore_int`, but it do nothing. <br/>

`0.619s-boot`:  
&nbsp;&nbsp;&nbsp;&nbsp;load 180KB of disk, not 4KB <br/>

`0.566s-kernel`:  
&nbsp;&nbsp;&nbsp;&nbsp;write in C. <br/>

`0.790s-kernel`:  
&nbsp;&nbsp;&nbsp;&nbsp;make some structs <br/>

`1.384s-hal`:  
&nbsp;&nbsp;&nbsp;&nbsp;use text VGA mode, and make a file-operations of it. <br/>

`1.440s-lib`:  
&nbsp;&nbsp;&nbsp;&nbsp;make some macros about assembly. <br/>


`1.562s-init`:  
&nbsp;&nbsp;&nbsp;&nbsp;new head.s, re-init GDT and IDT. <br/>

`1.217s-init`:  
&nbsp;&nbsp;&nbsp;&nbsp;nt for file-operations, and remove all modules. <br/>

`1.302s-module`:  
&nbsp;&nbsp;&nbsp;&nbsp;there is a bug with loader: it cannot load kernel because 0 - 8 = -8 (not 0). <br/>
&nbsp;&nbsp;&nbsp;&nbsp;so we read it byte by byte. and we used assembly to wrote a tty driver. It just can putchar now. <br/>

`1.690s-module`:  
&nbsp;&nbsp;&nbsp;&nbsp;new function printf, put format string on screen. <br/>
&nbsp;&nbsp;&nbsp;&nbsp;and, new panic.S to `kernel panic`. <br/>


`1.727s-module`:  
&nbsp;&nbsp;&nbsp;&nbsp;add support '\n' for printf. <br/>

`1.760s-module`:  
&nbsp;&nbsp;&nbsp;&nbsp;accept fault or interrupt in head.s <br/>

`1.879s-memory`:  
&nbsp;&nbsp;&nbsp;&nbsp;init page table in head.S, it can map 0-64MB memory (32 pages). <br/>

`2.086s-module`:  
&nbsp;&nbsp;&nbsp;&nbsp;support 'roll' screen, and create some functions (string.h). <br/>
