// John Reese
// Systems Programming I
// Q16 Assembler

.section .data

inst_halt:
	.ascii "halt"
inst_move:
	.ascii "move"
inst_add:
	.ascii "add "
inst_sub:
	.ascii "sub "
inst_comp:
	.ascii "comp"
inst_mult:
	.ascii "mult"
inst_divd:
	.ascii "divd"
inst_rem:
	.ascii "rem "
inst_breq:
	.ascii "breq"
inst_brne:
	.ascii "brne"
inst_brgt:
	.ascii "brgt"
inst_brge:
	.ascii "brge"
inst_brlt:
	.ascii "brlt"
inst_brle:
	.ascii "brle"
inst_br:
	.ascii "br  "
inst_incr:
	.ascii "incr"
inst_decr:
	.ascii "decr"
inst_rot:
	.ascii "rot "
inst_shl:
	.ascii "shl "
inst_shr:
	.ascii "shr "
inst_read:
	.ascii "read"
inst_prt:
	.ascii "prt "


data_blocks:
	.lcomm convertx_buffer, 8

	.lcomm file, 1			// file descriptor
	.lcomm line_buffer, 100		// file input buffer

	.lcomm symbol_count, 1		// Current symbol count
	.lcomm symbol_table, 400	// Maximum number of 50 symbols to track,
					// 4 bytes for label, 4 bytes for address, 8 * 50 = 400 bytes

comment:
	.ascii "+"
empty_label:
	.ascii "    "

error_open_file:
	.string "Error opening file.\n"

hello:
	.string "Hello.\n"
bye:
	.string "Bye!\n"

space:
	.string " "
newline:
	.string	"\n"

.section .text

//
// main assembler entry point
//
// @param int argc
// @param string[] argv
//
.global main
main:
	enter	$0, $0

main_open_file:
	movl	12(%ebp), %eax	// argv
	movl	4(%eax), %eax	// argv[1]

	pushl	$0		// O_RDONLY
	pushl	%eax		// argv[1]
	pushl	$0
	movl	$5, %eax	// SYS_open
	lcall	$0x27, $0
	addl	$12, %esp

	cmpl	$2, %eax	// error check
	jle	main_error

	movl	%eax, file	// new file descriptor

	call	pass1

	pushl	$0		// SEEK_SET
	pushl	$0		// offset
	pushl	file		// file descriptor
	pushl	$0
	movl	$19, %eax	// SYS_lseek
	lcall	$0x27, $0
	addl	$16, %esp

	call	pass2

	pushl	file		// file descriptor
	pushl	$0
	movl	$6, %eax	// SYS_close
	lcall	$0x27, $0
	addl	$8, %esp

	jmp	main_exit

main_error:
	pushl	$error_open_file
	call	printz
	addl	$4, %esp

main_exit:
	leave
	ret

//
// first pass processing
// compile the symbol table of all labels and their effective address
//
pass1:
	enter	$0, $0
	pushl	%ebx
	pushl	%edi
	pushl	%esi

	movl	$16, %esi		// instruction address
	movl	$symbol_table, %edi
	movl	$0, symbol_count
	movl	$0, %ebx		// word count

pass1_nextline:
	call	clear_line_buffer

	addl	%ebx, %esi
	movl	$0, %ebx

	pushl	$line_buffer		// get the next input line
	pushl	file
	call	getline
	addl	$8, %esp

	cmpl	$-1, %eax		// check for EOF
	je	pass1_print

	pushl	$1			// check for comment
	pushl	$line_buffer
	pushl	$comment
	call	ncompare
	addl	$12, %esp

	cmpl	$0, %eax		// ignore comments
	je	pass1_nextline

	pushl	$line_buffer		// get the instruction's word-count
	call	inst_word_count
	addl	$4, %esp
	movl	%eax, %ebx		// save the word count

pass1_check_label:
	push	$4			// check for labels
	pushl	$line_buffer
	pushl	$empty_label
	call	ncompare
	addl	$12, %esp

	cmpl	$0, %eax		// ignore empty labels
	je	pass1_nextline

	incl	symbol_count
	pushl	$4			// copy the label to the symbol table
	pushl	%edi
	pushl	$line_buffer
	call	strncpy
	addl	$12, %esp

	addl	$4, %edi

	movl	%esi, (%edi)		// copy the instruction address to the symbol table
	addl	$4, %edi
	
	jmp	pass1_nextline		// continue to the next line

pass1_print:				// Print the symbol table
	movl	symbol_count, %ecx
	movl	$symbol_table, %edi

pass1_print_loop:
	pushl	%ecx

	pushl	$4			// print the symbol
	pushl	%edi
	call	print
	addl	$8, %esp
	addl	$4, %edi

	pushl	$3			// spacing
	call	print_spaces
	addl	$4, %esp

	pushl	(%edi)			// print the address
	call	printin
	addl	$4, %esp
	addl	$4, %edi

	popl	%ecx
	loop	pass1_print_loop

pass1_print_done:			// print two blank lines
	pushl	$newline
	call	printzn
	add	$4, %esp

pass1_leave:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret

//
// Return the word-count for the given instruction line
//
// @param string instruction
// @return int instruction word count
//
inst_word_count:
	enter	$0, $0
	pushl	%ebx
	pushl	%edi
	pushl	%esi

	movl	8(%ebp), %ebx		// instruction string
	addl	$5, %ebx		// ignore the first five characters

inst_wc_branches:			// all branches require a second word
	pushl	$2
	pushl	%ebx
	pushl	$inst_br
	call	ncompare
	addl	$12, %esp

	cmpl	$0, %eax		// not a branch statement
	jne	inst_wc_operands

	movl	$2, %eax		// is a branch, return two
	jmp	inst_wc_leave

inst_wc_operands:			// check instruction operands for large immediates
	movl	$1, %edi
	movl	$0, %esi

inst_wc_next_operand:
	movb	(%ebx, %esi), %al	// the next character
	incl	%esi

	cmp	$0, %al			// look for end-of-line, done
	je	inst_wc_done

	cmp	$35, %al		// look for # symbol
	jne	inst_wc_next_operand

	movl	%ebx, %edx		// evaluate the number
	addl	%esi, %edx
	pushl	%edx
	call	evaluate
	addl	$4, %esp

	cmpl	$7, %eax		// is it bigger than 7?
	jbe	inst_wc_next_operand	

	incl	%edi			// increment byte-count
	jmp	inst_wc_next_operand

inst_wc_done:
	movl	%edi, %eax		// word-count to be returned

inst_wc_leave:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret

//
// second pass processing
//
pass2:
	enter	$0, $0
	pushl	%ebx
	pushl	%edi
	pushl	%esi

	movl	$16, %esi		// instruction address
	movl	$0, %ebx		// word count

pass2_nextline:
	call	clear_line_buffer

	addl	%ebx, %esi
	movl	$0, %ebx

	pushl	$line_buffer		// get the next input line
	pushl	file
	call	getline
	addl	$8, %esp

	cmpl	$-1, %eax		// check for EOF
	je	pass2_leave

	pushl	$1			// check for comment
	pushl	$line_buffer
	pushl	$comment
	call	ncompare
	addl	$12, %esp

	cmpl	$0, %eax
	jne	pass2_parse_line

	pushl	$25			// print the comment and then loop
	call	print_spaces
	pushl	$line_buffer
	call	printzn
	addl	$8, %esp

	jmp	pass2_nextline

pass2_parse_line:
	pushl	%esi			// call the instruction parser
	pushl	$line_buffer
	pushl	$0
	pushl	$0
	pushl	$0
	call	inst_word_parse
	movl	%esp, %ebx

	pushl	%esi			// print the instruction address and instruction word
	call	printi
	pushl	$3
	call	print_spaces
	pushl	(%ebx)
	call	printi
	addl	$12, %esp

	cmpl	$1, %eax		// check for single word instructions
	je	pass2_parse_one

	cmpl	$2, %eax		// check for two word instructions
	je	pass2_parse_two

pass2_parse_three:			// fall through to three word instructions
	pushl	$1			// print two extension words and the spacing
	call	print_spaces
	pushl	4(%ebx)
	call	printi
	pushl	$1
	call	print_spaces
	pushl	8(%ebx)
	call	printi
	pushl	$4
	call	print_spaces
	addl	$20, %esp

	movl	$3, %ebx
	jmp	pass2_parse_done

pass2_parse_two:
	pushl	$1			// print one extension word and the spacing
	call	print_spaces
	pushl	4(%ebx)
	call	printi
	pushl	$9
	call	print_spaces
	addl	$12, %esp

	movl	$2, %ebx		// set the word-count to two
	jmp	pass2_parse_done

pass2_parse_one:
	pushl	$14			// print no extensions words, just spacing
	call	print_spaces
	add	$4, %esp

	movl	$1, %ebx
	jmp	pass2_parse_done

pass2_parse_done:
	pushl	$line_buffer		// print the input line
	call	printzn
	addl	$24, %esp		// reset the stack and loop
	jmp	pass2_nextline

pass2_leave:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret
//
// Return the word-count for the given instruction line
//
// @param int instruction word
// @param int first extension word
// @param int second extension word
// @param string instruction
// @param int instruction address
// @return int instruction word count
//
inst_word_parse:
	enter	$0, $0
	pushl	%ebx
	pushl	%edi
	pushl	%esi

	// 8  instruction word
	// 12 first extension word
	// 16 second extension word
	// 20 instruction string
	// 24 address

	movl	20(%ebp), %ebx		// instruction string
	addl	$5, %ebx		// ignore the first five characters

	movl	$0, 8(%ebp)		// clear the return values
	movl	$0, 12(%ebp)
	movl	$0, 16(%ebp)
	movl	$1, %esi		// all ops use at least one word

inst_wpop_halt:
	pushl	$4			// compare to halt
	pushl	$inst_halt
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_move		// not halt

	movl	$1, %eax		// halt is one word, all zeroes
	jmp	inst_wp_leave

//// Two operand dispatch

inst_wpop_move:
	pushl	$4			// compare to move
	pushl	$inst_move
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_add		// not move

	movl	$0x1000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

inst_wpop_add:
	pushl	$4			// compare to add
	pushl	$inst_add
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_sub		// not add

	movl	$0x2000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

inst_wpop_sub:
	pushl	$4			// compare to sub
	pushl	$inst_sub
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_comp		// not sub

	movl	$0x3000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

inst_wpop_comp:
	pushl	$4			// compare to comp
	pushl	$inst_comp
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_mult		// not comp

	movl	$0x4000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

inst_wpop_mult:
	pushl	$4			// compare to mult
	pushl	$inst_mult
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_divd		// not mult

	movl	$0x5000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

inst_wpop_divd:
	pushl	$4			// compare to divd
	pushl	$inst_divd
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_rem		// not divd

	movl	$0x6000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

inst_wpop_rem:
	pushl	$4			// compare to rem
	pushl	$inst_rem
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_breq		// not rem

	movl	$0x7000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

/// Branch operand dispatch

inst_wpop_breq:
	pushl	$4			// compare to breq
	pushl	$inst_breq
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_brne		// not breq

	movl	$0xF038, %edi		// move opcode
	jmp	inst_wpop_branch	// parse destination symbol

inst_wpop_brne:
	pushl	$4			// compare to brne
	pushl	$inst_brne
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_brgt		// not brne

	movl	$0xF078, %edi		// move opcode
	jmp	inst_wpop_branch	// parse destination symbol

inst_wpop_brgt:
	pushl	$4			// compare to brgt
	pushl	$inst_brgt
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_brge		// not brgt

	movl	$0xF0B8, %edi		// move opcode
	jmp	inst_wpop_branch	// parse destination symbol

inst_wpop_brge:
	pushl	$4			// compare to brge
	pushl	$inst_brge
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_brlt		// not brge

	movl	$0xF0F8, %edi		// move opcode
	jmp	inst_wpop_branch	// parse destination symbol

inst_wpop_brlt:
	pushl	$4			// compare to brlt
	pushl	$inst_brlt
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_brle		// not brlt

	movl	$0xF138, %edi		// move opcode
	jmp	inst_wpop_branch	// parse destination symbol

inst_wpop_brle:
	pushl	$4			// compare to brle
	pushl	$inst_brle
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_br		// not brle

	movl	$0xF178, %edi		// move opcode
	jmp	inst_wpop_branch	// parse destination symbol

inst_wpop_br:
	pushl	$4			// compare to br
	pushl	$inst_br
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_incr		// not br

	movl	$0xF1F8, %edi		// move opcode
	jmp	inst_wpop_branch	// parse destination symbol

//// Single operand dispatch

inst_wpop_incr:
	pushl	$4			// compare to incr
	pushl	$inst_incr
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_decr		// not incr

	movl	$0xF400, %edi		// move opcode
	jmp	inst_wpop_one		// parse destination operand

inst_wpop_decr:
	pushl	$4			// compare to decr
	pushl	$inst_decr
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_rot		// not decr

	movl	$0xF440, %edi		// move opcode
	jmp	inst_wpop_one		// parse destination operand

inst_wpop_rot:
	pushl	$4			// compare to rot
	pushl	$inst_rot
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_shl		// not rot

	movl	$0xF500, %edi		// move opcode
	jmp	inst_wpop_one		// parse destination operand

inst_wpop_shl:
	pushl	$4			// compare to shl
	pushl	$inst_shl
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_shr		// not shl

	movl	$0xF600, %edi		// move opcode
	jmp	inst_wpop_one		// parse destination operand

inst_wpop_shr:
	pushl	$4			// compare to shr
	pushl	$inst_shr
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_read		// not shr

	movl	$0xF700, %edi		// move opcode
	jmp	inst_wpop_one		// parse destination operand

inst_wpop_read:
	pushl	$4			// compare to read
	pushl	$inst_read
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wpop_prt		// not read

	movl	$0xF480, %edi		// move opcode
	jmp	inst_wpop_one		// parse destination operand

inst_wpop_prt:
	pushl	$4			// compare to prt
	pushl	$inst_prt
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmpl	$0, %eax
	jne	inst_wp_leave		// not prt

	movl	$0xF4C0, %edi		// move opcode
	jmp	inst_wpop_one		// parse destination operand

//// Two Operand Parsing

inst_wpop_two:				// two operands
	pushl	%ebx			// grab the source operand
	pushl	$0
	call	inst_source_op
	movl	(%esp), %edx
	add	$8, %esp

	orl	%eax, %edi		// combine the operand with the opcode

	cmpl	$0, %edx		// check for an extension word
	je	inst_wpop_two_dest

	incl	%esi			// increase the word-count and put the extension word on the return stack
	movl	%edx, 12(%ebp)

inst_wpop_two_dest:
	pushl	%ebx			// grab the destination operand
	pushl	$0
	call	inst_dest_op2
	movl	(%esp), %edx
	add	$8, %esp

	orl	%eax, %edi		// combine the operand with the opcode

	cmpl	$0, %edx		// check for an extension word
	je	inst_wpop_two_done

	incl	%esi			// check if it's the second extension word
	cmpl	$2, %esi
	ja	inst_wpop_two_dest2

inst_wpop_two_dest1:			// first extension word
	movl	%edx, 12(%ebp)
	jmp	inst_wpop_two_done

inst_wpop_two_dest2:			// second extension word
	movl	%edx, 16(%ebp)
	jmp	inst_wpop_two_done

inst_wpop_two_done:			// done parsing two ops
	movl	%edi, 8(%ebp)
	movl	%esi, %eax

	jmp	inst_wp_leave

//// Branch Label Parsing

inst_wpop_branch:			// handle branch extension word
	pushl	24(%ebp)		// get extension word with relative branch address
	pushl	%ebx
	call	inst_branch_op
	addl	$8, %esp

	movl	%eax, 12(%ebp)		// all branch instructions are two words
	movl	%edi, 8(%ebp)
	movl	$2, %eax

	jmp	inst_wp_leave

//// One Operand Parsing

inst_wpop_one:				// handle single operand instructions
	pushl	%ebx			// grab the destination operand
	pushl	$0
	call	inst_dest_op
	movl	(%esp), %edx
	add	$8, %esp

	orl	%eax, %edi		// combine the operand with the opcode

	cmpl	$0, %edx		// check for an extension word
	je	inst_wpop_one_done

	incl	%esi			// increase the word-count and put the extension word on the return stack
	movl	%edx, 12(%ebp)

inst_wpop_one_done:
	movl	%edi, 8(%ebp)
	movl	%esi, %eax

	jmp	inst_wp_leave

//// Done Parsing

inst_wp_leave:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret

//
// Parse the label operand for a branch instruction
//
// @param string instruction string
// @param int instruction address
// @return int branch operand
//
inst_branch_op:
	enter	$0, $0
	pushl	%ebx
	pushl	%edi
	pushl	%esi

	movl	8(%ebp), %ebx		// instruction string
	movl	12(%ebp), %esi		// instruction address
	movl	$symbol_table, %edi

	addl	$5, %ebx		// move to branch label

inst_bo_search:
	pushl	$4			// compare label to symbol table
	pushl	%ebx
	pushl	%edi
	call	ncompare
	addl	$12, %esp

	cmpl	$0, %eax		// match?
	je	inst_bo_found

	addl	$8, %edi		// next symbol table entry
	jmp	inst_bo_search

inst_bo_found:
	movl	4(%edi), %eax		// target address
	subl	%esi, %eax		// subtract instruction address

inst_bo_leave:
	popl	%esi
	popl	%edi
	popl	%ebx
	leave
	ret

//
// Parse the source operand bits for an instruction word
//
// @param int extension word
// @ebx string instruction string, at the operation label
// @return int operand bits
//
inst_source_op:
	enter	$0, $0
	pushl	%ebx

	movl	$0, 8(%ebp)
	addl	$5, %ebx

inst_so_indirect:
	movb	(%ebx), %al			// check for @
	cmp	$64, %al
	jne	inst_so_register		// otherwise jump

	movb	1(%ebx), %al			// check for %
	cmp	$37, %al
	jne	inst_so_indirect_location
	
inst_so_indirect_register:			// we have a @% indirect register ref
	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	orl	$0x0C00, %eax

	jmp	inst_so_leave

inst_so_indirect_location:
	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	shl	%eax				// just a regular indirect location ref
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	orl	$0x800, %eax

	jmp	inst_so_leave

inst_so_register:
	movb	(%ebx), %al			// check for %
	cmp	$37, %al
	jne	inst_so_immediate		// otherwise jum

inst_so_register_direct:
	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	orl	$0x0400, %eax

	jmp	inst_so_leave

inst_so_immediate:
	movb	(%ebx), %al			// check for #
	cmp	$35, %al
	jne	inst_so_location

	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	cmpl	$7, %eax			// check for > 7
	jg	inst_so_large_immediate

	cmpl	$0, %eax
	jl	inst_so_large_immediate

inst_so_small_immediate:
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	orl	$0x600, %eax			// small immediate value

	jmp	inst_so_leave
	
inst_so_large_immediate:
	movl	%eax, 8(%ebp)			// large immediate value in extension word
	movl	$0x0E00, %eax

	jmp	inst_so_leave
	
inst_so_location:
	movl	%ebx, %edx			// get the location value
	pushl	%edx
	call	evaluate
	add	$4, %esp

	shl	%eax				// direct location
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax
	shl	%eax

	jmp	inst_so_leave

inst_so_leave:
	popl	%ebx
	leave
	ret

//
// Parse the destination operand bits for an instruction word
//
// @param int extension word
// @ebx string instruction string, at the operation label
// @return int operand bits
//
inst_dest_op:
	enter	$0, $0				// entrance for instructions with only destination operands
	pushl	%ebx

	movl	$0, %eax
	movl	$0, 8(%ebp)
	addl	$5, %ebx

	jmp	inst_do_ready			// go straight to op parsing

inst_dest_op2:
	enter	$0, $0				// entrance for instructions with source and destination operands
	pushl	%ebx

	movl	$0, %eax
	movl	$0, 8(%ebp)
	addl	$5, %ebx

inst_do_find_comma:
	movb	(%ebx), %al			// go through the string until we get past the comma
	incl	%ebx
	cmp	$44, %al
	jne	inst_do_find_comma

inst_do_ready:					// ready to start parsing

inst_do_indirect:
	movb	(%ebx), %al			// check for @
	cmp	$64, %al
	jne	inst_do_register		// otherwise jump

	movb	1(%ebx), %al			// check for %
	cmp	$37, %al
	jne	inst_do_indirect_location
	
inst_do_indirect_register:			// we have a @% indirect register ref
	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	orl	$0x0030, %eax

	jmp	inst_do_leave

inst_do_indirect_location:
	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	orl	$0x0020, %eax			// just a regular indirect location ref

	jmp	inst_do_leave

inst_do_register:
	movb	(%ebx), %al			// check for %
	cmp	$37, %al
	jne	inst_do_immediate		// otherwise jum

inst_do_register_direct:
	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	orl	$0x0010, %eax

	jmp	inst_do_leave

inst_do_immediate:
	movb	(%ebx), %al			// check for #
	cmp	$35, %al
	jne	inst_do_location

	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	cmpl	$7, %eax			// check for > 7
	jg	inst_do_large_immediate

	cmpl	$0, %eax
	jl	inst_do_large_immediate

inst_do_small_immediate:
	orl	$0x0018, %eax			// small immediate value

	jmp	inst_do_leave
	
inst_do_large_immediate:
	movl	%eax, 8(%ebp)			// large immediate value in extension word
	movl	$0x0038, %eax

	jmp	inst_do_leave
	
inst_do_location:
	movl	%ebx, %edx			// get the location value
	pushl	%edx
	call	evaluate
	add	$4, %esp

	// no-op, because operand in %eax is all we need

	jmp	inst_do_leave

inst_do_leave:
	popl	%ebx
	leave
	ret

//
// Clear the line_buffer string
//
clear_line_buffer:
	enter	$0, $0

	movl	$line_buffer, %eax
	movl	$100, %ecx

clear_lb_loop:	// loop over the string, setting each character to zero
	movb	$0, (%eax)
	incl	%eax
	loop	clear_lb_loop

clear_lb_leave:
	leave
	ret

//
// copy one null-terminated string to another, not including the null-termination
//
// @param string source string
// @param string destination string
//
strcpy:
	enter	$0, $0
	pushl	%ebx

	movl	$0, %eax	// count
	movl	8(%ebp), %ebx	// source string

strcpy_count:
	movb	(%ebx,%eax),%dl	// next character
	cmp	$0, %dl		// is it null?
	je	strcpy_ready

	addl	$1, %eax	// increment character count
	jmp	strcpy_count

strcpy_ready:
	pushl	%eax		// final count
	pushl	12(%ebp)	// destination pointer
	pushl	8(%ebp)		// source string
	call	strncpy

	addl	$12, %esp

strcpy_leave:
	popl	%ebx
	leave
	ret

//
// copy a given number of characters from one string to another
//
// @param string source string
// @param string destination string
// @param int character count
//
strncpy:
	enter	$0, $0
	pushl	%ebx
	pushl	%esi

	movl	$0, %esi
	movl	8(%ebp), %eax	// source string
	movl	12(%ebp), %ebx	// destination string
	movl	16(%ebp), %ecx	// count

	cmpl	$0, %ecx
	jle	strncpy_leave

strncpy_loop:
	movb	(%eax,%esi), %dl
	movb	%dl, (%ebx,%esi)
	incl	%esi
	
	loop	strncpy_loop
	
strncpy_leave:
	popl	%esi
	popl	%ebx
	leave
	ret

//
// print an integer to standard out
//
// @param int integer to print
//
printi:
	enter	$0, $0
	pushal

	movl	8(%ebp), %eax

	pushl	$convertx_buffer
	pushl	%eax
	call	convertx

	movl	$convertx_buffer, %eax
	addl	$4, %eax

	pushl	$4
	pushl	%eax
	call	print

	addl	$16, %esp

printi_leave:
	popal
	leave
	ret

//
// print an integer, followed by a newline, to standard out
//
// @param int integer to print
//
printin:
	enter	$0, $0
	pushal

	movl	8(%ebp), %eax

	pushl	$convertx_buffer
	pushl	%eax
	call	convertx

	movl	$convertx_buffer, %eax
	addl	$4, %eax

	pushl	$4
	pushl	%eax
	call	print

	pushl	$1
	pushl	$newline
	call	print

	addl	$24, %esp

printin_leave:
	popal
	leave
	ret

//
// prints a null-terminated string, followed by a newline, to standard out
//
// @param string null-terminated string to print
//
printzn:
	enter	$0, $0
	pushal

	movl	$0, %eax	// count
	movl	8(%ebp), %ebx

printzn_count:
	movb	(%ebx,%eax),%dl	// next character
	cmp	$0, %dl		// is it null?
	je	printzn_ready

	addl	$1, %eax	// increment character count
	jmp	printzn_count

printzn_ready:
	pushl	%eax		// final count
	pushl	8(%ebp)		// string pointer
	call	print
	addl	$8, %esp

	pushl	$1
	push	$newline
	call	print
	addl	$8, %esp

printzn_leave:
	popal
	leave
	ret

//
// prints a null-terminated string to standard out
//
// @param string null-terminated string to print
//
printz:
	enter	$0, $0
	pushal

	movl	$0, %eax	// count
	movl	8(%ebp), %ebx

printz_count:
	movb	(%ebx,%eax),%dl	// next character
	cmp	$0, %dl		// is it null?
	je	printz_ready

	addl	$1, %eax	// increment character count
	jmp	printz_count

printz_ready:
	pushl	%eax		// final count
	pushl	8(%ebp)		// string pointer
	call	print

	addl	$8, %esp

printz_leave:
	popal
	leave
	ret

//
// prints a given number of space characters
//
// @param int number of spaces
//
print_spaces:
	enter	$0, $0
	pushal

	movl	8(%ebp), %ecx

print_spaces_loop:
	pushl	$1
	pushl	$space
	call	print	
	addl	$8, %esp

	loop	print_spaces_loop

print_spaces_leave:
	popal
	leave
	ret

//
// prints a string to standard out using the given length
//
// @param string string to print
// @param int number of characters to print
//
print:
	enter	$0, $0
	pushal

	pushl	12(%ebp)	// character count
	pushl	8(%ebp)		// string pointer
	pushl	$1		// stdout
	pushl	$0		// dummy
	movl	$0x4, %eax	// SYS_write
	lcall	$0x27, $0

	addl	$16, %esp

print_leave:
	popal
	leave
	ret

