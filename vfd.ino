#include <digitalWriteFast.h>

/*
   G8
  ----    
G1|G2|G7
  ----    
G3|  |G6
  ----    
   G4
*/

typedef struct tagBLINK {
  unsigned long tmo;
  int state;
  int seg;
  int pos;
} BLINK;

int G1_pin=2;
int G2_pin=3;
int G3_pin=4;
int G4_pin=18;
int G5_pin=13;
int G6_pin=10;
int G7_pin=11;
int G8_pin=12;
int P1_pin=5;
int P2_pin=6;
int P3_pin=7;
int P4_pin=8;
int P5_pin=9;
int P6_pin=24;
int P7_pin=23;
int P8_pin=22;
int P9_pin=19;

char G1seg    ((char)0x81);
char G2seg    ((char)0x82);
char G3seg    ((char)0x83);
char G4seg    ((char)0x84);
char G5seg    ((char)0x85);
char G6seg    ((char)0x86);
char G7seg    ((char)0x87);
char G8seg    ((char)0x88);

int g_grid_pins[8]={G1_pin,G2_pin,G3_pin,G4_pin,G5_pin,G6_pin,G7_pin,G8_pin};
int g_pos_pins[9]={P1_pin,P2_pin,P3_pin,P4_pin,P5_pin,P6_pin,P7_pin,P8_pin,P9_pin};
char g_char2id[]={'A','H','P','F','.','0','L','E','S','C','U','J','o','r','c','b','d','-','i','h',
                  G1seg,G2seg,G3seg,G4seg,G5seg,G6seg,G7seg,G8seg,'1','2','3','4','5','6','7','8','9',0};
BLINK g_pos_blink[sizeof(g_char2id)/sizeof(g_char2id[0])]={0};
int g_grid_state[][8]={
  {LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,LOW},            //A
  {LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,HIGH},           //H
  {LOW,LOW,LOW,HIGH,HIGH,HIGH,LOW,LOW},           //P
  {LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH,LOW},          //F
  {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH},       //.
  {LOW,HIGH,LOW,LOW,HIGH,LOW,LOW,LOW},            //0
  {LOW,HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH},         //L
  {LOW,LOW,LOW,LOW,HIGH,HIGH,HIGH,LOW},           //E
  {LOW,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW},           //S
  {LOW,HIGH,LOW,LOW,HIGH,HIGH,HIGH,LOW},          //C
  {LOW,HIGH,LOW,LOW,HIGH,LOW,LOW,HIGH},           //U
  {HIGH,HIGH,HIGH,LOW,HIGH,LOW,LOW,HIGH},         //J
  {HIGH,LOW,LOW,LOW,HIGH,LOW,HIGH,HIGH},          //o
  {HIGH,LOW,LOW,HIGH,HIGH,HIGH,HIGH,HIGH},        //r
  {HIGH,LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH},         //c
  {LOW,LOW,LOW,LOW,HIGH,LOW,HIGH,HIGH},           //b
  {HIGH,LOW,LOW,LOW,HIGH,LOW,LOW,HIGH},           //d
  {HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},       //-
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH},       //i
  {LOW,LOW,LOW,HIGH,HIGH,LOW,HIGH,HIGH},          //h
  {LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},       //G1
  {HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},       //G2
  {HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH,HIGH},       //G3
  {HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH},       //G4
  {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH},       //G5
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH},       //G6
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,HIGH},       //G7
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW},       //G8
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,HIGH},        //1
  {HIGH,LOW,LOW,LOW,HIGH,HIGH,LOW,LOW},           //2
  {HIGH,LOW,HIGH,LOW,HIGH,LOW,LOW,LOW},           //3
  {LOW,LOW,HIGH,HIGH,HIGH,LOW,LOW,HIGH},          //4
  {LOW,LOW,HIGH,LOW,HIGH,LOW,HIGH,LOW},           //5
  {LOW,LOW,LOW,LOW,HIGH,LOW,HIGH,LOW},            //6
  {HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW},         //7
  {LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW},             //8
  {LOW,LOW,HIGH,LOW,HIGH,LOW,LOW,LOW}             //9
};

/*******************************************************/
int grid_on(int pin)
{
  digitalWriteFast(pin,LOW);
  return(0);
}
/*******************************************************/
int grid_off(int pin)
{
  digitalWriteFast(pin,HIGH);
  return(0);
}
/*******************************************************/
int pos_on(int pin)
{
  digitalWriteFast(pin,LOW);
  return(0);
}
/*******************************************************/
int pos_off(int pin)
{
  digitalWriteFast(pin,HIGH);
  return(0);
}
/*******************************************************/
int set_A(int pos, int on)
{
  grid_on(G1_pin);
  grid_on(G2_pin);
  grid_on(G3_pin);
  grid_off(G4_pin);
  grid_off(G5_pin);
  grid_on(G6_pin);
  grid_on(G7_pin);
  grid_on(G8_pin);
  if(on == 1) {
    pos_on(g_pos_pins[pos-1]);
  } else {
    pos_off(g_pos_pins[pos-1]);
  }
  return(0);
}
/*******************************************************/
int set_H(int pos, int on)
{
  grid_on(G1_pin);
  grid_on(G2_pin);
  grid_on(G3_pin);
  grid_off(G4_pin);
  grid_off(G5_pin);
  grid_on(G6_pin);
  grid_on(G7_pin);
  grid_off(G8_pin);
  if(on == 1) {
    pos_on(g_pos_pins[pos-1]);
  } else {
    pos_off(g_pos_pins[pos-1]);
  }
  return(0);
}
/*******************************************************/
int set_P(int pos, int on)
{
  grid_on(G1_pin);
  grid_on(G2_pin);
  grid_on(G3_pin);
  grid_off(G4_pin);
  grid_off(G5_pin);
  grid_off(G6_pin);
  grid_on(G7_pin);
  grid_on(G8_pin);
  if(on == 1) {
    pos_on(g_pos_pins[pos-1]);
  } else {
    pos_off(g_pos_pins[pos-1]);
  }
  return(0);
}
/*******************************************************/
int set_1(int pos, int on)
{
  grid_off(G1_pin);
  grid_off(G2_pin);
  grid_off(G3_pin);
  grid_off(G4_pin);
  grid_off(G5_pin);
  grid_on(G6_pin);
  grid_on(G7_pin);
  grid_off(G8_pin);
  if(on == 1) {
    pos_on(g_pos_pins[pos-1]);
  } else {
    pos_off(g_pos_pins[pos-1]);
  }
  return(0);
}
/*******************************************************/
int get_pos(char c)
{
  int n;

  if(c == 0) return(-1);  

  for(n=0;;n++) {
    if(g_char2id[n] == 0) return(-1);
    if(g_char2id[n] == c) return(n);
  }
  
  return(-1);
}
/*******************************************************/
int set_char(char c)
{
  int i,n;

  if(c == 0) return(-1);  

  for(n=0;;n++) {
    if(g_char2id[n] == 0) return(-1);
    if(g_char2id[n] == c) break;
  }
  for(i=0;i < 8;i++) {
    digitalWriteFast(g_grid_pins[i],g_grid_state[n][i]);
  }
  
  return(0);
}
/*******************************************************/
int show_char(char c, int pos)
{
  if((pos < 1) || ((unsigned int)pos > sizeof(g_pos_pins)/sizeof(g_pos_pins[0]))) return(-1);

  pos=pos-1;
  if(set_char(c) != 0) return(-1);  
  pos_on(g_pos_pins[pos]);
  delay(1);
  pos_off(g_pos_pins[pos]);

  return(0);
}
/*******************************************************/
int show_string(char *str, int pos)
{
  char *c;

  for(c=str;*c != '\0';c++) {
    show_char(*c,pos+(c-str));
  }

  return(0);
}
/*******************************************************/
int blinking_char(char c, int pos, unsigned long tmo_on, unsigned long tmo_off)
{
  if((pos < 1) || ((unsigned int)pos > sizeof(g_pos_pins)/sizeof(g_pos_pins[0]))) return(-1);

  pos=pos-1;
  if(g_pos_blink[pos].state == 1) {
    if((millis()-g_pos_blink[pos].tmo) > tmo_on) {
      g_pos_blink[pos].tmo=millis();
      g_pos_blink[pos].state=0;
      pos_off(g_pos_pins[pos]);
    }
  } else {
    if((millis()-g_pos_blink[pos].tmo) > tmo_off) {
      g_pos_blink[pos].tmo=millis();
      g_pos_blink[pos].state=1;
    }
  }
  if(g_pos_blink[pos].state == 1) {
    show_char(c,pos+1);
  }

  return(0);
}
/*******************************************************/
int blinking_string(char *str, int pos, unsigned long tmo_on, unsigned long tmo_off)
{
  char *c;
  
  if(str == NULL) return(-1);
  if(*str == '\0') return(-1);
  if((pos < 1) || ((pos+strlen(str)-1) > sizeof(g_pos_pins)/sizeof(g_pos_pins[0]))) return(-1);

  for(c=str;*c != '\0';c++) {
    blinking_char(*c,pos+(c-str),tmo_on,tmo_off);
  }

  return(0);
}
/*******************************************************/
int running_char(char c, int pos1, int pos2, int start_pos, unsigned long tmo_on, unsigned long tmo_off)
{
  int pos;
  
  if((pos1 < 1) || ((unsigned int)pos1 > sizeof(g_pos_pins)/sizeof(g_pos_pins[0]))) return(-1);
  if((pos2 < 1) || ((unsigned int)pos2 > sizeof(g_pos_pins)/sizeof(g_pos_pins[0]))) return(-1);
  if(pos1 >= pos2) return(-1);

//  pos=pos1-1;
  pos=start_pos-1;
  if(g_pos_blink[pos].state == 1) {
    if((millis()-g_pos_blink[pos].tmo) > tmo_on) {
      g_pos_blink[pos].tmo=millis();
      g_pos_blink[pos].state=0;
      pos_off(g_pos_pins[pos]);
      if(g_pos_blink[pos].pos >= pos2) {
        g_pos_blink[pos].pos=pos1;
      } else {
        if(g_pos_blink[pos].pos < pos1) {
//          g_pos_blink[pos].pos=pos1;
          g_pos_blink[pos].pos=start_pos;
        } else {
          g_pos_blink[pos].pos++;
        }
      }
    }
  } else {
    if((millis()-g_pos_blink[pos].tmo) > tmo_off) {
      g_pos_blink[pos].tmo=millis();
      g_pos_blink[pos].state=1;
    }
  }
  if(g_pos_blink[pos].state == 1) {
    show_char(c,g_pos_blink[pos].pos);
  }

  return(0);
}
/*******************************************************/
int running_string(char *str, int pos1, int pos2, int start_pos, unsigned long tmo_on, unsigned long tmo_off)
{
  char *c;

  if(str == NULL) return(-1);
  if(*str == '\0') return(-1);
  if((start_pos < pos1) || (start_pos > pos2)) return(-1);

  if(g_pos_blink[start_pos+strlen(str)-2].state == 1) {
    if(g_pos_blink[start_pos+strlen(str)-2].pos == pos1) {
      for(c=str;*c != 0;c++) {
        g_pos_blink[start_pos+(c-str)-1].pos=pos1+(c-str);
      }
    }
  }

  for(c=str;*c != 0;c++) {
    running_char(*c,pos1,pos2,start_pos+(c-str),tmo_on,tmo_off);
  }

  return(0);
}
/*******************************************************/
void setup(void)
{
  unsigned int i;
  
  for(i=0;i < sizeof(g_grid_pins)/sizeof(g_grid_pins[0]);i++) {
    pinMode(g_grid_pins[i],OUTPUT);  
    digitalWrite(g_grid_pins[i],HIGH);
  } 

  for(i=0;i < sizeof(g_pos_pins)/sizeof(g_pos_pins[0]);i++) {
    pinMode(g_pos_pins[i],OUTPUT);  
    digitalWrite(g_pos_pins[i],HIGH);
  } 
  Serial.begin(115200);
}
/*******************************************************/
void loop(void)
 {
//   static int p1=1,p2=2;
   static unsigned long tmo=0;
//   static unsigned long l_blink_state=0,l_blink_tmo=0;
char segs1[]={G1seg,G8seg,G7seg,G6seg,G4seg,G3seg};
char segs2[]={G7seg,G8seg,G1seg,G3seg,G4seg,G6seg};
static int segpos=0;
unsigned long sec,tsec;
char sbuf[12],tsbuf[12];

/*
    if((millis()-g_millis) > 1000) {   
      g_millis=millis();
      p1=p1%4+1;
      p2=p1%4+1;
    }
*/    
    
//    p1=3;
//    p2=4;
/*
  if((millis()-l_blink_tmo) > 1000) {
    l_blink_tmo=millis();
    l_blink_state=(l_blink_state+1)%2;
  }
  if(l_blink_state == 1) {
    show_char('A',1);
  }
*/  
//  running_char('8',1,9,1,1000,150);
//  running_char('A',1,5,2,100,10);

  
//  running_string((char*)"Error",1,6,1,600,400);
//  blinking_char('C',2,500,300);
//  blinking_string((char*)"Error",5,600,400);
//  blinking_string((char*)segs,1,600,400);
//  show_char('b',1);
//  show_char('d',9);
//  blink_char('F',5,500,1500);
//  show_char('.',4);
//  show_char(G1seg,4);

//  show_string("123456789",1);

//  show_char('A',1);
//  blinking_string((char*)"Err",7,600,400);
//  show_char('E',7);
//  show_char('r',8);
//  show_char('r',9);


//  running_string((char*)"HELP",2,8,2,300,200);
//  show_char(segs1[segpos],1);
//  show_char(segs2[segpos],9);
//  if((millis()-tmo) > 50) {
//    segpos=(segpos+1)%(sizeof(segs1)/sizeof(segs1[0]));
//    tmo=millis();
//  }
//  Serial.println(segpos);
  if((millis()-tmo) > 50) {
    tmo=millis();
    sec=tmo/1000;
    tsec=(tmo%1000)/100;
    ltoa(sec,sbuf,10);
    ltoa(tsec,tsbuf,10);
  }
  show_string(sbuf,1);
  show_char('.',strlen(sbuf));
  show_string(tsbuf,1+strlen(sbuf));


//    show_char('P',P3_pin);
//    show_char('H',P5_pin);

/*
pos_on(P1_pin);
grid_on(G8_pin);
delay(1000);
grid_off(G8_pin);
delay(1000);
*/    
/*  
    show_A(p1,1);
    delay(15);
    show_A(p1,0);
    show_B(p2,1);
    delay(15);
    show_B(p2,0);
*/    
}
/*******************************************************/
