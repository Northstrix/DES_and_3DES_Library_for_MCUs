#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <DES.h>

DES des;

byte key[] = { 
                  0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e, // key A
                  0x92, 0x2f, 0xb5, 0x10, 0xc7, 0x1f, 0x43, 0x6e, // key B
                  0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e, // key C (in this case A)
                };


void printArray(byte output[])
{
  for (int i = 0; i < 8; i++)
  {
    if (output[i] < 0x10)
    {
      Serial.print("0");
    }
    Serial.print(output[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void printArray(byte output[], int len)
{
  for (int i = 0; i < len; i++)
  {
    if (output[i] < 0x10)
    {
      Serial.print("0");
    }
    Serial.print(output[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}


byte *encrypt( byte *dataIn , int len ) {

    unsigned int memsize = ((len/8)+1)*8; // round to the upper 8 byte size
    unsigned int nBlocks = ((len/8)+1);   // Number of blocks. There is at least one block
    unsigned int boffset = 0;             // Byte offset
    
    // WARNING WARNING WARNING WARNING
    byte *bout = (byte *)malloc(memsize); // THIS IS a very bad idea!!!! Just for testing. Allocation should be done OUTSIDE the function.
    
    while ( nBlocks > 0 ) {
        des.tripleEncrypt(&bout[boffset], &dataIn[boffset], key);
        boffset = boffset + 8;
        nBlocks = nBlocks - 1;
    };

    
    return bout;
}


byte *decrypt(byte *dataIn, int len ) {
    unsigned int memsize = ((len/8)+1)*8; // round to the upper 8 byte size
    unsigned int nBlocks = ((len/8)+1);   // Number of blocks. There is always one block
    unsigned int boffset = 0;
    
    // WARNING WARNING WARNING WARNING
    byte *bout = (byte *)malloc(memsize); // THIS IS a very bad idea!!!! Just for testing. Allocation should be done OUTSIDE the function.
    
    while ( nBlocks > 0 ) {
        des.tripleDecrypt(&bout[boffset], &dataIn[boffset], key);
        boffset = boffset + 8;
        nBlocks = nBlocks - 1;
    };
    
    return bout;
    
}


void tdesTest()
{
  byte out[8];
  byte in[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  byte key[] = { 
                  0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e, // key A
                  0x92, 0x2f, 0xb5, 0x10, 0xc7, 0x1f, 0x43, 0x6e, // key B
                  0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e, // key C (in this case A)
                };
  
  Serial.println();
  Serial.println("====== Triple-DES test ======");
  
  //encrypt
  Serial.print("Encrypt...");
  unsigned long time = micros();
  des.tripleEncrypt(out, in, key);
  time = micros() - time;
  Serial.print("done. (");
  Serial.print(time);
  Serial.println(" micros)");
  printArray(out);
  
  //decrypt
  for (int i = 0; i < 8; i++)
  {
    in[i] = out[i];
  }
  Serial.print("Decrypt...");
  time = micros();
  des.tripleDecrypt(out, in, key);
  time = micros() - time;
  Serial.print("done. (");
  Serial.print(time);
  Serial.println(" micros)");
  printArray(out);
}

void desTest()
{
  byte out[8];
  byte in[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  byte key[] = { 0x3b, 0x38, 0x98, 0x37, 0x15, 0x20, 0xf7, 0x5e };
  
  Serial.println();
  Serial.println("========= DES test ==========");
  
  //encrypt
  Serial.print("Encrypt...");
  unsigned long time = micros();
  des.encrypt(out, in, key);
  time = micros() - time;
  Serial.print("done. (");
  Serial.print(time);
  Serial.println(" micros)");
  printArray(out);
  
  //decrypt
  for (int i = 0; i < 8; i++)
  {
    in[i] = out[i];
  }
  Serial.print("Decrypt...");
  time = micros();
  des.decrypt(out, in, key);
  time = micros() - time;
  Serial.print("done. (");
  Serial.print(time);
  Serial.println(" micros)");
  printArray(out);
}

void sysReady() {
    
        char st[] = "This is a long string to be used as an encryption and decryption test.";
        Serial.println("System ready....");

	tdesTest();

	desTest();

    
        Serial.println("------------------------------------------------------------");
        Serial.println("------Encryption test-----------------");
    
        byte *b = encrypt ( (byte *)st, strlen(st) );
       
        printArray( b , strlen(st) );
        
        Serial.println("-------------------------------");
        Serial.println("------Decryption test-----------------");
                
        byte *cb = decrypt( b , strlen(st) );
    
        Serial.println((char *)cb); 
        
}

void init()
{

        system_set_os_print(0);
       
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(false); // Disable debug output to serial
        
        System.onReady(sysReady);
       
}
