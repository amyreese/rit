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
	movl	$0x5, %eax	// SYS_open
	lcall	$0x27, $0
	addl	$12, %esp

	cmp	$2, %eax	// error check
	jle	main_error

	movl	%eax, file	// new file descriptor

	call	pass1
	call	pass2
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
	enter	$4, $0
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
// second pass processing
//
pass2:
	enter	$0, $0

pass2_leave:
	leave
	ret

//
// Return the word-count for the given instruction line
//
// @param string instruction
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

