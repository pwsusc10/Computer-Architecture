/**********************************************************************
 * Copyright (c) 2021-2022
 *  Sang-Hoon Kim <sanghoonkim@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

/* To avoid security error on Visual Studio */
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

/*====================================================================*/
/*          ****** DO NOT MODIFY ANYTHING FROM THIS LINE ******       */
#define MAX_NR_TOKENS	32	/* Maximum length of tokens in a command */
#define MAX_TOKEN_LEN	64	/* Maximum length of single token */
#define MAX_ASSEMBLY	256 /* Maximum length of assembly string */
#define MAX_Register	32

typedef unsigned char bool;
#define true	1
#define false	0
/*          ****** DO NOT MODIFY ANYTHING UP TO THIS LINE ******      */
/*====================================================================*/


/***********************************************************************
 * translate()
 *
 * DESCRIPTION
 *   Translate assembly represented in @tokens[] into a MIPS instruction.
 *   This translate should support following 13 assembly commands
 *
 *    - add
 *    - addi
 *    - sub
 *    - and
 *    - andi
 *    - or
 *    - ori
 *    - nor
 *    - lw
 *    - sw
 *    - sll
 *    - srl
 *    - sra
 *    - beq
 *    - bne
 *
 * RETURN VALUE
 *   Return a 32-bit MIPS instruction
 *
 */
int Mips_num(char tokens[])
{
	if(strcmp(tokens, "zero") == 0)
		return 0;
	else if(strcmp(tokens, "at") == 0)
		return 1;
	else if(strcmp(tokens, "v0") == 0)
		return 2;
	else if(strcmp(tokens, "v1") == 0)
		return 3;
	else if(strcmp(tokens, "a0") == 0)
		return 4;
	else if(strcmp(tokens, "a1") == 0)
		return 5;
	else if(strcmp(tokens, "a2") == 0)
		return 6;
	else if(strcmp(tokens, "a3") == 0)
		return 7;
	else if(strcmp(tokens, "t0") == 0)
		return 8;
	else if(strcmp(tokens, "t1") == 0)
		return 9;
	else if(strcmp(tokens, "t2") == 0)
		return 10;
	else if(strcmp(tokens, "t3") == 0)
		return 11;
	else if(strcmp(tokens, "t4") == 0)
		return 12;
	else if(strcmp(tokens, "t5") == 0)
		return 13;
	else if(strcmp(tokens, "t6") == 0)
		return 14;
	else if(strcmp(tokens, "t7") == 0)
		return 15;
	else if(strcmp(tokens, "s0") == 0)
		return 16;
	else if(strcmp(tokens, "s1") == 0)
		return 17;
	else if(strcmp(tokens, "s2") == 0)
		return 18;
	else if(strcmp(tokens, "s3") == 0)
		return 19;
	else if(strcmp(tokens, "s4") == 0)
		return 20;
	else if(strcmp(tokens, "s5") == 0)
		return 21;
	else if(strcmp(tokens, "s6") == 0)
		return 22;
	else if(strcmp(tokens, "s7") == 0)
		return 23;
	else if(strcmp(tokens, "t8") == 0)
		return 24;
	else if(strcmp(tokens, "t9") == 0)
		return 25;
	else if(strcmp(tokens, "k1") == 0)
		return 26;
	else if(strcmp(tokens, "k2") == 0)
		return 27;
	else if(strcmp(tokens, "gp") == 0)
		return 28;
	else if(strcmp(tokens, "sp") == 0)
		return 29;
	else if(strcmp(tokens, "fp") == 0)
		return 30;
	else if(strcmp(tokens, "ra") == 0)
		return 31;
	else
		return 99;
}

int R_instruction(char *tokens[], int opcode, int funct)
{
	long long result = 0;

	long long rs, rt, rd, shamt;

	if((strcmp(tokens[0], "sll") && strcmp(tokens[0], "srl") && strcmp(tokens[0], "sra")) == 0)
	{
		rs = 0;
		rd = Mips_num(tokens[1]);
		rt = Mips_num(tokens[2]);
		if(atoi(tokens[3]) == 0)
		{
			shamt =strtol(tokens[3], NULL, 16);
		}
		else
			shamt = atoi(tokens[3]);
	}
	else
	{
		rd = Mips_num(tokens[1]);
		rs = Mips_num(tokens[2]);
		rt = Mips_num(tokens[3]);
		shamt = 0;
	}

	result = opcode * pow(2, 26) + rs * pow(2, 21) + rt * pow(2, 16) + rd * pow(2, 11) + shamt * pow(2, 6) + funct;

	return result;
}


int I_instruction(char *tokens[], int opcode)
{
	long long result = 0;

	long long rs, rt, number;

	rt = Mips_num(tokens[1]);
	rs = Mips_num(tokens[2]);
	if(atoi(tokens[3]) == 0)
	{
		number = strtol(tokens[3], NULL, 16);
	}
	else
	{
		number = atoi(tokens[3]);
	}

	if(number < 0)
	{
		number = pow(2, 16) + number;
	}
	result = opcode * pow(2, 26) + rs * pow(2, 21) + rt * pow(2, 16) + number;

	return result;
}

static unsigned int translate(int nr_tokens, char *tokens[])
{
	/* TODO:
	 * This is an example MIPS instruction. You should change it accordingly.
	 */
	long long result;

	if(strcmp(tokens[0], "addi") && strcmp(tokens[0], "andi") && strcmp(tokens[0], "ori") &&
					strcmp(tokens[0], "lw") && strcmp(tokens[0], "sw") &&
					strcmp(tokens[0], "beq") && strcmp(tokens[0], "bne"))
	{
		if(strcmp(tokens[0], "add") == 0)
		{
			result = R_instruction(tokens, 0, 0x20);
		}
		else if(strcmp(tokens[0], "sub") == 0)
		{
			result = R_instruction(tokens, 0, 0x22);
		}
		else if(strcmp(tokens[0], "and") == 0)
		{
			result = R_instruction(tokens, 0, 0x24);
		}
		else if(strcmp(tokens[0], "or") == 0)
		{
			result = R_instruction(tokens, 0, 0x25);
		}
		else if(strcmp(tokens[0], "nor") == 0)
		{
			result = R_instruction(tokens, 0, 0x27);
		}
		else if(strcmp(tokens[0], "sll") == 0)
		{
			result = R_instruction(tokens, 0, 0x00);
		}
		else if(strcmp(tokens[0], "srl") == 0)
		{
			result = R_instruction(tokens, 0, 0x02);
		}
		else if(strcmp(tokens[0], "slt") == 0)
		{
			result = R_instruction(tokens, 0, 0x2a);
		}
		else
		{
			result = R_instruction(tokens, 0, 0x03);
		}
	}
	else
	{
		if(strcmp(tokens[0], "addi") == 0)
		{
			result = I_instruction(tokens, 0x08);
		}
		else if(strcmp(tokens[0], "andi") == 0)
		{
			result = I_instruction(tokens, 0x0c);
		}
		else if(strcmp(tokens[0], "ori") == 0)
		{
			result = I_instruction(tokens, 0x0d);
		}
		else if(strcmp(tokens[0], "lw") == 0)
		{
			result = I_instruction(tokens, 0x23);
		}
		else if(strcmp(tokens[0], "sw") == 0)
		{
			result = I_instruction(tokens, 0x2b);
		}
		else if(strcmp(tokens[0], "beq") == 0)
		{
			result = I_instruction(tokens, 0x04);
		}
		else
		{
			result = I_instruction(tokens, 0x05);
		}
	}
	return result;
}



/***********************************************************************
 * parse_command()
 *
 * DESCRIPTION
 *   Parse @assembly, and put each assembly token into @tokens[] and the number
 *   of tokes into @nr_tokens. You may use this implemention or your own
 *   from PA0.
 *
 *   A assembly token is defined as a string without any whitespace (i.e., space
 *   and tab in this programming assignment). For exmaple,
 *     command = "  add t1   t2 s0 "
 *
 *   then, nr_tokens = 4, and tokens is
 *     tokens[0] = "add"
 *     tokens[1] = "t0"
 *     tokens[2] = "t1"
 *     tokens[3] = "s0"
 *
 *   You can assume that the characters in the input string are all lowercase
 *   for testing.
 *
 *
 * RETURN VALUE
 *   Return 0 after filling in @nr_tokens and @tokens[] properly
 *
 */
static int parse_command(char *assembly, int *nr_tokens, char *tokens[])
{
	char *curr = assembly;
	int token_started = false;
	*nr_tokens = 0;

	while (*curr != '\0') {  
		if (isspace(*curr)) {  
			*curr = '\0';
			token_started = false;
		} else {
			if (!token_started) {
				tokens[*nr_tokens] = curr;
				*nr_tokens += 1;
				token_started = true;
			}
		}
		curr++;
	}

	return 0;
}


/*====================================================================*/
/*          ****** DO NOT MODIFY ANYTHING BELOW THIS LINE ******      */

/***********************************************************************
 * The main function of this program.
 */
int main(int argc, char * const argv[])
{
	char assembly[MAX_ASSEMBLY] = { '\0' };
	FILE *input = stdin;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (!input) {
			fprintf(stderr, "No input file %s\n", argv[0]);
			return EXIT_FAILURE;
		}
	}

	if (input == stdin) {
		printf("*********************************************************\n");
		printf("*          >> SCE212 MIPS translator  v0.10 <<          *\n");
		printf("*                                                       *\n");
		printf("*                                       .---.           *\n");
		printf("*                           .--------.  |___|           *\n");
		printf("*                           |.------.|  |=. |           *\n");
		printf("*                           || >>_  ||  |-- |           *\n");
		printf("*                           |'------'|  |   |           *\n");
		printf("*                           ')______('~~|___|           *\n");
		printf("*                                                       *\n");
		printf("*                                 Spring 2022           *\n");
		printf("*********************************************************\n\n");
		printf(">> ");
	}

	while (fgets(assembly, sizeof(assembly), input)) {
		char *tokens[MAX_NR_TOKENS] = { NULL };
		int nr_tokens = 0;
		unsigned int machine_code;

		for (size_t i = 0; i < strlen(assembly); i++) {
			assembly[i] = tolower(assembly[i]);
		}

		if (parse_command(assembly, &nr_tokens, tokens) < 0)
			continue;

		machine_code = translate(nr_tokens, tokens);

		fprintf(stderr, "0x%08x\n", machine_code);

		if (input == stdin) printf(">> ");
	}

	if (input != stdin) fclose(input);

	return EXIT_SUCCESS;
}

