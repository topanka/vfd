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
  int pos;
} BLINK;

int G1_pin=2;
int G2_pin=3;
int G3_pin=4;
int G4_pin=19;
int G5_pin=18;
int G6_pin=10;
int G7_pin=11;
int G8_pin=12;
int P1_pin=5;
int P2_pin=6;
int P3_pin=7;
int P4_pin=8;
int P5_pin=9;

int g_grid_pins[8]={G1_pin,G2_pin,G3_pin,G4_pin,G5_pin,G6_pin,G7_pin,G8_pin};
int g_pos_pins[5]={P1_pin,P2_pin,P3_pin,P4_pin,P5_pin};
BLINK g_pos_blink[5]={0};
int g_char2id[6]={'A','H','P','F','.',0};
int g_grid_state[5][8]={
  {LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,LOW},
  {LOW,LOW,LOW,HIGH,HIGH,LOW,LOW,HIGH},
  {LOW,LOW,LOW,HIGH,HIGH,HIGH,LOW,LOW},
  {LOW,LOW,LOW,HIGH,HIGH,HIGH,HIGH,LOW},
  {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH}
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
  set_char(c);  
  pos_on(g_pos_pins[pos]);
  delay(3);
  pos_off(g_pos_pins[pos]);

  return(0);
}
/*******************************************************/
int blink_char(char c, int pos, unsigned long tmo_on, unsigned long tmo_off)
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
  int rp=0;
  char *c;

  if(str == NULL) return(-1);

  if(g_pos_blink[start_pos-1].state == 1) {
    if(g_pos_blink[start_pos+strlen(str)-1].pos >= ((unsigned int)pos1 > sizeof(g_pos_pins)/sizeof(g_pos_pins[0]))) {
      rp=1;
    }
  }

  for(c=str;*c != 0;c++) {
    if(rp == 1) {
        g_pos_blink[start_pos+strlen(str)-1].pos=pos1+(c-str);
    }
    running_char(*c,pos1,pos2,start_pos+(c-str),tmo_on,tmo_off);
  }

  return(0);
}
/*******************************************************/
void setup(void)
{
  // put your setup code here, to run once:
  pinMode(G1_pin,OUTPUT);
  pinMode(G2_pin,OUTPUT);
  pinMode(G3_pin,OUTPUT);
  pinMode(G4_pin,OUTPUT);
  pinMode(G5_pin,OUTPUT);
  pinMode(G6_pin,OUTPUT);
  pinMode(G7_pin,OUTPUT);
  pinMode(G8_pin,OUTPUT);
  
  pinMode(P1_pin,OUTPUT);
  pinMode(P2_pin,OUTPUT);
  pinMode(P3_pin,OUTPUT);
  pinMode(P4_pin,OUTPUT);
  pinMode(P5_pin,OUTPUT);
  
  digitalWrite(G1_pin,HIGH);
  digitalWrite(G2_pin,HIGH);
  digitalWrite(G3_pin,HIGH);
  digitalWrite(G4_pin,HIGH);
  digitalWrite(G5_pin,HIGH);
  digitalWrite(G6_pin,HIGH);
  digitalWrite(G7_pin,HIGH);
  digitalWrite(G8_pin,HIGH);

  digitalWrite(P1_pin,HIGH);
  digitalWrite(P2_pin,HIGH);
  digitalWrite(P3_pin,HIGH);
  digitalWrite(P4_pin,HIGH);
  digitalWrite(P5_pin,HIGH);
}
/*******************************************************/
void loop(void)
 {
//   static int p1=1,p2=2;
//   static unsigned long g_millis=0;
//   static unsigned long l_blink_state=0,l_blink_tmo=0;

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
//  running_char('F',1,5,1,100,10);
//  running_char('A',1,5,2,100,10);

  
  blink_char('A',2,1000,250);
  show_char('A',1);
  show_char('P',3);
  blink_char('F',5,500,1500);
  show_char('.',4);
  

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
