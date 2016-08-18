#include <Wire.h>

#include <lp55231.h>

static const int32_t enable_pin = 15; // Apparently active high?
static const int32_t trigger_pin = 14; // low if unused
static const int32_t interrupt_pin = 16;


static uint32_t next;
//static bool     ledon;

static lp55231 ledChip(0x32);

static const uint16_t program[] = 
{
  0x0000,
  0x0001,
  0x0002,
  0x0003,
  0x0004,
  0x0005,
  0x0006,
  0x0007,
  0x0008,
  0x0009,
  0x000a,
  0x000b,
  0x000c,
  0x000d,
  0x000e,
  0x000f,
  0x0010,
  0x0011,
  0x0012,
  0x0013,
  0x0014,
  0x0015,
  0x0016,
  0x0017,
  0x0018,
  0x0019,
  0x001a,
  0x001b,
  0x001c,
  0x001d,
  0x001e,
  0x001f,
  0x0020,
  0x0021,
  0x0022,
  0x0023,
  0x0024,
  0x0025,
  0x0026,
  0x0027,
  0x0028,
  0x0029,
  0x002a,
  0x002b,
  0x002c,
  0x002d,
  0x002e,
  0x002f,
  0x0030,
  0x0031,
  0x0032,
  0x0033,
  0x0034,
  0x0035,
  0x0036,
  0x0037,
  0x0038,
  0x0039,
  0x003a,
  0x003b,
  0x003c,
  0x003d,
  0x003e,
  0x003f,
  0x0040,
  0x0041,
  0x0042,
  0x0043,
  0x0044,
  0x0045,
  0x0046,
  0x0047,
  0x0048,
  0x0049,
  0x004a,
  0x004b,
  0x004c,
  0x004d,
  0x004e,
  0x004f,
  0x0050,
  0x0051,
  0x0052,
  0x0053,
  0x0054,
  0x0055,
  0x0056,
  0x0057,
  0x0058,
  0x0059,
  0x005a,
  0x005b,
  0x005c,
  0x005d,
  0x005e,
  0x005f
};


void setup()
{
  Serial.begin(9600);
  
  delay(5000);
  Serial.println("### Setup entry");
  
  pinMode(enable_pin, OUTPUT);
  digitalWrite(enable_pin, LOW);
  digitalWrite(enable_pin, HIGH);

  ledChip.init();
  ledChip.reset();
  ledChip.enable();

  delay(1000);

  for(uint8_t i = 0; i < 9; i++)
  {
    ledChip.setLogBrightness(i);
    ledChip.setDriveCurrent(i, 111);
  }


#if 1
  Serial.println(sizeof(program)/2);
  if(ledChip.loadProgram(program, (sizeof(program)/2)))
  {
    Serial.println("Program loaded?");

    if(ledChip.verifyProgram(program, (sizeof(program)/2)))
    {
      Serial.println("program verifies");
    }
    // else: lib will print message...
  }
  else
  {
    Serial.println("Program dodn't load?");
  }
#endif

  next = millis() + 3000;

  Serial.println("### Setup complete");
  
}



void loop()
{
  int32_t result;
  int8_t  val;
  static uint32_t count = 0;

  if(millis() >= next)
  {
    next += 10000;
    count++;
    
    Serial.print("# ");
    Serial.println(count);

  }
}


