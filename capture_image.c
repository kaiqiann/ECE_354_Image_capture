#include "address_map_arm.h"
#include "altera_up_avalon_character_buffer.h"
#include "time.h"

#define KEY_BASE              0xFF200050
#define VIDEO_IN_BASE         0xFF203060
#define FPGA_ONCHIP_BASE      0xC8000000

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
	/*
	* initializing the alt up char buffer to writ stuff
	*/
	char* name = (char*) "DE1_SoC_With_D5M"		//name for the device
	char* buffer;
	alt_up_char_buffer_init(alt_up_char_buffer_dev name));
	char message = 0xff;
	
	/*
	* time
	*/
	time_t rawtimel
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);			
	
	int x, y;

	*(Video_In_DMA_ptr + 3)	= 0x4;				// Enable the video

	while (1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			*(Video_In_DMA_ptr + 3) = 0x0;			// Disable the video to capture one frame
			alt_up_char_buffer_string(buffer, message, 10, 100); //draw random message 
			printf("current time: \n", asctime(timeinfo);		//print time
			while (*KEY_ptr != 0);				// wait for pushbutton KEY release
			break;
		}
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
