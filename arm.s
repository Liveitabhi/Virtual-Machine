li $r28,3
sw $r28,$zero(0)
sw $r28,$one(0)
sw $r28,$one(1)

main:
	lw $r28,$zero(0)
	sw $zero,$r28(0)
	add $r28,$r28,$one
	sw $zero,$r28(0)
	add $r28,$r28,$one
	sw $zero,$r28(0)
	add $r28,$r28,$one
	sw $r28,$zero(0)

	lw $r27,$one(0)
	lw $r28,$r27(0)
	lw $r27,$zero(0)
	sw $r28,$r27(0)
	add $r27,$r27,$one
	sw $r27,$zero(0)
	lw $r27,$one(0)
	lw $r28,$r27(2)
	lw $r27,$zero(0)
	sw $r28,$r27(0)
	add $r27,$r27,$one
	sw $r27,$zero(0)
	lw $r28,$zero(0)
	addi $r28,$r28,-1
	lw $r27,$r28(0)
	addi $r28,$r28,-1
	lw $r26,$r28(0)
	seq $r26,$r26,$r27
	sw $r26,$r28(0)
	add $r28,$r28,$one
	sw $r28,$zero(0)
	lw $r28,$zero(0)
	addi $r28,$r28,-1
	sw $r28,$zero(0)
	lw $r0,$r28(0)

	lw $r28,$zero(0)
	sw $r29,$r28(0)
	add $r28,$r28,$one
	lw $r27,$one(0)
	sw $r27,$r28(0)
	add $r28,$r28,$one
	lw $r27,$one(1)
	sw $r27,$r28(0)
	add $r28,$r28,$one
	addi $r27,$r28,-3
	sw $r27,$one(1)
	sw $r28,$one(0)
	jal main1

	lw $r28,$zero(0)
	addi $r28,$r28,-1
	sw $r28,$zero(0)
	lw $r0,$r28(0)

main1:
end:
	j end
