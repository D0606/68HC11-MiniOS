int main()
{
	
	unsigned char *scsr, *scdr, *origin, *ptrLength, data, status, charCount, flag, i = 0;
	unsigned int address = 0x0000;
/*	unsigned char arrLength[3] = {'0','0','\0'}, arrAddress = ('0', '0', '0', '0', '\0'} *//*arrContent[100];*/
	unsigned char lineCount, lineLength=0x00, lineLength1=0x00, address1=0x00;
	
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
				/*putchar('>');*/ /* optional to save time remove */
				flag = 1;  /* tell to start counting characters */
				lineCount++;
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
				lineLength = lineLength - 0x30;
				lineLength = lineLength << 4;
				while(((*scsr) & 0x20) == 0x00);
				lineLength1 = *scdr;
				lineLength1 = lineLength1 - 0x30;
				lineLength = lineLength + lineLength1;
				
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
				if(address1 >= '0' && address1 <= '9')
				{
					address1 = address1 - 0x30;
				}
				if(address1 >= 'A' && address1 <= 'F')
				{
					address1 = address1 - 0x37;
				}
				address = address + address1;		

				flag = 0;
				printf("Length: %x, Address: %x\n\r", lineLength, address);

/*				do
				{
					while(((*scsr) & 0x20) == 0x0);
					arrContent[charCount] = *scdr;
					charCount++;
				}while(charCount <= 69);
*/				
				
				
				/* do rest extract length, address
				/* You can use XON/XOFF or change delay on hyperterm */
				/*Don't forget to ignore all characters after line length */
			}
	}while(status == 0);
			
		printf("\n\rDownload completed S %d lines \n\r",lineCount);
		printf("Last S1 Address + data + checksum = %02x \n\r",((charCount-1)/2) - 1);
		return(0);
}
