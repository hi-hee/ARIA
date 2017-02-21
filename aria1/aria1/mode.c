#include "mode.h"

void ReadFile(UNCHAR KEY[276][16], UNCHAR IV[276][16], UNCHAR PT[276][16], UNCHAR CT[276][16], const char* argv,const UNCHAR type);
void MmtReadFile(UNCHAR KEY[10][16], UNCHAR IV[10][16], UNCHAR PT[10][161], UNCHAR CT[10][161], const char* FileName, const UNCHAR type);
void WriteFile(const UNCHAR CT[276][16], const UNCHAR TestCT[276][16], const char* FileName);
void MmtWriteFile(const UNCHAR CT[10][161], const UNCHAR TestCT[10][161], const char* FileName);
	/* type
	* 0 = ECB mode
	* 1 = MCT test
	* 2 = other
	* 4 = ECB MCT
	*/

int TESTSET_NUM = 0;


////////*CBC_MODE*///////////////////////////////////////////////////////////////////
void CBCKat(){
	UNCHAR Ptmp[16],CTemp[276][16];
	UNCHAR KEY[276][16], IV[276][16], PT[276][16], CT[276][16];
	char FileName[] = "ARIA128(CBC)KAT.txt";
	char Respond[] = "ARIA128(CBC)KAT_Res.txt";

	TESTSET_NUM = 276;
	ReadFile(KEY, IV, PT, CT, FileName, 2);

	for (int i = 0; i < 276; i++){
		XOR(Ptmp,IV[i], PT[i]);
		ARIAEncryption(CTemp[i], Ptmp, KEY[i]);
	}

	//printf("CBC KAT test result : ");
	//WriteFile(CT, CTemp, Respond);
}

void CBCMct(){

	UNCHAR CTtemp[100][16],CTtemp2[16];
	UNCHAR PtXorTemp[16],PTtemp2[16];
	UNCHAR KEY[100][16], IV[100][16], PT[100][16], CT[100][16];
	char FileName[] = "ARIA128(CBC)MCT.txt";
	char Respond[] = "ARIA128(CBC)MCT_Res.txt";

	TESTSET_NUM = 100;
	ReadFile(KEY, IV, PT, CT, FileName, 1);

	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 1000; j++){
			if (j == 0){
				XOR(PtXorTemp, PT[i], IV[i]);
				ARIAEncryption(CTtemp[i], PtXorTemp, KEY[i]);
				INPUTARR(PtXorTemp, IV[i]);

			} else {
				XOR(PTtemp2, PtXorTemp, CTtemp[i]);
				ARIAEncryption(CTtemp2, PTtemp2, KEY[i]);
				INPUTARR(PtXorTemp, CTtemp[i]);
				INPUTARR(CTtemp[i], CTtemp2);

			}
		}
	}

	//printf("CBC MCT test result : ");
	//WriteFile(CT, CTtemp, Respond);
}

void CBCMmt(){
	UNCHAR KEY[10][16], IV[10][16], PT[10][161], CT[10][161];
	UNCHAR XORTemp[16], CTemp[10][16], PTemp[16],CTResult[10][161];
	char FileName[] = "ARIA128(CBC)MMT.txt";
	char Respond[] = "ARIA128(CBC)MMT_Res.txt";
	
	MmtReadFile(KEY, IV, PT, CT, FileName, 2);

	for (int i = 0; i < 10; i++){

		for (int j = 0; j < i + 1; j++){
			for (int k = 0; k < 16; k++){
				PTemp[k] = PT[i][j * 16 + k];
			}
			if (j == 0){
				XOR(XORTemp, IV[i], PTemp);
				ARIAEncryption(CTemp[j], XORTemp, KEY[i]);
			}
			else {
				XOR(XORTemp, CTemp[j - 1], PTemp);
				ARIAEncryption(CTemp[j], XORTemp, KEY[i]);
			}

			for (int k = 0; k < 16; k++)
				CTResult[i][(16 * j) + k] = CTemp[j][k];
		}
	}
	//printf("CBC MMT test result : ");
	//MmtWriteFile(CT, CTResult, Respond);
}


////////* ECB_MODE *///////////////////////////////////////////////////////////////////
void ECBKat(){
	UNCHAR CTemp[276][16];
	UNCHAR KEY[276][16], IV[276][16], PT[276][16], CT[276][16];
	char FileName[] = "ARIA128(ECB)KAT.txt";
	char Respond[] = "ARIA128(ECB)KAT_Res.txt";

	TESTSET_NUM = 276;
	ReadFile(KEY, IV, PT, CT, FileName, 0);

	for (int i = 0; i < 276; i++)
		ARIAEncryption(CTemp[i], PT[i], KEY[i]);

	//printf("ECB KAT test result : ");
	//WriteFile(CT, CTemp, Respond);

}

void ECBMct(){
	UNCHAR CTemp[100][16], PTemp[16];
	UNCHAR KEY[100][16], IV[100][16], PT[100][16], CT[100][16];
	char FileName[] = "ARIA128(ECB)MCT.txt";
	char Respond[] = "ARIA128(ECB)MCT_Res.txt";

	TESTSET_NUM = 100;
	ReadFile(KEY, IV, PT, CT, FileName, 4);

	for (int i = 0; i < 100; i++){
		INPUTARR(PTemp, PT[i]);
		for (int j = 0; j < 1000; j++){
			ARIAEncryption(CTemp[i],PTemp,KEY[i]);
			INPUTARR(PTemp, CTemp[i]);
		}
	}
	//printf("ECB MCT test result : ");
	//WriteFile(CT, CTemp, Respond);

}

void ECBMmt(){
	UNCHAR KEY[10][16], IV[10][16], PT[10][161], CT[10][161];
	UNCHAR CTemp[10][16], PTemp[16], CTResult[10][161];
	char FileName[] = "ARIA128(ECB)MMT.txt";
	char Respond[] = "ARIA128(ECB)MMT_Res.txt";

	MmtReadFile(KEY, IV, PT, CT, FileName, 0);

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < i + 1; j++){
			for (int k = 0; k < 16; k++)
				PTemp[k] = PT[i][j * 16 + k];
			
			ARIAEncryption(CTemp[j], PTemp, KEY[i]);

			for (int k = 0; k < 16; k++)
				CTResult[i][(16 * j) + k] = CTemp[j][k];
		}
	}
	//printf("ECB MMT test result : ");
	//MmtWriteFile(CT, CTResult, Respond);

}


////////* CTR_MODE *///////////////////////////////////////////////////////////////////
void CTRKat(){
	UNCHAR CTmp[276][16], IVTmp[16];
	UNCHAR KEY[276][16], IV[276][16], PT[276][16], CT[276][16];
	char FileName[] = "ARIA128(CTR)KAT.txt";
	char Respond[] = "ARIA128(CTR)KAT_Res.txt";

	TESTSET_NUM = 276;
	ReadFile(KEY, IV, PT, CT, FileName, 2);

	for (int i = 0; i < 276; i++){
		ARIAEncryption(IVTmp, IV[i], KEY[i]);
		XOR(CTmp[i], PT[i], IVTmp);

		//for (int j = 0; j < 16; j++)
		//	printf("%X", CTmp[j]);
		//printf("\n");
	}
	//printf("CTR KAT test result : ");
	//WriteFile(CT, CTmp, Respond);
}

void CTRMct(){
	UNCHAR CTRtemp[16], CTtemp[100][16], PTtemp[16], XORtemp[16];
	UNCHAR KEY[100][16], CTR[100][16], PT[100][16], CT[100][16];
	char FileName[] = "ARIA128(CTR)MCT.txt";
	char Respond[] = "ARIA128(CTR)MCT_Res.txt";

	TESTSET_NUM = 100;
	ReadFile(KEY, CTR, PT, CT, FileName, 1);

	for (int i = 0; i < 100; i++){
		
		INPUTARR(PTtemp, PT[i]);
		INPUTARR(CTRtemp, CTR[i]);

		for (int j = 0; j < 1000; j++){
			ARIAEncryption(XORtemp, CTRtemp, KEY[i]);
			XOR(CTtemp[i], PTtemp, XORtemp);
			INPUTARR(PTtemp, CTtemp[i]);

			if (CTRtemp[15] == 0xff && CTRtemp[14] == 0xff){
				CTRtemp[14]++;
				CTRtemp[13]++;
			}else if (CTRtemp[15] == 0xff )
				CTRtemp[14]++;
			CTRtemp[15]++;
			
		}

	}

		//printf("count = %d\n", i);t
		//for (int j = 0; j < 16; j++)
		//	printf("%X", CTtemp[j]);
		//printf("\n");
	
	/*printf("CTR MCT test result : ");
	WriteFile(CT, CTtemp, Respond);*/
}

void CTRMmt(){
	UNCHAR KEY[10][16], IV[10][16], PT[10][161], CT[10][161];
	UNCHAR CTRTemp[16], CTemp[10][16], CTResult[10][161], PTemp[16], CTR[16];
	char FileName[] = "ARIA128(CTR)MMT.txt";
	char Respond[] = "ARIA128(CTR)MMT_Res.txt";

	MmtReadFile(KEY, IV, PT, CT, FileName, 2);

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 16; j++)
			CTR[j] = IV[i][j];

		for (int j = 0; j < i + 1; j++){
			for (int k = 0; k < 16; k++)
				PTemp[k] = PT[i][j * 16 + k];
			
			ARIAEncryption(CTRTemp, CTR, KEY[i]);
			XOR(CTemp[j], CTRTemp, PTemp);
			
			for (int k = 0; k < 16; k++)
				CTResult[i][(16*j)+k] = CTemp[j][k];

			CTR[15]++;
		}

	/*	for (int k = 0; k < i + 1; k++)
		for (int j = 0; j < 16; j++)
			printf("%X", CTemp[k][j]);
		printf("\n");*/
	}

	/*printf("CTR MMT test result : ");
	MmtWriteFile(CT, CTResult, Respond);*/

}

////////* File_IO *///////////////////////////////////////////////////////////////////

void ReadFile(UNCHAR KEY[276][16], UNCHAR IV[276][16], UNCHAR PT[276][16], UNCHAR CT[276][16], const char* FileName, const UNCHAR type){
	char name[6];   char equal[2]; char count[4];
	UNCHAR KEYTmp[33], IVTmp[33], PTTmp[33], CTTmp[33];

	FILE *fp;
	fp = fopen(FileName, "r");

	for (int i = 0; i < TESTSET_NUM;i++){

		/* type
		* 0 = ECB mode
		* 1 = MCT test
		* 2 = other
		* 4 = ECB MCT 
		*/

		if ((type%3) == 1)	fscanf(fp, "%s %s %s", name, equal, count);
							fscanf(fp, "%s %s %s", name, equal, KEYTmp);
		if ((type%4) != 0)	fscanf(fp, "%s %s %s", name, equal, IVTmp);
							fscanf(fp, "%s %s %s", name, equal, PTTmp);
							fscanf(fp, "%s %s %s", name, equal, CTTmp);


		for (int j = 0; j < 32; j += 2){

			KEYTmp[j] = CtoH(KEYTmp[j]);
			KEYTmp[j + 1] = CtoH(KEYTmp[j + 1]);
			KEY[i][j / 2] = KEYTmp[j] * 0x10 + KEYTmp[j + 1];

			if ((type % 4) != 0){
				IVTmp[j] = CtoH(IVTmp[j]);
				IVTmp[j + 1] = CtoH(IVTmp[j + 1]);
				IV[i][j / 2] = IVTmp[j] * 0x10 + IVTmp[j + 1];
			}

			PTTmp[j] = CtoH(PTTmp[j]);
			PTTmp[j + 1] = CtoH(PTTmp[j + 1]);
			PT[i][j / 2] = PTTmp[j] * 0x10 + PTTmp[j + 1];

			CTTmp[j] = CtoH(CTTmp[j]);
			CTTmp[j + 1] = CtoH(CTTmp[j + 1]);						
			CT[i][j / 2] = CTTmp[j] * 0x10 + CTTmp[j + 1];

		}

		//for (int j = 0; j < 16; j++)
		//	printf("%X", CT[i][j]);
		//printf("\n");

		

	}

	fclose(fp);
	
}

void MmtReadFile(UNCHAR KEY[10][16], UNCHAR IV[10][16], UNCHAR PT[10][161], UNCHAR CT[10][161], const char* FileName, const UNCHAR type) {
	char name[6];	char equal[2];	
	UNCHAR KEYTmp[33], IVTmp[33], PTTmp[321], CTTmp[321];

	FILE *fp;
	fp = fopen(FileName, "r");
	
	for (int i = 0; i < 10; i++){

								fscanf(fp, "%s %s %s", name, equal, KEYTmp);
		if (type != 0)			fscanf(fp, "%s %s %s", name, equal, IVTmp);
								fscanf(fp, "%s %s %s", name, equal, PTTmp);
								fscanf(fp, "%s %s %s", name, equal, CTTmp);

		for (int j = 0; j < 32; j += 2){
			KEYTmp[j] = CtoH(KEYTmp[j]);
			KEYTmp[j + 1] = CtoH(KEYTmp[j + 1]);
			KEY[i][j / 2] = KEYTmp[j] * 0x10 + KEYTmp[j + 1];

			if (type != 0){
				IVTmp[j] = CtoH(IVTmp[j]);
				IVTmp[j + 1] = CtoH(IVTmp[j + 1]);
				IV[i][j / 2] = IVTmp[j] * 0x10 + IVTmp[j + 1];
			}
		}

		for (int j = 0; j < (32 * (i+1)); j+=2){
			
			PTTmp[j] = CtoH(PTTmp[j]);
			PTTmp[j + 1] = CtoH(PTTmp[j + 1]);
			PT[i][j / 2] = PTTmp[j] * 0x10 + PTTmp[j + 1];

			CTTmp[j] = CtoH(CTTmp[j]);
			CTTmp[j + 1] = CtoH(CTTmp[j + 1]);
			CT[i][j / 2] = CTTmp[j] * 0x10 + CTTmp[j + 1];
			
		}

		//for (int j = 0; j < 16; j++)
		//	printf("%X", PT[i][j]);
		//printf("\n");
	}

	
}

void WriteFile(const UNCHAR CT[276][16], const UNCHAR TestCT[276][16], const char* FileName){
	FILE *fp;
	fp = fopen(FileName, "w");

	int FailCount = 0;	int PassCount = 0;

	for (int i = 0; i < TESTSET_NUM; i++){
		
		fprintf(fp, "CT = ");
		for (int j = 0; j < 16; j++)
			fprintf(fp, "%X ", CT[i][j]);

		fprintf(fp, "\nCTtest = ");
		for (int j = 0; j < 16; j++)
			fprintf(fp, "%X ", TestCT[i][j]);

		if (!strncmp(CT[i], TestCT[i],16)){
			fprintf(fp, "\n------------------------------------pass!\n\n");
			PassCount++;
		}
		else {
			fprintf(fp, "\n------------------------------------fail!\n\n");
			FailCount++;
		}
	}

	printf("pass = %d		fail = %d\n", PassCount, FailCount);
}

void MmtWriteFile(const UNCHAR CT[10][160], const UNCHAR TestCT[10][160], const char* FileName){
	FILE *fp;
	fp = fopen(FileName, "w");

	int FailCount = 0;	int PassCount = 0;

	for (int i = 0; i < 10; i++){
		fprintf(fp, "CT = ");
		for (int j = 0; j < 16 * (i + 1); j++)
			fprintf(fp, "%X", CT[i][j]);

		fprintf(fp, "\nCTtest = ");
		for (int j = 0; j < 16 * (i + 1); j++)
			fprintf(fp, "%X", TestCT[i][j]);

		if (!strncmp(CT[i], TestCT[i], 16)){
			fprintf(fp, "\n------------------------------------pass!\n\n");
			PassCount++;
		}
		else {
			fprintf(fp, "\n------------------------------------fail!\n\n");
			FailCount++;
		}

	}

	printf("pass = %d		fail = %d\n", PassCount, FailCount);
}




