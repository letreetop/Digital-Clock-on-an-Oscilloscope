#define T0TCR       (*(volatile unsigned int*)0x40004004)
#define T0TC        (*(volatile unsigned int*)0x40004008)
#define T1TCR       (*(volatile unsigned int*)0x40008004)
#define T1TC 		(*(volatile unsigned int*)0x40008008)
#define T2TCR       (*(volatile unsigned int*)0x40090004)
#define T2TC 		(*(volatile unsigned int*)0x40090008)
#define PINSEL1     (*(volatile unsigned int*)0x4002C004)
#define DACCTRL     (*(volatile unsigned int*)0x4008C004)
#define DACR        (*(volatile unsigned int*)0x4008C000)
#define I2C0CONSET 	(*(volatile unsigned int*)0x4001C000)
#define I2C0STAT 	(*(volatile unsigned int*)0x4001C004)
#define I2C0DAT 	(*(volatile unsigned int*)0x4001C008)
#define I2C0SCLH 	(*(volatile unsigned int*)0x4001C010)
#define I2C0SCLL 	(*(volatile unsigned int*)0x4001C014)
#define I2C0CONCLR  (*(volatile unsigned int*)0x4001C018)
#define CCR			(*(volatile unsigned int*)0x40024008)
#define FIO0DIR     (*(volatile unsigned int*)0x2009c000) // defines on port 0 that we can use the DIR function
#define FIO2DIR     (*(volatile unsigned int*)0x2009c040) // defines on port 2 that we can use the DIR function
#define FIO2PIN     (*(volatile unsigned int*)0x2009c054) // defines on port 2 that we can use the PIN function
#define PINMODE4    (*(volatile unsigned int*)0x4002c050) // defines for port 2 (2*2) that we can use pull down resistors
int input[4][4] = {{1,2,3,10},{4,5,6,11},{7,8,9,12},{13,0,14,15}}; // A =10,B =11, C=12,* =13,# =14, D=15
int hourCount =0; //switch hour counter
int minuteCount=0; //switch minute counter
int GPIOAAddress =  0x12;
int OPYCODE =  0b01000000; // 0100 0000
int IODIRA =  0x00;
int count,time, hour, minute, second,k,timeElasped,hour1,minute1,second1,difference, alarmButton;
int Coords0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,2,3,4,5,6,7,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15,15,15,15,15,15,15,15,15,14,13,12,11,10,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1};
int Coords1[] = {3,4,1,2,3,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,7,8,9, 13,14,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,0,0,0,0};
int Coords2[] = {1,2,3,4,5,6,7,8,9,9,9,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,2,3,4,5,6,7,8,9, 15,15,15,15,15,15,15,15,14,13,12,11,10,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1};
int Coords3[] = {1,2,3,4,5,6,7,8,9,9,9,9,9,8,7,6,5,4,3,2,9,9,9,9,9,9,9,9,9,9,9,2,3,4,5,6,7,8,9, 15,15,15,15,15,15,15,15,14,13,12,11,10,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1};
int Coords4[] = {1,1,1,1,1,1,9,9,9,9,9,9,8,7,6,5,4,3,2,9,9,9,9,9,9,9,9,9,9,9,9, 15,14,13,12,11,10,15,14,13,12,11,10,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,1};
int Coords5[] = {1,2,3,4,5,6,7,8,1,1,1,1,1,8,7,6,5,4,3,2,1,1,1,1,9,9,9,9,9,9,9,2,3,4,5,6,7,8,9, 15,15,15,15,15,15,15,15,14,13,12,11,10,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1};
int Coords6[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,2,3,4,5,6,7,8,9,9,9,9,8,7,6,5,4,3,2,9,9,9,9,9,9,9,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15, 15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1};
int Coords7[] = {1,2,3,4,5,6,7,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, 15,15,15,15,15,15,15,15,14,13,12,11,10,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1};
int Coords8[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,2,3,4,5,6,7,8,9,9,9,9,9,8,7,6,5,4,3,2,9,9,9,9,9,9,9,9,9,9,9,2,3,4,5,6,7,8,9, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15, 15,15,15,15,15,15,15,14,13,12,11,10,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2};
int Coords9[] = {1,1,1,1,1,1,1,1,1, 1,2,3,4,5,6,7,8,9,9,9,9,9,8,7,6,5,4,3,2,9,9,9,9,9,9,9,9,9,9,9,2,3,4,5,6,7,8,9, 8,9,10,11,12,13,14,15,15, 15,15,15,15,15,15,15,14,13,12,11,10,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,1,1,1,1,1,1,1,1};
int time1[] = {0,0,0,0,0,0};
int time2[] = {0,0,0,0,0,0};
int gatherTime[] = {0,0,0,0,0,0};
int ooga[6];
void init()
{
	PINSEL1 |= (1<<21); //analogOUT
	PINSEL1 |= (1<<22);
	PINSEL1 |= (1<<24);
	I2C0SCLH = 5;
	I2C0SCLL = 5;
	I2C0CONCLR = (1<<6);
	I2C0CONSET = (1<<6);
	for(int i =0;i<4;i++)
	{
		FIO2DIR &= ~(1<< i);
		PINMODE4 |= (1u << 2*i)|(1u<< (2*i+1));
		FIO2DIR |= (1<<(i+4));
	}
}
void keypad()
{
timer(300000);
while(k<6)
{
	for (int i =4;i< 8;i++)
	{
		for (int j=0;j<4;j++)
		{
			FIO2PIN |= (1<<i);
			if((((FIO2PIN>>i)&1)==1) &&(((FIO2PIN>>j)&1)==1))
			{
				 gatherTime[k] = input[i-4][j];
				 timer(1000000);
				 k++;
			}
			FIO2PIN &= ~(1<<i);			     }
	}
	WriteTimeTotal(gatherTime);
  }
}
int * coords (int number)
{
	switch(number)
	{
		case 0: return  Coords0;
		case 1: return  Coords1;
		case 2: return  Coords2;
		case 3: return  Coords3;
		case 4: return  Coords4;
		case 5: return  Coords5;
		case 6: return  Coords6;
		case 7: return  Coords7;
		case 8: return  Coords8;
		case 9: return  Coords9;
	}
			return 0;
}
int size(int number)
{
	int size[] = {48,27,39,39,31,39,50,24,55,47};
	return size[number];
}

int yCoord(int number)
{
	int yCoord[] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF};
	return yCoord[number];
}
void sendStartCondition()
{
	I2C0CONSET = (1<<3); //sets SI bit to 1
	I2C0CONSET = (1<<5); //sets STA bit to 1
	I2C0CONCLR = (1<<3); //clears SI bit
	while (!((I2C0CONSET >> 3 & 1) == 1)); //waits if SI bit 1
	I2C0CONCLR = (1<<5); //clears STA bit
}
void write(int number)
{
	I2C0DAT  = number;// value in register saved to a variable, save the data read
	I2C0CONCLR = (1<<3); //clears SI bit
	while (!((I2C0CONSET >> 3 & 1) == 1)); //waits if SI bit 1
}
void sendStopCondition()
{
	I2C0CONSET = (1<<4); //sets STO
	I2C0CONCLR = (1<<3); //clears SI bit
	while (!((I2C0CONSET >> 4 & 1) == 1)); //waits if STO bit 1
}
void actOfWriting(int num)
{
	sendStartCondition();
	write(OPYCODE);// opcode
	write(IODIRA);// set output
	write(0);// write nothing
	sendStopCondition();
	timer(10);
	sendStartCondition();
	write(OPYCODE);// opcode
	write(GPIOAAddress);// GPIOA address to write
	write(yCoord(num));// value to write
	sendStopCondition();
}
int timer (int us)
{
	T1TCR |= (1<<0); //sets bit to activate timer
	T1TC = 0; //sets timer to 0 for simplicity
	while(T1TC < us);
}
void timer1()
{
	T0TCR |= (1<<0); //sets bit to activate timer
	T0TC = 0; //sets timer to 0 for simplicity
}
int * timeConversion(int x)
{
	time = T0TC;
	second = time/1000000;
	if (second == 59)
	{
		T0TC = 0;
		minute++;
		if(minute == 59)
		{
			minute = 0;
			hour++;
			if(hour == 23)
				hour = 0;
		}
	}
	if(x == 2)
	{
	timeElasped = T0TC - difference;
	second1 = timeElasped/1000000;
	if(T0TC < difference)
	{
		second1 = second1*(-1);
		second1 = 59-second1;
	}
		if (second1==59)
		{
			T0TC = difference;
			minute1++;
			if(minute1 == 59)
			{
				minute1 = 0;
				hour1++;
				if(hour1 == 23)
					hour1 = 0;
			}
		}
	}

	int timeValues[] = {hour, minute, second};
	int elaspedTimeValues[] = {hour1,minute1,second1};
	for (int i = 0; i < 3; i++)
	{
		time1[i*2] = timeValues[i] / 10;
	    time1[i*2+1] = timeValues[i] % 10;
	    time2[i*2] = elaspedTimeValues[i] / 10;
	    time2[i*2+1] = elaspedTimeValues[i] % 10;
	}
	if(x == 1)
		return  time1;
	if(x == 2 )
		return time2;
	if(x == 3)
		{
			hour1 = 0;
			minute1 = 0;
			T0TC = difference;
			return 0;
		}
}
void writeOscilloscope(int i[],int whatNumber,int position)
{
	int blah1;
	blah1 = size(whatNumber);
	for(int blah = 0; blah < blah1; blah++)
	{
		DACR = (i[blah]*600)+12000*position;
		actOfWriting(i[blah+blah1]);
	}
}
 int WriteTimeTotal(int i[])
{
	for(int j = 0; j<6; j++)
	{
		writeOscilloscope(coords(i[j]),i[j],j);
		timer(100);
	}
}
int main()
{
 	init();
	timer1();
	hour = 12;
	while(1)
	{
		FIO2PIN |= (1<<7);
		FIO2PIN |= (1<<4);
		if((((FIO2PIN>>7)&1)==1) && (((FIO2PIN>>0)&1)==1))
		{
			timer(300000);
			FIO2PIN &= ~(1<<7);
			FIO2PIN &= ~(1<<4);
			keypad();
			hour = gatherTime[0]*10+gatherTime[1];
			minute = gatherTime[2]*10+gatherTime[3];
			T0TC = (gatherTime[4]*10+gatherTime[5])*1000000;
			for(int i = 0; i<6; i++)
				gatherTime[i]=0;
			k=0;
		}
		if((((FIO2PIN>>4)&1)==1) && (((FIO2PIN>>3)&1)==1))
		{
			FIO2PIN &= ~(1<<7);
			FIO2PIN &= ~(1<<4);
			difference = T0TC;
			while(1)
			{
				FIO2PIN |=(1<<5);
				if((((FIO2PIN>>5)&1)==1) && (((FIO2PIN>>3)&1)==1))
				{
					for(int i = 0; i<6; i++)
						ooga[i] = time2[i];
					int hm = 0;
					FIO2PIN |= (1<<6);
					while(hm < 1)
					{
						WriteTimeTotal(ooga);
						if((((FIO2PIN>>6)&1)==1) && (((FIO2PIN>>3)&1)==1))
							hm++;
					}
					FIO2PIN &= ~(1<<6);
					hour1 = ooga[0]*10+ooga[1];
					minute1 = ooga[2]*10+ooga[3];
					difference = T0TC - ((ooga[4]*10+ooga[5]))*1000000;
				}
				else
					WriteTimeTotal(timeConversion(2));
				FIO2PIN &= ~(1<<5);
				FIO2PIN |=(1<<7);
				if((((FIO2PIN>>7)&1)==1) && (((FIO2PIN>>2)&1)==1))
				{
					timeConversion(3);
				}
				FIO2PIN %= ~(1<<7);
				FIO2PIN |= (1<<7);
				if((((FIO2PIN>>7)&1)==1) && (((FIO2PIN>>3)&1)==1))
				{
					minute1 = 0;
					hour1 = 0;
					break;
				}
			}
			FIO2PIN &= ~(1<<4);
			FIO2PIN &= ~(1<<5);
			FIO2PIN &= ~(1<<6);
			FIO2PIN &= ~(1<<7);
			for(int i = 0; i<6; i++)
				ooga[i] = 0;
		}
		WriteTimeTotal(timeConversion(1));
	}
}
