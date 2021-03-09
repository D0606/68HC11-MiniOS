#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct opAssembler
{
	char instruction[8];
	int bytes;
	char isValid[6];
} opAssembler;

int main()
{
	
	struct opAssembler command[255];
	unsigned char getStart[5], getEnd[5];
	unsigned char data, data1, data2;
	char temp[10], temp1[5], temp2[5];
	unsigned char i, *addStart, *addEnd;
	unsigned int addRange;

	/*Initialse data*/
	strcpy(command[0x1B].instruction,"ABA ");
	command[0x1B].bytes = 0;
	strcpy(command[0x1B].isValid, "Valid");
	
	strcpy(command[0x3A].instruction,"ABX ");
	command[0x3A].bytes = 0;
	strcpy(command[0x3A].isValid, "Valid");
		
	/*strcpy(command[0x183A].instruction,"ADCA ");
	command[0x183A].bytes = 0;
	strcpy(command[0x183A].isValid, "Valid");*/
		
	strcpy(command[0x89].instruction,"ADCA #$");
	command[0x89].bytes = 1; /*Usually*/
	strcpy(command[0x89].isValid, "Valid");
		
	strcpy(command[0x99].instruction,"ADCA $");
	command[0x99].bytes = 2;
	strcpy(command[0x99].isValid, "Valid");
		
	strcpy(command[0xB9].instruction,"ADCA $");
	command[0xB9].bytes = 2;
	strcpy(command[0xB9].isValid, "Valid");
		
	strcpy(command[0xA9].instruction,"ADCA $");
	command[0xA9].bytes = 1;
	strcpy(command[0xA9].isValid, "Valid");
		
	/*strcpy(command[0x18A9].instruction,"ADCA $");
	command[0x18A9].bytes = 1;
	strcpy(command[0x18A9].isValid, "Valid");*/
		
	strcpy(command[0xC9].instruction,"ADCB #$");
	command[0xC9].bytes = 1; /*Usually*/
	strcpy(command[0xC9].isValid, "Valid");
		
	strcpy(command[0xD9].instruction,"ADCB $");
	command[0xD9].bytes = 2;
	strcpy(command[0xD9].isValid, "Valid");
		
	strcpy(command[0xF9].instruction,"ADCB $");
	command[0xF9].bytes = 2;
	strcpy(command[0xF9].isValid, "Valid");
		
	strcpy(command[0xE9].instruction,"ADCB $");
	command[0xE9].bytes = 1;
	strcpy(command[0xE9].isValid, "Valid");
		
	/*strcpy(command[0x18E9].instruction,"ADCB $");
	command[0x18E9].bytes = 1;
	strcpy(command[0x18E9].isValid, "Valid");*/
		
	strcpy(command[0x8B].instruction,"ADDA #$");
	command[0x8B].bytes = 1; /*Usually*/
	strcpy(command[0x8B].isValid, "Valid");
		
	strcpy(command[0x9B].instruction,"ADDA $");
	command[0x9B].bytes = 2;
	strcpy(command[0x9B].isValid, "Valid");
		
	strcpy(command[0xBB].instruction,"ADDA $");
	command[0xBB].bytes = 2;
	strcpy(command[0xBB].isValid, "Valid");
		
	strcpy(command[0xAB].instruction,"ADDA $");
	command[0xAB].bytes = 1;
	strcpy(command[0xAB].isValid, "Valid");
		
	/*strcpy(command[0x18AB].instruction,"ADDA $");
	command[0x18AB].bytes = 1;
	strcpy(command[0x18AB].isValid, "Valid");*/
		
	strcpy(command[0xCB].instruction,"ADDB #$");
	command[0xCB].bytes = 1; /*Usually*/
	strcpy(command[0xCB].isValid, "Valid");
		
	strcpy(command[0xDB].instruction,"ADDB $");
	command[0xDB].bytes = 2;
	strcpy(command[0xDB].isValid, "Valid");
		
	strcpy(command[0xFB].instruction,"ADDB $");
	command[0xFB].bytes = 2;
	strcpy(command[0xFB].isValid, "Valid");
		
	strcpy(command[0xEB].instruction,"ADDB $");
	command[0xEB].bytes = 1;
	strcpy(command[0xEB].isValid, "Valid");
		
	/*strcpy(command[0x18EB].instruction,"ADDB $");
	command[0x18EB].bytes = 1;
	strcpy(command[0x18EB].isValid, "Valid");*/
		
	strcpy(command[0xC3].instruction,"ADDD #$");
	command[0xC3].bytes = 2;
	strcpy(command[0xC3].isValid, "Valid");
		
	strcpy(command[0xD3].instruction,"ADDD $");
	command[0xD3].bytes = 1;
	strcpy(command[0xD3].isValid, "Valid");
	
	strcpy(command[0xF3].instruction,"ADDD $");
	command[0xF3].bytes = 2;
	strcpy(command[0xF3].isValid, "Valid");
	
	strcpy(command[0xE3].instruction,"ADDD $");
	command[0xE3].bytes = 1;
	strcpy(command[0xE3].isValid, "Valid");
	
	/*strcpy(command[0x18E3].instruction,"ADDD $");
	command[0x18E3].bytes = 1;
	strcpy(command[0x18E3].isValid, "Valid");*/
	
	strcpy(command[0x80].instruction,"SUBA #$");
	command[0x80].bytes = 1; /*Usually*/
	strcpy(command[0x80].isValid, "Valid");
	
	strcpy(command[0x90].instruction,"SUBA $");
	command[0x90].bytes = 2;
	strcpy(command[0x90].isValid, "Valid");
	
	strcpy(command[0xB0].instruction,"SUBA $");
	command[0xB0].bytes = 2;
	strcpy(command[0xB0].isValid, "Valid");
	
	strcpy(command[0xA0].instruction,"SUBA $");
	command[0xA0].bytes = 1;
	strcpy(command[0xA0].isValid, "Valid");
	
	/*strcpy(command[0x18A0].instruction,"SUBA $");
	command[0x18A0].bytes = 1;
	strcpy(command[0x18A0].isValid, "Valid");*/
	
	strcpy(command[0xC0].instruction,"SUBB #$");
	command[0xC0].bytes = 1; /*Usually*/
	strcpy(command[0xC0].isValid, "Valid");
	
	strcpy(command[0xD0].instruction,"SUBB $");
	command[0xD0].bytes = 2;
	strcpy(command[0xD0].isValid, "Valid");
	
	strcpy(command[0xF0].instruction,"SUBB $");
	command[0xF0].bytes = 2;
	strcpy(command[0xF0].isValid, "Valid");
	
	strcpy(command[0xE0].instruction,"SUBB $");
	command[0xE0].bytes = 1;
	strcpy(command[0xE0].isValid, "Valid");
	
	/*strcpy(command[0x18E0].instruction,"SUBB $");
	command[0x18E0].bytes = 1;
	strcpy(command[0x18E0].isValid, "Valid");*/
	
	strcpy(command[0x83].instruction,"SUBD #$");
	command[0x83].bytes = 2;
	strcpy(command[0x83].isValid, "Valid");
	
	strcpy(command[0x93].instruction,"SUBD $");
	command[0x93].bytes = 1;
	strcpy(command[0x93].isValid, "Valid");
	
	strcpy(command[0xB3].instruction,"SUBD $");
	command[0xB3].bytes = 2;
	strcpy(command[0xB3].isValid, "Valid");
	
	strcpy(command[0xA3].instruction,"SUBD $");
	command[0xA3].bytes = 1;
	strcpy(command[0xA3].isValid, "Valid");
	
	/*strcpy(command[0x18A3].instruction,"SUBD $");
	command[0x18A3].bytes = 1;
	strcpy(command[0x18A3].isValid, "Valid");*/
	
	strcpy(command[0x86].instruction,"LDAA #$");
	command[0x86].bytes = 1; /*Usually*/
	strcpy(command[0x86].isValid, "Valid");
	
	strcpy(command[0x96].instruction,"LDAA $");
	command[0x96].bytes = 2;
	strcpy(command[0x96].isValid, "Valid");
	
	strcpy(command[0xB6].instruction,"LDAA $");
	command[0xB6].bytes = 2;
	strcpy(command[0xB6].isValid, "Valid");
	
	strcpy(command[0xA6].instruction,"LDAA $");
	command[0xA6].bytes = 1;
	strcpy(command[0xA6].isValid, "Valid");
	
	/*strcpy(command[0x18A6].instruction,"LDAA $");
	command[0x18A6].bytes = 1;
	strcpy(command[0x18A6].isValid, "Valid");
	
	strcpy(command[0xC6].instruction,"LDAB #$");
	command[0xC6].bytes = 2; /*Usually*/
	strcpy(command[0xC6].isValid, "Valid");
	
	strcpy(command[0xD6].instruction,"LDAB $");
	command[0xD6].bytes = 2;
	strcpy(command[0xD6].isValid, "Valid");
	
	strcpy(command[0xF6].instruction,"LDAB $");
	command[0xF6].bytes = 2;
	strcpy(command[0xF6].isValid, "Valid");
	
	strcpy(command[0xE6].instruction,"LDAB $");
	command[0xE6].bytes = 1;
	strcpy(command[0xE6].isValid, "Valid");
	
	/*strcpy(command[0x18E6].instruction,"LDAB $");
	command[0x18E6].bytes = 1;
	strcpy(command[0x18E6].isValid, "Valid");*/
	
	strcpy(command[0xCC].instruction,"LDD #$");
	command[0xCC].bytes = 2;
	strcpy(command[0xCC].isValid, "Valid");
	
	strcpy(command[0xDC].instruction,"LDD $");
	command[0xDC].bytes = 1;
	strcpy(command[0xDC].isValid, "Valid");
	
	strcpy(command[0xFC].instruction,"LDD $");
	command[0xFC].bytes = 2;
	strcpy(command[0xFC].isValid, "Valid");
	
	strcpy(command[0xEC].instruction,"LDD $");
	command[0xEC].bytes = 1;
	strcpy(command[0xEC].isValid, "Valid");
	
	/*strcpy(command[0x18EC].instruction,"LDD $");
	command[0x18EC].bytes = 1;
	strcpy(command[0x18EC].isValid, "Valid");*/
	
	strcpy(command[0x97].instruction,"STAA $");
	command[0x97].bytes = 2; /*Top 8 bits assumed 00*/
	strcpy(command[0x97].isValid, "Valid");
	
	strcpy(command[0xB7].instruction,"STAA $");
	command[0xB7].bytes = 2;
	strcpy(command[0xB7].isValid, "Valid");
	
	strcpy(command[0xA7].instruction,"STAA $");
	command[0xA7].bytes = 1;
	strcpy(command[0xA7].isValid, "Valid");
	
	/*strcpy(command[0x18A7].instruction,"STAA $");
	command[0x18A7].bytes = 1;
	strcpy(command[0x18A7].isValid, "Valid");*/
	
	strcpy(command[0xD7].instruction,"STAB $");
	command[0xD7].bytes = 2; /*Top 8 bits assumed 00*/
	strcpy(command[0xD7].isValid, "Valid");
	
	strcpy(command[0xF7].instruction,"STAB $");
	command[0xF7].bytes = 2;
	strcpy(command[0xF7].isValid, "Valid");
	
	strcpy(command[0xE7].instruction,"STAB $");
	command[0xE7].bytes = 1;
	strcpy(command[0xE7].isValid, "Valid");
	
	/*strcpy(command[0x18E7].instruction,"STAB $");
	command[0x18E7].bytes = 1;
	strcpy(command[0x18E7].isValid, "Valid");*/
	
	strcpy(command[0xDD].instruction,"STD $");
	command[0xDD].bytes = 1;
	strcpy(command[0xDD].isValid, "Valid");
	
	strcpy(command[0xFD].instruction,"STD $");
	command[0xFD].bytes = 2;
	strcpy(command[0xFD].isValid, "Valid");
	
	strcpy(command[0xED].instruction,"STD $");
	command[0xED].bytes = 1;
	strcpy(command[0xED].isValid, "Valid");
	
	/*strcpy(command[0x18ED].instruction,"STD $");
	command[0x18ED].bytes = 1;
	strcpy(command[0x18ED].isValid, "Valid");*/
	

	/*Get the disassembler paramters*/
	printf("Please enter a start address: ");
	gets(getStart); /*Obtain user entered address - 3000 and after seems clear*/
	sscanf(getStart, "%x", &addStart); /*assign input to addvalue*/
	printf("\n\rAddress obtained: %x, %d\n\r", addStart, addStart);
	
	printf("Please enter an end address: ");
	gets(getEnd); /*Obtain user entered address - 3000 and after seems clear*/
	sscanf(getEnd, "%x", &addEnd); /*assign input to addvalue*/
	printf("\n\rAddress obtained: %x, %d\n\r", addEnd, addEnd);
	
	/*get opcode*/
	addRange = addEnd - addStart;
	printf("Range = %d\n\r", addRange);
	
	for(i = 0; i < addRange+1; i++)
	{
		/*Clear the strings*/
		temp[0] = '\0';
		temp1[0] = '\0';
		temp2[0] = '\0';
		
		data = *addStart;
		printf("\n\rAddress: %x, Data: %02x,", addStart, data);
		
		if (data == 0x18)
		{
			printf("\n\r18 FOUND\n\r");
		}
		
		/*look up string*/
		if (strcmp(command[data].isValid, "Valid") == 0) /*Check valid tab*/
		{
			strcpy(temp, command[data].instruction);
				
			/*look up number of bytes next*/
			if (command[data].bytes == 2)
			{
				data1 = *(addStart+1);
				sprintf(temp1, "%02x", data1);
				data2 = *(addStart+2);
				sprintf(temp2, "%02x", data2);
				strcat(temp1, temp2);
				i++;
				i++;
				*addStart++;
				*addStart++;
			}
			
			if (command[data].bytes == 1)
			{
				data1 = *(addStart+1);
				sprintf(temp1, "%02x", data1);
				i++;
				*addStart++;
			}
		
			strcat(temp,temp1);
			printf("\tCommand: %s", temp);
			
		}
		*addStart++;
	}
}





