Cunix kernel
============

# Build
Use `GNU-Make`, there is a file `cunix.img` in `boot`. It's a 1.44M floppy image. 
And then, use disk writer (like `dd`) write image to your start-up media, Cunix 
will start after it. 

# Version
2021 - 02 - 08: `0.362s-boot`: 
	`Boot` read `loader` from `boot-device`, then it jumps to it. 
	Loader doesn't load anything, it just enable long-mode and paging. 

	Loader defines temporary page table at `0x70000` (0x0000:0x7000), 
	it uses `2MB` page to make 0-12 MB memory to `0x0000 - 0xc0000`. 

2021 - 02 - 09: `0.385s-boot`: 
	rebuild `boot` and `loader`.

