bits 64

_start:
	mov byte [0xb8000], 'K'

	hlt
	jmp $
