Cunix kernel
============

# Version
`0.362s-boot`:  
	`Boot` read `loader` from `boot-device`, then it jumps to it.  
	Loader doesn't load anything, it just enable long-mode and paging.  
	Loader defines temporary page table at `0x70000` (0x0000:0x7000),  
	it uses `2MB` page to make 0-12 MB memory to `0x0000 - 0xc0000`.  

`0.385s-boot`:  
	rebuild `boot` and `loader`.  

`0.391s-boot`:  
	`loader` forgot open A20 line, so `0.385` and `0.362` just can  
	use 1MB memory like real-mode.  

`0.432s-boot`:  
	make directory `include/`, and add segment.inc, but it doesn't work. :-)  

`0.451s-boot`:  
	`boot` can load 8 sectors (4KB) of loader (not 1 sector).  

