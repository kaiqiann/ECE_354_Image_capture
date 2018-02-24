// #include "address_map_arm.h"
//clean !

#include "time.h"
#include "stdio.h"

#define KEY_BASE              0xFF200050
#define VIDEO_IN_BASE         0xFF203060
#define FPGA_ONCHIP_BASE      0xC8000000
#define TEXT				  0xC9000000

/* This program demonstrates the use of the D5M camera with the DE1-SoC Board
 * It performs the following: 
 * 	1. Capture one frame of video when any key is pressed.
 * 	2. Display the captured frame when any key is pressed.		  
*/
/* Note: Set the switches SW1 and SW2 to high and rest of the switches to low for correct exposure timing while compiling and the loading the program in the Altera Monitor program.
*/
int main(void)
{
	volatile int * KEY_ptr				= (int *) KEY_BASE;
	volatile int * Video_In_DMA_ptr	= (int *) VIDEO_IN_BASE;
	volatile short * Video_Mem_ptr	= (short *) FPGA_ONCHIP_BASE;
	volatile short * TXT	= (short *) TEXT;
	int offset;
	// time stampt use
	char *text_ptr;
	time_t mytime;
	mytime = time(NULL);
	text_ptr = ctime(&mytime);
	
	int x, y;

	*(Video_In_DMA_ptr + 3)	= 0x4;				// Enable the video


	while (1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			*(Video_In_DMA_ptr + 3) = 0x0;			// Disable the video to capture one frame
			while (*KEY_ptr != 0);				// wait for pushbutton KEY release
			break;
		}
	}
	/*
	* adding text 
	*/
	printf("%s",text_ptr);
	offset = (25 << 7) + 1;
	while ( *(text_ptr) )
	{
		*(TXT + offset) = *(text_ptr); // write to the character buffer
		printf("%s",*(TXT + offset));
		++text_ptr;
		++offset;
	}
	
	
	
	
	while (1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			break;
		}
	}
		
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			*(Video_Mem_ptr + (y << 9) + x) = temp2;
		}
	}

}
