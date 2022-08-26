/*
Triple-DES encrypt and decrypt with key incrementation example for DES_and_3DES_Library_for_MCUs
This code is distributed under the General Public License v3.0
© Copyright Maxim Bortnikov 2022
For more information please visit:
https://github.com/Northstrix/DES_and_3DES_Library_for_MCUs
*/
#include <DES.h>
DES des;

byte TDESkey_backup[16];

byte TDESkey[] = { 
                0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
              }; // Encryption (and decryption) key

void back_TDESkey(){
  for(int i = 0; i < 16; i++){
    TDESkey_backup[i] = TDESkey[i];
  }
}

void rest_TDESkey(){
  for(int i = 0; i < 16; i++){
    TDESkey[i] = TDESkey_backup[i];
  }
}

void incr_TDESkey() { // Key incrementing function
  if (TDESkey[15] == 255) {
    TDESkey[15] = 0;
    if (TDESkey[14] == 255) {
      TDESkey[14] = 0;
      if (TDESkey[13] == 255) {
        TDESkey[13] = 0;
        if (TDESkey[12] == 255) {
          TDESkey[12] = 0;
          if (TDESkey[11] == 255) {
            TDESkey[11] = 0;
            if (TDESkey[10] == 255) {
              TDESkey[10] = 0;
              if (TDESkey[9] == 255) {
                TDESkey[9] = 0;
                if (TDESkey[8] == 255) {
                  TDESkey[8] = 0;
                  if (TDESkey[7] == 255) {
                    TDESkey[7] = 0;
                    if (TDESkey[6] == 255) {
                      TDESkey[6] = 0;
                      if (TDESkey[5] == 255) {
                        TDESkey[5] = 0;
                        if (TDESkey[4] == 255) {
                          TDESkey[4] = 0;
                          if (TDESkey[3] == 255) {
                            TDESkey[3] = 0;
                            if (TDESkey[2] == 255) {
                              TDESkey[2] = 0;
                              if (TDESkey[1] == 255) {
                                TDESkey[1] = 0;
                                if (TDESkey[0] == 255) {
                                  TDESkey[0] = 0;
                                } else {
                                  TDESkey[0]++;
                                }
                              } else {
                                TDESkey[1]++;
                              }
                            } else {
                              TDESkey[2]++;
                            }
                          } else {
                            TDESkey[3]++;
                          }
                        } else {
                          TDESkey[4]++;
                        }
                      } else {
                        TDESkey[5]++;
                      }
                    } else {
                      TDESkey[6]++;
                    }
                  } else {
                    TDESkey[7]++;
                  }
                } else {
                  TDESkey[8]++;
                }
              } else {
                TDESkey[9]++;
              }
            } else {
              TDESkey[10]++;
            }
          } else {
            TDESkey[11]++;
          }
        } else {
          TDESkey[12]++;
        }
      } else {
        TDESkey[13]++;
      }
    } else {
      TDESkey[14]++;
    }
  } else {
    TDESkey[15]++;
  }
}

int getNum(char ch)
{
    int num=0;
    if(ch>='0' && ch<='9')
    {
        num=ch-0x30;
    }
    else
    {
        switch(ch)
        {
            case 'A': case 'a': num=10; break;
            case 'B': case 'b': num=11; break;
            case 'C': case 'c': num=12; break;
            case 'D': case 'd': num=13; break;
            case 'E': case 'e': num=14; break;
            case 'F': case 'f': num=15; break;
            default: num=0;
        }
    }
    return num;
}

void split_by_eight_for_encr(char plntxt[], int k, int str_len){
  byte res[] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 8; i++){
      if(i+k > str_len - 1)
      break;
      res[i] = byte(plntxt[i+k]);
  }
  encr_TDES(res);
}

void encr_TDES(byte inp_for_tdes[]){
  byte out_of_tdes[8];
  des.tripleEncrypt(out_of_tdes, inp_for_tdes, TDESkey);
  for(int i = 0; i<8; i++){
    if(out_of_tdes[i]<16)
    Serial.print("0");
    Serial.print(out_of_tdes[i],HEX);
  }
}

void decr_eight_chars_block(char ct[], int ct_len, int p){
  int br = false;
  byte res[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 16; i+=2){
    if(i+p > ct_len - 1){
      br = true;
      break;
    }
    if (i == 0){
    if(ct[i+p] != 0 && ct[i+p+1] != 0)
    res[i] = 16*getNum(ct[i+p])+getNum(ct[i+p+1]);
    if(ct[i+p] != 0 && ct[i+p+1] == 0)
    res[i] = 16*getNum(ct[i+p]);
    if(ct[i+p] == 0 && ct[i+p+1] != 0)
    res[i] = getNum(ct[i+p+1]);
    if(ct[i+p] == 0 && ct[i+p+1] == 0)
    res[i] = 0;
    }
    else{
    if(ct[i+p] != 0 && ct[i+p+1] != 0)
    res[i/2] = 16*getNum(ct[i+p])+getNum(ct[i+p+1]);
    if(ct[i+p] != 0 && ct[i+p+1] == 0)
    res[i/2] = 16*getNum(ct[i+p]);
    if(ct[i+p] == 0 && ct[i+p+1] != 0)
    res[i/2] = getNum(ct[i+p+1]);
    if(ct[i+p] == 0 && ct[i+p+1] == 0)
    res[i/2] = 0;
    }
  }
    if(br == false){
      byte decr_text[8];
      des.tripleDecrypt(decr_text, res, TDESkey);
      for (int i = 0; i < 8; ++i) {
        Serial.print(char(decr_text[i]));
      }
   }
}

void setup() {
  Serial.begin(115200);
  Serial.println("3DES encrypt & decrypt with key incrementation");
}

void loop() {
  back_TDESkey();
  Serial.println();
  Serial.println("What do you want to do?");
  Serial.println("1.Encrypt string");
  Serial.println("2.Decrypt string");
  while (!Serial.available()) {}
  int x = Serial.parseInt();
  if(x == 1){
    Serial.println("Enter plaintext:");
    String input;
    while (!Serial.available()) {}
    input = Serial.readString();
    Serial.println("Ciphertext:");
    int str_len = input.length() + 1;
    char input_arr[str_len];
    input.toCharArray(input_arr, str_len);
    int p = 0;
    while(str_len > p+1){
      split_by_eight_for_encr(input_arr, p, str_len);
      p+=8;
      incr_TDESkey();
    }
    Serial.println();
    rest_TDESkey();
  }
  if(x == 2){
     String ct;
     Serial.println("Paste ciphertext:");
     while (!Serial.available()) {}
     ct = Serial.readString();
     int ct_len = ct.length() + 1;
     char ct_array[ct_len];
     ct.toCharArray(ct_array, ct_len);
     int ext = 0;
     Serial.println("Plaintext:");
     while( ct_len > ext){
       decr_eight_chars_block(ct_array, ct_len, 0+ext);
       ext+=16;
       incr_TDESkey();
     }
     Serial.println();
     rest_TDESkey();
   }
}
