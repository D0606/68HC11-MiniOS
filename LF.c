int main()
{
	
	unsigned char *scsr, *scdr, *origin, data, status, charCount, flag, i = 0, chkFail = 0, failLine = 0;
	unsigned int address = 0x0000;
	unsigned char fileData=0x00, fileData1=0x00, lineCount, lineLength=0x00, lineLength1=0x00,
					address1=0x00, addChk = 0x00, myChkSum = 0x00, fileChkSum = 0x00, fileChkSum1 = 0x00;
	
	charCount=0;
	lineCount =0;
	flag =0;
	status =0;
	
	/* Note no config needed for baud rate since already defined in monitor program*/
	scsr = (unsigned char *)0x2e;
	scdr = (unsigned char *)0x2f;
	
	do
	{
		while(((*scsr) & 0x20) == 0x0);
		data = *scdr;
		if ( data == 'S')
		{
			flag = 0; /* reset char count */
			while(((*scsr) & 0x20) == 0x0);
			data = *scdr;
			if ( data == '1')
			{
				charCount = 0;
				myChkSum = 0x00;
				putchar('/');/* optional to save time remove */
				flag = 1;  /* tell to start counting characters */
			}
			if ( data == '9') 
			{
				status = 1; /* Temp stop if S9 detected */
			}
		}
			if ( flag == 1)	
			{
				while(((*scsr) & 0x20) == 0x00);
				lineLength = *scdr;
				if(lineLength >= '0' && lineLength <= '9')
				{
					lineLength = lineLength - 0x30;
				}
				if(lineLength >= 'A' && lineLength <= 'F')
				{
					lineLength = lineLength - 0x37;
				}
				lineLength = lineLength << 4;
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
				lineLength = lineLength + lineLength1;
				myChkSum = myChkSum + lineLength; /*Checksum addition*/
				
				/*Get first address nibble*/
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
				
				/*Get second address nibble*/
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
				myChkSum = myChkSum + address; /*Checksum addition*/
				address = address << 4;
				charCount+=1;
				
				/*Get third address nibble*/
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
				
				/*Get last address nibble*/
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
				
				origin = (unsigned char *)address;
				
				do
				{
					/*Get first nibble*/
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
					/*Get second address nibble*/
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
					fileData = fileData + fileData1;
					myChkSum = myChkSum + fileData; /*Checksum addition*/
					charCount+=1;
					*origin = fileData;
					origin+=1;
				}while(charCount <= lineLength-2);

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
				
				/*Get second address nibble*/
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
				if(myChkSum != fileChkSum)
				{
					chkFail = 1;
					failLine = lineCount+1;
					status = 1;
					break;
				}
				lineCount+=1;
				flag = 0;
			}
	}while(status == 0);
		
		if(chkFail == 0)
		{
			printf("\n\rDownload completed with %d lines successfully read.\n\r",lineCount);
		}
		else
		{
			printf("\n\rError! File read failed on line %d!\n\r", failLine);
		}
		printf("Programme start address: %04x, received checksum: %02x, validated checksum: %02x\n\r", address, fileChkSum, myChkSum);
	    /*printf("Last S1 Address + data + checksum = %02x \n\r",((charCount-1)/2) - 1);*/
		return(0);
}
