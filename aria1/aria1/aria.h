#ifndef ARIA_H

#define ARIA_H
#define UNCHAR unsigned __int8
#define INTE64 unsigned __int64

#define XOR(output,input1,input2) for(int x = 0; x<16; x++ ){ output[x] = input1[x] ^ input2[x]; }
#define INPUTARR(output,input) for(int x = 0; x<16; x++){ output[x] = input[x];}
#define POW2(output,index) for(int x= index; x>0; x--){ output *= 2; }


void SL2(UNCHAR output[16], const UNCHAR input[16]);
void Diffusion(UNCHAR output[16], const UNCHAR input[16]);
void SHIFT(UNCHAR output[16], const UNCHAR input[16], const UNCHAR direction, const int num);

void FE(UNCHAR output[16], const UNCHAR input[16], const UNCHAR key[16]);
void FO(UNCHAR output[16], const UNCHAR input[16], const UNCHAR key[16]);

void KeySchedule(UNCHAR Roundkey[13][16], const UNCHAR key[16]);

void ARIAEncryption(UNCHAR C[16], const UNCHAR P[16], const UNCHAR key[16]);
void ARIADecryption(UNCHAR P[16], const UNCHAR C[16], const UNCHAR key[16]);

#endif


//��ũ�� �ٽ� ¥��
//XOR ����