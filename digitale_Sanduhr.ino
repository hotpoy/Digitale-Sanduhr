// Matrikelname: dunh1011
// Datum: 2.6.2020
// Funktion: DIGITALE SANDUHR, schaltet sich jedes Mal bei Dunkelheit ein, eingestellt auf 15 Minuten Timerzeit, Animationen für 3/6/9/12/15 abgelaufene Minuten, nach Ablauf der 15 Minuten schaltet es sich ab


#include "LedControl.h"                // Wird für alles benötigt

int LDR = A0;                          // LDR an Pin A0 
int Helligkeit;                        // Nimmt Werte von LDR an

LedControl lc=LedControl(11,13,10,4);  // Pins: DIN,CLK,CS, wie viele LED-Matrix werden verwendet

unsigned long delayTime=500;           // Pause zwischen jeder Animation

struct MyMillis                        // struct: behinhaltet Aufrufen/Zurücksetzen von millis()
{
  unsigned long Offset = 0;            
  unsigned long get1()                 // Bei Aufruf wird millis() zurückgegeben
  {
    return millis() - Offset;
  }
  void reset()                         // Bei Aufruf wird millis() wieder auf 0 gesetzt
  {
    Offset = millis();
  }
};

MyMillis MM;                           // Wird für Zugriff auf get1()/reset() benötigt

// -------------------------Animation der einzelnen LED7219 zur jeweiligen Timerzeit darstellen------------------------

// -------------------------LED-Einstellungen, wenn es hell ist----------------------------------------------

byte Matrix1Ende[] =
{
   B00000000,  
   B00000000,   
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
};

byte Matrix2Ende[] =
{
   B00000000,  
   B00000000,   
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
};

byte Matrix3Ende[] =
{
   B00000000,  
   B00000000,   
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
};

byte Matrix4Ende[] =
{
   B00000000,  
   B00000000,   
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
   B00000000, 
};

//---------------LED-Einstellungen, wenn es dunkel ist und noch 15 Min übrig sind-------------------------

byte Matrix1Anfang[] =
{
   B11100000,  
   B11100010,   
   B11101111, 
   B11100000, 
   B11101011, 
   B11101101, 
   B11100000, 
   B11100000, 
};

byte Matrix2Anfang[] =
{
  B00000011, 
  B00001111,
  B00111111,
  B11111111,
  B11111111,
  B00111111,
  B00001111,
  B00000011
};

byte Matrix3Anfang1[] =
{
  B11000000, 
  B00110000,
  B00001100,
  B00000011,
  B00000011,
  B00001100,
  B00110000,
  B11000000
};

byte Matrix3Anfang2[] =
{
  B11000000, 
  B00110000,
  B00001100,
  B00000010,
  B00000010,
  B00001100,
  B00110000,
  B11000000
};

byte Matrix3Anfang3[] =
{
  B11000000, 
  B00110000,
  B00001100,
  B00000111,
  B00000111,
  B00001100,
  B00110000,
  B11000000
};

byte Matrix3Anfang4[] =
{
  B11000000, 
  B00110000,
  B00001100,
  B00010011,
  B00010011,
  B00001100,
  B00110000,
  B11000000
};

byte Matrix3Anfang5[] =
{
  B11000000, 
  B00110000,
  B00001100,
  B01000011,
  B01000011,
  B00001100,
  B00110000,
  B11000000
};

byte Matrix4Anfang1[] =
{
  B00000111, 
  B01100100,
  B10010100,
  B01100100,
  B00000100,
  B00000100,
  B00000100,
  B00000111
};

byte Matrix4Anfang2[] =
{
  B00000111, 
  B01100100,
  B10010100,
  B01100101,
  B00000101,
  B00000100,
  B00000100,
  B00000111
};

//---------------LED-Einstellungen, wenn es dunkel ist und noch 12 Min übrig ist-------------------------

byte Matrix1Min12[] =
{
   B11100000,  
   B10100010,   
   B10101111, 
   B10100000, 
   B10101001, 
   B10101101, 
   B10101010, 
   B11100000
};

byte Matrix4Min12a[] =
{
  B00000111, 
  B10010110,
  B10110110,
  B11010110,
  B00000110,
  B00000110,
  B00000110,
  B00000111
};

byte Matrix4Min12b[] =
{
  B00000111, 
  B10010110,
  B10110110,
  B11010111,
  B00000111,
  B00000110,
  B00000110,
  B00000111
};

//---------------LED-Einstellungen, wenn es dunkel ist und noch 9 Min übrig ist-------------------------

byte Matrix1Min9[] =
{
   B11100000,  
   B00101011,   
   B00101011, 
   B00100111, 
   B00100000, 
   B00100000, 
   B00100000, 
   B11100000 
};

byte Matrix2Min9[] =
{
  B00000011, 
  B00001100,
  B00111100,
  B11111100,
  B11111100,
  B00111100,
  B00001100,
  B00000011
};

byte Matrix3Min9a[] =
{
  B11000000, 
  B10110000,
  B10001100,
  B10000011,
  B10000011,
  B10001100,
  B10110000,
  B11000000
};

byte Matrix3Min9b[] =
{
  B11000000, 
  B10110000,
  B10001100,
  B10000010,
  B10000010,
  B10001100,
  B10110000,
  B11000000
};

byte Matrix3Min9c[] =
{
  B11000000, 
  B10110000,
  B10001100,
  B10000111,
  B10000111,
  B10001100,
  B10110000,
  B11000000
};

byte Matrix3Min9d[] =
{
  B11000000, 
  B10110000,
  B10001100,
  B10010011,
  B10010011,
  B10001100,
  B10110000,
  B11000000
};

byte Matrix3Min9e[] =
{
  B11000000, 
  B10110000,
  B10001100,
  B11000011,
  B11000011,
  B10001100,
  B10110000,
  B11000000
};

byte Matrix4Min9[] =
{
  B00000111, 
  B11100111,
  B11010111,
  B11010111,
  B00000111,
  B00000111,
  B00000111,
  B00000111
};

//--------------------LED-Einstellungen, wenn es dunkel ist und noch 6 Min übrig ist-----------------------------------

byte Matrix1Min6[] =
{
   B11100000,  
   B00101110,   
   B00101101, 
   B00101101, 
   B00100000, 
   B00100000, 
   B00100000, 
   B11100000 
};

byte Matrix2Min6[] =
{
  B00000011, 
  B00001100,
  B00110000,
  B11110000,
  B11110000,
  B00110000,
  B00001100,
  B00000011
};

byte Matrix3Min6a[] =
{
  B11000000, 
  B11110000,
  B11101100,
  B11100011,
  B11100011,
  B11101100,
  B11110000,
  B11000000
};

byte Matrix3Min6b[] =
{
  B11000000, 
  B11110000,
  B11101100,
  B11100110,
  B11100110,
  B11101100,
  B11110000,
  B11000000
};

byte Matrix3Min6c[] =
{
  B11000000, 
  B11110000,
  B11101100,
  B11110010,
  B11110010,
  B11101100,
  B11110000,
  B11000000
};

byte Matrix4Min6[] =
{
  B00000111, 
  B10110111,
  B10110111,
  B01110111,
  B00000111,
  B00000111,
  B00000111,
  B00000111
};

//-----------------------LED-Einstellungen, wenn es dunkel ist und noch 3 Min übrig ist-------------------------

byte Matrix1Min3[] =
{
   B11100000,  
   B00101001,   
   B00101011, 
   B00101101, 
   B00100000, 
   B00100000, 
   B00100000, 
   B11100000 
};

byte Matrix2Min3[] =
{
  B00000011, 
  B00001100,
  B00110000,
  B11000000,
  B11000000,
  B00110000,
  B00001100,
  B00000011
};

byte Matrix3Min3a[] =
{
  B11000000, 
  B11110000,
  B11111100,
  B11111011,
  B11111011,
  B11111100,
  B11110000,
  B11000000
};

byte Matrix3Min3b[] =
{
  B11000000, 
  B11110000,
  B11111100,
  B11111110,
  B11111110,
  B11111100,
  B11110000,
  B11000000
};

byte Matrix4Min3[] =
{
  B00100111, 
  B11110111,
  B00000111,
  B10010111,
  B11010111,
  B10100111,
  B00000111,
  B00000111
};

// -------------------LED-Einstellungen, wenn es dunkel ist und die 15 Min abgelaufen sind--------------------------

byte Matrix1Schlafen[] =
{
   B00111000,  
   B00111000,   
   B00111000, 
   B00111000, 
   B00111000, 
   B00000000, 
   B00111000, 
   B00111000, 
};

byte Matrix2Schlafen[] =
{
   B00111000,  
   B00111000,   
   B00111000, 
   B00111000, 
   B00111000, 
   B00000000, 
   B00111000, 
   B00111000, 
};

byte Matrix3Schlafen[] =
{
   B00111000,  
   B00111000,   
   B00111000, 
   B00111000, 
   B00111000, 
   B00000000, 
   B00111000, 
   B00111000,  
};

byte Matrix4Schlafen[] =
{
   B00111000,  
   B00111000,   
   B00111000, 
   B00111000, 
   B00111000, 
   B00000000, 
   B00111000, 
   B00111000,  
};

//----------------------------Grundeinstellungen für die Matrix-----------------------------------

void setup()
{
  lc.shutdown(0,false);           // false für das Deaktivieren des Power-Saving-Modes
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,1);           // Helligkeit der einzelnen Pixel (1 - 15)
  lc.setIntensity(1,1);
  lc.setIntensity(2,1);
  lc.setIntensity(3,1);
  lc.clearDisplay(0);             // Schaltet alle Pixel aus
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

//  -------------Umsetzen der einzelnen LED-Einstellungen in die LED-Matrix---------------------------

// --------------Initialisieren wenn es hell wird------------------------------------------------------

void matrix1Ende()
{
for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,Matrix1Ende[i]); // Sobald die Fkt ein Byte = 1 findet, leuchtet die zum Byte zugehörige Pixel-LED auf 
  }
}

void matrix2Ende()
{
for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,Matrix2Ende[i]);
  }
}

void matrix3Ende()
{
for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Ende[i]);
  }
}

void matrix4Ende()
{
for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Ende[i]);
  }
}

//---------------Initialisieren am Anfang------------------------------------

void matrix1Anfang()
{
for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,Matrix1Anfang[i]);
  }
}

void matrix2Anfang()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,Matrix2Anfang[i]);
  }
}

void matrix3Anfang1()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(2,i,Matrix3Anfang1[i]);
  }
}

void matrix3Anfang2()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Anfang2[i]);
  }
}

void matrix3Anfang3()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Anfang3[i]);
  }
}

void matrix3Anfang4()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Anfang4[i]);
  }
}

void matrix3Anfang5()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Anfang5[i]);
  }
}

void matrix4Anfang1()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Anfang1[i]);
  }
}

void matrix4Anfang2()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Anfang2[i]);
  }
}

// ------------------Initialisieren nach 3 Min----------------------------

void matrix1Min12()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,Matrix1Min12[i]);
  } 
}

void matrix4Min12a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Min12a[i]);
  } 
}

void matrix4Min12b()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Min12b[i]);
  } 
}

// -------------------Initialisieren nach 6 Min------------------------------
void matrix1Min9()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,Matrix1Min9[i]);
  }
}

void matrix2Min9()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,Matrix2Min9[i]);
  }
}

void matrix3Min9a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min9a[i]);
  }
}

void matrix3Min9b()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min9b[i]);
  }
}

void matrix3Min9c()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min9c[i]);
  }
}

void matrix3Min9d()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min9d[i]);
  }
}

void matrix3Min9e()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min9e[i]);
  }
}

void matrix4Min9()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Min9[i]);
  }
}

//-----------------Initialisieren nach 9 Minuten-----------------------

void matrix1Min6()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,Matrix1Min6[i]);
  }
}

void matrix2Min6()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,Matrix2Min6[i]);
  }
}

void matrix3Min6a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min6a[i]);
  }
}

void matrix3Min6b()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min6b[i]);
  }
}

void matrix3Min6c()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min6c[i]);
  }
}

void matrix4Min6()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Min6[i]);
  }
}
//-----------------Initialisieren nach 12 Minuten-----------------------

void matrix1Min3()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,Matrix1Min3[i]);
  }
}

void matrix2Min3()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,Matrix2Min3[i]);
  }
}

void matrix3Min3a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min3a[i]);
  }
}

void matrix3Min3b()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Min3b[i]);
  }
}

void matrix4Min3()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Min3[i]);
  }
}

//-----------------Initialisieren nach 15 Minuten-----------------------

void matrix1Schlafen()
{ 
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,Matrix1Schlafen[i]);
  }
}

void matrix2Schlafen()
{ 
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(1,i,Matrix2Schlafen[i]);
  }
}

void matrix3Schlafen()
{ 
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,Matrix3Schlafen[i]);
  }
}

void matrix4Schlafen()
{ 
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,Matrix4Schlafen[i]);
  }
}

// ------------------Sanduhr-Funktion----------------------------

void loop()
{
  Helligkeit = analogRead(LDR);                    // Helligkeit nimmt Werte zwischen 0 (sehr dunkel) und 4096 (sehr hell) an
 
  if (Helligkeit < 150)                              // Sobald es dunkel wird
  {
    while (MM.get1() < 180053)                        // Solange es keine 12 Minuten sind
    {
       Anfang();
    }
    
   while (MM.get1() > 180053 && MM.get1() < 360053)    // Solange es keine 9 Minuten sind
   {
       Min12();
   }

   while (MM.get1() > 360053 && MM.get1() < 540053)    // Solange es keine 6 Minuten sind
   {
      Min9();
   }

   while(MM.get1() > 540053 && MM.get1() < 720053)     // Solange es keine 3 Minuten sind
   {
     Min6();
   }

   while (MM.get1() > 720053 && MM.get1() < 900053)    // Solange die 15 Minuten noch nicht abgelaufen sind
   {
    Min3();
   }

   while (MM.get1() > 900053 && MM.get1() < 920053)    // Nach Ablauf der 15 Minuten
   {
    Schlafen();
   }

   Ende();                                           //"Ausschalten" der Matrix
  }

  else
  {
    MM.reset();                                     // millis() = 0
    Ende();
  }
}

// ---------------------Ausgabe der LED-Einstellungen auf die LED-Matrix----------------------------------

void Anfang()
{
    matrix1Anfang();
    matrix2Anfang();
    matrix3Anfang1();
    matrix4Anfang1();
    delay(delayTime);

    matrix1Anfang();
    matrix2Anfang();
    matrix3Anfang2();
    matrix4Anfang1();
    delay(delayTime);

    matrix1Anfang();
    matrix2Anfang();
    matrix3Anfang3();
    matrix4Anfang1();
    delay(delayTime);

    matrix1Anfang();
    matrix2Anfang();
    matrix3Anfang4();
    matrix4Anfang1();
    delay(delayTime);

    matrix1Anfang();
    matrix2Anfang();
    matrix3Anfang5();
    matrix4Anfang1();
    delay(delayTime);

    matrix1Anfang();
    matrix2Anfang();
    matrix3Anfang1();
    matrix4Anfang2();
    delay(delayTime);   
}


void Min12()
{
    matrix1Min12();
    matrix2Anfang();
    matrix3Anfang1();
    matrix4Min12a();
    delay(delayTime);

    matrix1Min12();
    matrix2Anfang();
    matrix3Anfang2();
    matrix4Min12a();
    delay(delayTime);

    matrix1Min12();
    matrix2Anfang();
    matrix3Anfang3();
    matrix4Min12a();
    delay(delayTime);

    matrix1Min12();
    matrix2Anfang();
    matrix3Anfang4();
    matrix4Min12a();
    delay(delayTime);

    matrix1Min12();
    matrix2Anfang();
    matrix3Anfang5();
    matrix4Min12a();
    delay(delayTime);

    matrix1Min12();
    matrix2Anfang();
    matrix3Anfang1();
    matrix4Min12b();
    delay(delayTime);
}

void Min9()
{
    matrix1Min9();
    matrix2Min9();
    matrix3Min9a();
    matrix4Min9();
    delay(delayTime);

    matrix1Min9();
    matrix2Min9();
    matrix3Min9b();
    matrix4Min9();
    delay(delayTime);

    matrix1Min9();
    matrix2Min9();
    matrix3Min9c();
    matrix4Min9();
    delay(delayTime);

    matrix1Min9();
    matrix2Min9();
    matrix3Min9d();
    matrix4Min9();
    delay(delayTime);

    matrix1Min9();
    matrix2Min9();
    matrix3Min9e();
    matrix4Min9();
    delay(delayTime);
}

void Min6()
{
  matrix1Min6();
  matrix2Min6();
  matrix3Min6a();
  matrix4Min6();
  delay(delayTime);

  matrix1Min6();
  matrix2Min6();
  matrix3Min6b();
  matrix4Min6();
  delay(delayTime);

  matrix1Min6();
  matrix2Min6();
  matrix3Min6c();
  matrix4Min6();
  delay(delayTime);
}

void Min3()
{
   matrix1Min3();
   matrix2Min3();
   matrix3Min3a();
   matrix4Min3();
   delay(delayTime);

   matrix1Min3();
   matrix2Min3();
   matrix3Min3b();
   matrix4Min3();
   delay(delayTime);
}

void Schlafen()
{
  matrix1Schlafen();
  matrix2Schlafen();
  matrix3Schlafen();
  matrix4Schlafen();
  delay(delayTime);
}

void Ende()
{
   matrix1Ende();
   matrix2Ende();
   matrix3Ende();
   matrix4Ende();
   
}
