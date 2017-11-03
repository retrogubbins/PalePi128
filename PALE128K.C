#include <stdio.h>

#include "PALESDL.H"
#include "PALEDOS_VID.H"
#include "PALEDOS_GUI.H"
#include "PALEDISK.H"
#include "PALESDL_IO.H"




void bank_latch128k(unsigned char value)
{
    bank_latch=value;
        //if(debug==1)printf("Bank Switch %2x",value);


}



void vid_latch128k(UBYTE value){
 char lbl[100];

     video_latch=value;


//      if(debug==1)
//              printf("Port &80 (%02X)\n", value);
//      if (value & 0x03) {
// Cassette/Speaker 
//       if(debug==1)
//              printf("Cassette/Speaker accessed\n");
//      }
//      if (value & 0x04) {
//
//      }
//      if (value & 0x08) {
//
//      }

        if (value & 0x10)
        {
                show_alt_green=1;
        }
        else
        {
                show_alt_green=0;
        }
        
        if (value & 0x20)
        {
                show_allbanks=0;
        }
        else
        {
                show_allbanks=1;
        }

        if (value & 0x40 && Line_Blank==0)
        {               //Line Blanking monostable - freezes z80 till next scanline end
                Line_Blank=1;
                z80_stop_emulating();
        }       

}




void outp_128(UWORD port, UBYTE value){
    port = port & 0xFF;
        switch (port) {
                case 0x82:
                        bank_latch128k(value);
                        break;
                case 0x80:
                        vid_latch128k(value);
                        break;
                default:
                        if(debug==1)
                                printf("Trying to out to port %02X (%02X)\n",port,value);
        }
}

Uint8 getpixel_128(Uint16 start_offset, Uint8 bit)
{
        Uint8 red=0, blue=0, green=0,b1,b2,b3;
        Uint8 colour = 0;

        //Important for CPM
        start_offset=start_offset%0x4000;

        if(show_allbanks==1)
        {
                b1=bank2[0x4000+start_offset];  //red
                b2=bank2[0x0000+start_offset]; //blue
                if(show_alt_green==1)
                        b3=bank2[0xc000+start_offset];  //alt green mirror
                else
                        b3=bank2[0x8000+start_offset];  //green mirror
        }
        else
                b1=b2=b3=0;

        blue= ((b1>> bit) & 0x01) ;
        red= ((b2>> bit) & 0x01)<<1 ;
        green= ((b3>> bit) & 0x01)<<2 ;

        colour = green + red + blue;
        return(colour);
}



Uint8 getbyte_128(Uint8 bank, Uint16 byte_offset, Uint8 byte)
{
        Uint8 red=0, blue=0, green=0,b1,b2,b3;
        Uint8 retbyte = 0;



        //Important for CPM
        byte_offset=byte_offset%0x4000;

        if(show_allbanks==1)
        {
                b1=bank2[0x4000+byte_offset+byte];  //red
                b2=bank2[0x0000+byte_offset+byte]; //blue
                if(show_alt_green==1)
                        b3=bank2[0xc000+byte_offset+byte];  //alt green mirror
                else
                        b3=bank2[0x8000+byte_offset+byte];  //green mirror
        }
        else
                b1=b2=b3=0;

       if(bank == 0)
            return b1;
        else if(bank == 1)
            return b2;
        else if(bank == 2)
            return b3;

        return(b1);
}



unsigned int getword_128(Uint8 bank, Uint16 byte_offset, Uint8 byte)  //note these should really be named wordXXX
{
        unsigned int *bnk2;

      //Important for CPM
        byte_offset=byte_offset%0x4000;

        if(show_allbanks==1)
        {
                switch(bank)
				{
					case 0:
						bnk2 =  (unsigned int *)&bank2[0x4000+byte_offset+byte];  //red
						break;
					case 1:
						bnk2 =  (unsigned int *)&bank2[0x0000+byte_offset+byte]; //blue
						break;
                	case 2:
						if(show_alt_green==1)
                        	bnk2 =  (unsigned int *)&bank2[0xc000+byte_offset+byte];  //alt green mirror
                		else
                        	bnk2 =   (unsigned int *)&bank2[0x8000+byte_offset+byte];  //green mirror
						break;
				}
           		return bnk2[0];
        }
        return 0;
}





void update_keyrate128K()
{
                static  unsigned int new_keyval,looper=0;
                if(bank2[0]!=0) //Check for CPM running, if so dont bother with the keyrate
                {
                        if(emu_speed >2 )       //stop keyrepeat for faster emus
                        {
                                                new_keyval=0x0c00*(emu_speed-1);
                                                bank1[0x6233]=new_keyval % 256;
                                                bank1[0x6234]=new_keyval / 256;
                        }
                        else
                        {
                                                new_keyval=0x0c00;
                                                bank1[0x6233]=new_keyval % 256;
                                                bank1[0x6234]=new_keyval / 256;
                        }
                }
}
