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

	cmp	$2, %eax	// error check
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
	pushl	$bye
	call	printz
	addl	$4, %esp

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

	cmp	$-1, %eax		// check for EOF
	je	pass1_print

	pushl	$1			// check for comment
	pushl	$line_buffer
	pushl	$comment
	call	ncompare
	addl	$12, %esp

	cmp	$0, %eax		// ignore comments
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

	cmp	$0, %eax		// ignore empty labels
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

	cmp	$0, %eax		// not a branch statement
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

	cmp	$7, %eax		// is it bigger than 7?
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

	cmp	$-1, %eax		// check for EOF
	je	pass1_print

	pushl	$1			// check for comment
	pushl	$line_buffer
	pushl	$comment
	call	ncompare
	addl	$12, %esp

	cmp	$0, %eax
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

	pushl	%esi
	call	printi
	pushl	$3
	call	print_spaces
	pushl	4(%ebx)
	call	printi
	addl	$8, %esp

	cmp	$1, %eax		// check for single word instructions
	je	pass2_parse_one

	cmp	$2, %eax		// check for two word instructions
	je	pass2_parse_two

pass2_parse_three:			// fall through to three word instructions
	pushl	$1			// print two extension words and the spacing
	call	print_spaces
	pushl	8(%ebx)
	call	printi
	pushl	$1
	call	print_spaces
	pushl	12(%ebx)
	call	printi
	pushl	$4
	call	print_spaces
	addl	$20, %esp

	movl	$3, %ebx
	jmp	pass2_parse_done

pass2_parse_two:
	pushl	$1			// print one extension word and the spacing
	call	print_spaces
	pushl	8(%ebx)
	call	printi
	pushl	$9
	call	print_spaces
	addl	$12, %esp

	movl	$2, %ebx		// set the word-count to two
	jmp	pass2_parse_done

pass2_parse_one:
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
	movl	$0, %esi

inst_wpop_halt:
	pushl	$4			// compare to halt
	pushl	$inst_halt
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmp	$0, %eax
	jne	inst_wpop_move		// not halt

	movl	$1, %eax		// halt is one word, all zeroes
	jmp	inst_wp_leave

inst_wpop_move:
	pushl	$4			// compare to move
	pushl	$inst_move
	pushl	%ebx
	call	ncompare
	add	$12, %esp

	cmp	$0, %eax
	jne	inst_wp_leave		// not move

	movl	$0x1000, %edi		// move opcode
	jmp	inst_wpop_two		// parse two operands

inst_wpop_two:				// two operands
	pushl	%ebx			// grab the source operand
	pushl	$0
	call	inst_source_op
	movl	4(%esp), %edx

	orl	%eax, %edi		// combine the operand with the opcode

	cmp	$0, %edx		// check for an extension word
	jne	inst_wpop_two_dest

	incl	%esi
	movl	%edx, 12(%ebp)

inst_wpop_two_dest:
	pushl	%ebx			// grab the destination operand
	pushl	$0
	call	inst_dest_op
	movl	4(%esp), %edx

	orl	%eax, %edi		// combine the operand with the opcode

	cmp	$0, %edx		// check for an extension word
	jne	inst_wpop_two_done

	incl	%esi			// check if it's the second extension word
	cmp	$1, %esi
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

inst_wp_leave:
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
	movl	$0, %eax
	movb	2(%ebx), %al
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
	movl	$0, %eax			// direct register ref
	movb	2(%ebx), %al
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

	cmp	$7, %eax			// check for > 7
	ja	inst_so_large_immediate

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
	enter	$0, $0
	pushl	%ebx

	movl	$0, 8(%ebp)
	addl	$5, %ebx

inst_do_indirect:
	movb	(%ebx), %al			// check for @
	cmp	$64, %al
	jne	inst_do_register		// otherwise jump

	movb	1(%ebx), %al			// check for %
	cmp	$37, %al
	jne	inst_do_indirect_location
	
inst_do_indirect_register:			// we have a @% indirect register ref
	movl	$0, %eax
	movb	2(%ebx), %al
	orl	$0x0030, %eax

	jmp	inst_do_leave

inst_do_indirect_location:
	movl	%ebx, %edx			// get the immediate value
	incl	%edx
	incl	%edx
	pushl	%edx
	call	evaluate
	add	$4, %esp

	orl	$0x0020, %eax	// just a regular indirect location ref

	jmp	inst_do_leave

inst_do_register:
	movb	(%ebx), %al			// check for %
	cmp	$37, %al
	jne	inst_do_immediate		// otherwise jum

inst_do_register_direct:
	movl	$0, %eax			// direct register ref
	movb	2(%ebx), %al
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

	cmp	$7, %eax			// check for > 7
	ja	inst_do_large_immediate

inst_do_small_immediate:
	orl	$0x0018, %eax	// small immediate value

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

	cmp	$0, %ecx
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
	leave
	ret

//
// print an integer, followed by a newline, to standard out
//
// @param int integer to print
//
printin:
	enter	$0, $0

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
	leave
	ret

//
// prints a null-terminated string, followed by a newline, to standard out
//
// @param string null-terminated string to print
//
printzn:
	enter	$0, $0
	pushl	%ebx

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
	popl	%ebx
	leave
	ret

//
// prints a null-terminated string to standard out
//
// @param string null-terminated string to print
//
printz:
	enter	$0, $0
	pushl	%ebx

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
	popl	%ebx
	leave
	ret

//
// prints a given number of space characters
//
// @param int number of spaces
//
print_spaces:
	enter	$0, $0

	movl	8(%ebp), %ecx

print_spaces_loop:
	pushl	$1
	pushl	$space
	call	print	
	addl	$8, %esp

	loop	print_spaces_loop

print_spaces_leave:
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

