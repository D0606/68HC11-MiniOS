#include <stdio.h>

int lf();

int main()
{
	lf();
	return 0;	
}

int lf()
{
	
	unsigned char *scsr, *scdr, *origin;
	unsigned char fileData = 0x00, fileData1 = 0x00, lineLength = 0x00, lineLength1 = 0x00,
					address1 = 0x00, addChk = 0x00, myChkSum = 0x00, fileChkSum = 0x00, fileChkSum1 = 0x00,
					data, status = 0, charCount = 0, flag = 0, addFlag = 0, chkFail = 0, failLine = 0, lastLine = 0, lineCount = 0;
	unsigned int address = 0x0000, addLog;
	
	/* Assign pointers to serial data and comms registers. Baud rate defined in monitor programme */
	scsr = (unsigned char *)0x2e;
	scdr = (unsigned char *)0x2f;
	
	printf("Select a text file to upload.\n\r");
	do
	{
		/* Check for valid S19, first character and following character */
		while(((*scsr) & 0x20) == 0x0);
		data = *scdr;
		
		if (data == 'S')
		{
			flag = 0; /* reset flag */
			while(((*scsr) & 0x20) == 0x0);
			data = *scdr;
			if (data == '1')
			{
				charCount = 0; /*Reset char count*/
				myChkSum = 0x00; /*Clear checksum*/
				putchar('/');/* Output for each line */
				flag = 1;  /* Mark ready for reading line */
			}
			if ( data == '9') 
			{
				status = 1; /* Last line, stop operation */
				lastLine = 1;
				charCount = 0;
				myChkSum = 0x00;
				putchar('/');
				flag = 1;
			}
		}
		
			if ( flag == 1)	
			{
				/* Get first line length nibble and bitshift*/
				while(((*scsr) & 0x20) == 0x00);
				lineLength = *scdr;
				if(lineLength >= '0' && lineLength <= '9') /* Check for numeric and offset */
				{
					lineLength = lineLength - 0x30;
				}
				if(lineLength >= 'A' && lineLength <= 'F') /* Check for alpha and offset */
				{
					lineLength = lineLength - 0x37;
				}
				lineLength = lineLength << 4;
				
				/*Get second length nibble and bitshift*/
				while(((*scsr) & 0x20) == 0x00);
				lineLength1 = *scdr;
				if(lineLength1 >= '0' && lineLength1 <= '9')
				{
					lineLength1 = lineLength1 - 0x30;
				}
				if(lineLength1 >= 'A' && lineLength1 <= 'F')
				{
					lineLength1 = lineLength1 - 0x37;
				}
				lineLength = lineLength + lineLength1; /* Add nibbles to calculate full byte */
				myChkSum = myChkSum + lineLength; /* Full address retrieved, process checksum */
				
				/*Get first address nibble and bitshift*/
				while(((*scsr) & 0x20) == 0x00);
				address = *scdr;
				if(address >= '0' && address <= '9')
				{
					address = address - 0x30;
				}
				if(address >= 'A' && address <= 'F')
				{
					address = address - 0x37;
				}
				address = address << 4;
				
				/*Get second address nibble and bitshift*/
				while(((*scsr) & 0x20) == 0x00);
				address1 = *scdr;
				if(address1 >= '0' && address1 <= '9')
				{
					address1 = address1 - 0x30;
				}
				if(address1 >= 'A' && address1 <= 'F')
				{
					address1 = address1 - 0x37;
				}
				address = address + address1;
				myChkSum = myChkSum + address; /* Process checksum for byte */
				address = address << 4;
				charCount+=1; /* Begin counting characters on full bytes*/
				
				/*Get third address nibble and bitshift*/
				while(((*scsr) & 0x20) == 0x00);
				address1 = *scdr;
				if(address1 >= '0' && address1 <= '9')
				{
					address1 = address1 - 0x30;
				}
				if(address1 >= 'A' && address1 <= 'F')
				{
					address1 = address1 - 0x37;
				}
				address = address + address1;			
				address = address << 4;
				addChk = addChk + address1;
				addChk = addChk << 4;
				
				/*Get last address nibble and bitshift*/
				while(((*scsr) & 0x20) == 0x00);
				address1 = *scdr;
				if(address1 >= '0' && address1 <= '9')
				{
					address1 = address1 - 0x30;
				}
				if(address1 >= 'A' && address1 <= 'F')
				{
					address1 = address1 - 0x37;
				}
				address = address + address1;
				addChk = addChk + address1;
				myChkSum = myChkSum + addChk;
				charCount+=1;
				/* Set start address once retrieved on first line only */
				if (addFlag == 0)
				{
					addLog = address;
					addFlag = 1;
				}
				
				if (lastLine == 0)
				{
					/* Assign retrived address to pointer */
					origin = (unsigned char *)address;
					/* Retrieve line data */
					do
					{
						/*Get first nibble and bitshift*/
						while(((*scsr) & 0x20) == 0x00);
						fileData = *scdr;
						if(fileData >= '0' && fileData <= '9')
						{
							fileData = fileData - 0x30;
						}
						if(fileData >= 'A' && fileData <= 'F')
						{
							fileData = fileData - 0x37;
						}
						fileData = fileData << 4;
						
						/*Get second address nibble and bitshift*/
						while(((*scsr) & 0x20) == 0x00);
						fileData1 = *scdr;
						if(fileData1 >= '0' && fileData1 <= '9')
						{
							fileData1 = fileData1 - 0x30;
						}
						if(fileData1 >= 'A' && fileData1 <= 'F')
						{
							fileData1 = fileData1 - 0x37;
						}
						fileData = fileData + fileData1; /*Calculate byte */
						myChkSum = myChkSum + fileData; /*Checksum addition*/
						charCount+=1;
						*origin = fileData; /* Assign pointer and increment */
						origin+=1;
					}while(charCount <= lineLength-2);
				}

				/* Retrive checksum and calculate for validation */
				while(((*scsr) & 0x20) == 0x00);
				fileChkSum = *scdr;
				if(fileChkSum >= '0' && fileChkSum <= '9')
				{
					fileChkSum = fileChkSum - 0x30;
				}
				if(fileChkSum >= 'A' && fileChkSum <= 'F')
				{
					fileChkSum = fileChkSum - 0x37;
				}
				fileChkSum = fileChkSum << 4;
				
				/* Get second checksum nibble and bitshift */
				while(((*scsr) & 0x20) == 0x00);
				fileChkSum1 = *scdr;
				if(fileChkSum1 >= '0' && fileChkSum1 <= '9')
				{
					fileChkSum1 = fileChkSum1 - 0x30;
				}
				if(fileChkSum1 >= 'A' && fileChkSum1 <= 'F')
				{
					fileChkSum1 = fileChkSum1 - 0x37;
				}
				fileChkSum = fileChkSum + fileChkSum1;
				myChkSum = ~myChkSum; /*1s complement for correct checksum value*/
				
				/* Validate line with checksum */
				if(myChkSum != fileChkSum)
				{
					chkFail = 1;
					failLine = lineCount+1;
					status = 1;
					break;
				}
				lineCount+=1; /*increment line count as done and flag ready for next line */
				flag = 0;
			}
			
	}while(status == 0);
		
	/* Process once file has finished or failed */
	if(chkFail == 0)
	{
		printf("\n\n\rDownload completed with %d lines successfully read.\n\r",lineCount);
	}
	else
	{
		printf("\n\n\rError! File read failed on line %d!\n\r", failLine);
	}
	printf("Data origin at: %04x, last received checksum: %02x, validated checksum: %02x\n\r", addLog, fileChkSum, myChkSum);

	return(1);
}
