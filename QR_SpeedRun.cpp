//Begining Time => 2022/05/03 06:14 PM (yy/mm/dd)

#include <iostream>
#include <Windows.h>

#define rSize 65 //Versin 12 M-12

#define SIZE rSize*rSize

uint8_t* EncodeMsg(uint8_t* Msg, size_t& Length) {

	uint8_t* EncoddedMsg = (uint8_t*)malloc(158);

	if (EncoddedMsg == NULL) {

		::exit(-2);

	}

	memset(EncoddedMsg, 0, 158);

	size_t TempLength = Length;

	if (Length > 153) {

		::exit(-38);

	}

	uint8_t AppendingByte[2] = { 0xec, 0x11 };

	//Some Static Stuff
	EncoddedMsg[0] = 0b1000000;									// Mode 0
	EncoddedMsg[1] = (Length >> 4) & 0xff;						// Length 8 Bits Are Only Taken [Not Safe]

	EncoddedMsg[2] = ((Length & 0xf) << 4) | ((Msg[0] >> 4) & 0xf);

	for (size_t Index = 0; Index < Length - 1; Index++) {

		EncoddedMsg[Index + 3] = ((Msg[Index + 1] >> 4) & 0xf) | ((Msg[Index] & 0xf) << 4);

	}
	
	EncoddedMsg[Length + 2] |= (Msg[Length - 1] & 0xf) << 4;

	for (size_t Index = Length + 3; Index < 158; Index++) {		// Appending Bytes
		
		if (Index & 1) {
			
			EncoddedMsg[Index] = AppendingByte[0];
		
		}
		else {

			EncoddedMsg[Index] = AppendingByte[1];

		}

	}

	return EncoddedMsg;

}

BYTE* FillBlock(uint8_t* EncodedMsg) {

	BYTE Block[11][15];

	size_t Length = 158;										// We can assume the length is 158

	size_t Index = 0;
	size_t limit = 0;

	for (size_t d1 = 0; d1 < 11; d1++) {

		if (d1 < 7) {

			limit = 14;
		
		}
		else {

			limit = 15;

		}

		for (size_t d2 = 0; d2 < limit; d2++) {

			Block[d1][d2] = EncodedMsg[Index];

			Index++;

		}

	}

	BYTE* DataBlock = (BYTE*)malloc(Index);

	if (DataBlock == 0) {

		::exit(-2);

	}

	memset(DataBlock, 0, 158);

	Index = 0;

	for (size_t d1 = 0; d1 < 11; d1++) {

		if (d1 < 7) {

			limit = 14;

		}
		else {

			limit = 15;

		}

		for (size_t d2 = 0; d2 < limit; d2++) {

			DataBlock[Index] = Block[d1][d2];

			Index++;

		}

	}

	return DataBlock;

}

BYTE* GenerateQRArray() {

	BYTE ByteArray[rSize][rSize];


	return (BYTE*)NULL;

}

int main() {

	auto Temp = ("http://anish-poudel-39539.portmap.host:39539/autoprinter-server/htdocs/index.php?UserId=e154d68ab7414c45a39f2eac08202a10810d4bf97649ee9cfe5aab109224b9d8");

	size_t Length = 152;

	uint8_t* TestMsg = (uint8_t*)malloc(Length);

	if (TestMsg == NULL) {

		::exit(-2);

	}

	memset(TestMsg, 0, Length);

	for (size_t Index = 0; Index < Length; Index++) {

		TestMsg[Index] = Temp[Index];

	}

	uint8_t* Msg = EncodeMsg(TestMsg, Length);

#ifdef DEBUG
	for (size_t Index = 0; Index < _msize(Msg); Index++) {

		printf("%02X ", Msg[Index]);

	}
#endif

	FillBlock(Msg);

	free(Msg);

	free(TestMsg);

}