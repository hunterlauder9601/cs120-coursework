.data
	first_Name: .space 50
	last_Name: .space 50
	jedi_Name: .space 6
	text_1: .asciiz "Please enter first name: "
	text_2: .asciiz "Please enter last name: "
	text_3: .asciiz "Invalid input. Program exit."
	firstName_length: .word 0
	lastName_length: .word 0
	space: .asciiz " "
.text
	main:
		addi $s0, $zero, 0
		addi $a0, $s0, 0 #sets s0 to parameter register for subroutine
		jal jediName
		addi $a0, $v0, 0   # take return value (v0) and pace in parameter (a0) for next subroutine 
		jal jediPower
		
		li $v0, 10    # end of program
		syscall
                 		

#=======================================
# start jediName subroutine
# subroutine to get first, last and jedi name
#=======================================
	jediName:
		# Save regs and return address (ra) on stack
		addi    $sp, $sp, -28
		sw      $ra, 0($sp)
		sw      $t0, 4($sp)
		sw      $t1, 8($sp)
		sw      $t2, 12($sp)
		sw      $t3, 16($sp)
		sw      $t4, 20($sp)
		sw      $t5, 24($sp)
			
		#fist name
		li $v0, 4
		la $a0, text_1
		syscall
	
		li $v0, 8
		la $a0, first_Name
		addi $a1, $zero, 50
		syscall
		
		#last name
		li $v0, 4
		la $a0, text_2
		syscall
	
		li $v0, 8
		la $a0, last_Name
		addi $a1, $zero, 50
		syscall
		
		#**gets the length of the first_Name string**
		la $t0 first_Name
		loop:
    		lb   $t1 0($t0)
    		beq  $t1 $zero endLoop
    		addi $t0 $t0 1
    		j loop

	endLoop:
		la $t1 first_Name
		sub $t3 $t0 $t1 #includes the null character
		sw $t3, firstName_length
		
		ble $t3, 3, program_exit_with_error   #if the length is less than 2 (with the null character), exit the program
		
		#**gets the length of the last_Name string**
		la $t0 last_Name
	loop2:
    		lb   $t1 0($t0)
    		beq  $t1 $zero endLoop2
    		addi $t0 $t0 1
    		j loop2
	endLoop2:
		la $t1 last_Name
		sub $t3 $t0 $t1 #includes the null character
		sw $t3, lastName_length
		
		ble $t3, 3, program_exit_with_error   #if the length is less than 2 (with the null character), exit the program
		#creates jedi_Name
		la $t0, last_Name
		la $t6 first_Name
		la $t5, jedi_Name
		lb $t1, 0($t0)
		sb $t1, 0($t5) 
		lb $t1, 1($t0)
		sb $t1, 1($t5)
		lb $t1, 2($t0)
		sb $t1, 2($t5) 

		lb $t1, 0($t6)
		sb $t1, 3($t5)
		lb $t1, 1($t6)
		sb $t1, 4($t5) 
		sb $0, 5($t5) # add char 0
		
		addi $v0, $t5, 0    # this is our return value (v0)  

		# Restore return address (ra) and the t registrs used
		lw      $ra, 0($sp)
		lw      $t0, 4($sp)
		lw      $t1, 8($sp)
		lw      $t2, 12($sp)
		lw      $t3, 16($sp)
		lw      $t4, 20($sp)
		lw      $t5, 24($sp)
		addi    $sp, $sp, 28    # re-position the stack pointer
		jr	$ra
#=======================================
# end jediName subroutine
#=======================================



#=======================================
# start jediPower subroutine
#=======================================
	jediPower:
		# Save regs and return address (ra) on stack
		addi    $sp, $sp, -16
		sw      $ra, 0($sp)
		sw	$t1, 4($sp)
		sw	$t3, 8($sp)
		sw	$t7, 12($sp)
		# get byte 0-4 and add them in reg t7
		addi $t3, $a0, 0    # load t3 with parameter (a0) 
		addi $t7, $0, 0
		lb $t1, 0($t3)
		add $t7, $t7, $t1
		lb $t1, 1($t3)
		add $t7, $t7, $t1
		lb $t1, 2($t3)
		add $t7, $t7, $t1
		lb $t1, 3($t3)
		add $t7, $t7, $t1
		lb $t1, 4($t3)
		add $t7, $t7, $t1
		
		li $v0, 4	   # print jeti name
		la $a0, jedi_Name
		syscall
		
		li $v0, 4
		la $a0, space
		syscall
		
		li $v0, 1            # print jeti power
		addi $a0, $t7, 0
		syscall
		

		
		# Restore return address (ra) and the t registrs used
		lw      $ra, 0($sp)
		lw      $t1, 4($sp)
		lw      $t3, 8($sp)
		lw      $t7, 12($sp)
		addi    $sp, $sp, 16    # re-position the stack pointer
		
		jr $ra      # return to main
#=======================================
# end jediPower subroutine
#=======================================



#=======================================
# program_exit_with_error subroutine (never returns)
#=======================================
	program_exit_with_error:
		li $v0, 4
		la $a0, text_3
		syscall
		li $v0, 10
		syscall
