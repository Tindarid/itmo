enum { SCALElog=15, SCALE=1<<SCALElog, mSCALE=SCALE-1, hSCALE=SCALE/2, eSCALE=16*SCALE };
enum { N_STATES=32768 };

#include <stdio.h>

#pragma pack(1)

typedef unsigned int   uint;
typedef unsigned short word;
typedef unsigned char  byte;
typedef unsigned long long int qword;

template <typename T1, typename T2> T1 Min( T1 t1, T2 t2 ) { return t1<t2?t1:t2; }
template <typename T1, typename T2> T1 Max( T1 t1, T2 t2 ) { return t1>t2?t1:t2; }

uint flen( FILE* f ) {
  fseek( f, 0, SEEK_END );
  uint len = ftell(f);
  fseek( f, 0, SEEK_SET );
  return len;
}

struct fsm {
  word s[2]; // next state after bits 0,1
  uint pp;

  uint get_number( char*& p, char* q ) {
    int c; uint r=0;
    while( p<q ) { c = *p++; if( (c>='0')&&(c<='9') ) {--p; break; } }
    while( p<q ) { c = *p++; if( (c>='0')&&(c<='9') ) (r*=10)+=c-'0'; else break; }
    return r;
  }

  uint Load( FILE* f ) {
    uint i, f_len = flen(f);
    char* p = new char[f_len]; if( p==0 ) return 1;
    f_len = fread( p, 1,f_len, f );
    char* q = p + f_len, *p0=p;
    for( i=0; i<N_STATES; i++ ) {
      this[i].s[0] = Max(0,Min(N_STATES-1,get_number(p,q)));
      this[i].s[1] = Max(0,Min(N_STATES-1,get_number(p,q)));
      this[i].pp   = Max(1,Min(SCALE-1,get_number(p,q)));
    }
    delete[] p0;
    return 0;
  }

} FSM[N_STATES];

struct Counter {
  word state; 
  uint P() { return FSM[state].pp; }
  void Update( uint bit ) { state = FSM[state].s[bit]; }
};

struct Predictor {
  uint ctx;  // o0 aligned bit context
  Counter p[0x100<<16];   // order2

  void Init() { for( uint i=0; i<sizeof(p)/sizeof(p[0]); i++ ) p[i].state=0; ctx=1<<16; }

  uint P() { return p[ctx].P(); }

  uint byte() { uint c = ctx&0xFF; ctx=(ctx&0xFFFF)|(1<<16); return c; }

  void update( uint bit ) {
    bit = (bit>0);
    p[ctx].Update( bit );   
    (ctx*=2)+=bit;
  }
};

template< int DECODE >
struct Rangecoder {
  enum { NUM=4, sTOP=0x01000000U, Thres=0xFF000000U };

  FILE* f;
  uint range, code, FFNum, Cache; qword lowc; 

  void Init( FILE* _f ) {
    f = _f; range = 0xFFFFFFFF; lowc = 0; FFNum = 0; Cache = -1;
    if( DECODE==1 ) for( uint _=0; _<NUM; _++ ) (code<<=8)+=getc(f); 
  }

  void Quit() { if( DECODE==0 ) for( uint _=0; _<NUM+1; _++ ) ShiftLow();  }

  uint Process( uint freq, uint bit ) { 
    uint rnew = (qword(range)*(freq<<(32-SCALElog)))>>32;
    if( DECODE ) bit = (code>=rnew);
    bit ? range-=rnew, (DECODE ? code-=rnew : lowc+=rnew) : range=rnew;
    while( range<sTOP ) range<<=8, (DECODE ? (code<<=8)+=getc(f) : ShiftLow());
    return bit;
  }

  uint ShiftLow() {
    uint Carry = uint(lowc>>32), low = uint(lowc);
    if( low<Thres || Carry ) {
      if( Cache!=-1 ) putc( Cache+Carry, f );
      for (;FFNum != 0;FFNum--) putc( Carry-1, f );
      Cache = low>>24;
    } else FFNum++;
    return lowc = (low<<8);
  }
};

template< class Predictor, class Rangecoder > 
void proc( Predictor& p, Rangecoder& rc, uint bit=0 ) { p.update( rc.Process( p.P(), bit ) ); }

// coder c|d input_file output_file
int main( int argc, char** argv ) {
  uint i,c,f_len = 0;

  if( argc<5 ) return 1;

  FILE* f = fopen( argv[2], "rb" ); if( f==0 ) return 2;
  FILE* g = fopen( argv[3], "wb" ); if( g==0 ) return 3;
  FILE* h = fopen( argv[4], "rb" ); if( h==0 ) return 4;

  if( FSM[0].Load(h) ) return 5;

  static Predictor P;

  if( argv[1][0]=='c' ) {

    f_len = flen( f );
    fwrite( &f_len, 1,4, g );
    Rangecoder<0> rc; rc.Init(g); P.Init();
    for( i=0; i<f_len; i++ ) {
      c = getc(f); 
      proc(P,rc,c&0x80); proc(P,rc,c&0x40); proc(P,rc,c&0x20); proc(P,rc,c&0x10);
      proc(P,rc,c&0x08); proc(P,rc,c&0x04); proc(P,rc,c&0x02); proc(P,rc,c&0x01); P.byte();
    } 
    rc.Quit();

  } else {

    fread( &f_len, 1,4, f );
    Rangecoder<1> rc; rc.Init(f); P.Init();
    for( i=0; i<f_len; i++ ) {
      proc(P,rc); proc(P,rc); proc(P,rc); proc(P,rc); 
      proc(P,rc); proc(P,rc); proc(P,rc); proc(P,rc);
      putc( P.byte(), g );
    }

  }

  fclose( f );
  fclose( g );

  return 0;
}
