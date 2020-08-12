/*
  Displays.h - Library for Managment group of 7 seg displays
  Created by Carlos Nunes, August 9, 2020.
  version: 0.01
  Released into the public domain.
*/
#ifndef Displays_h
#define Displays_h

#define maxDigitsNumber 4
#define freqDisplayMultiplex 2

class led {  
public:
  led(byte);
  led();
  void setAddr(byte);  
  void On();
  void Off();
  boolean getPortAddress();
  boolean getPort();
  void setPort(boolean);
private:
  byte _addr;
  boolean _state;
};

led:: led() {
  _addr=-1;
  _state=false;
}

led:: led (byte port) {
  _addr=port;
  pinMode(port, OUTPUT);
}

void led::setAddr(byte port){
  pinMode(port, OUTPUT);
  _addr=port;
  _state= false;
  digitalWrite(_addr, _state);
  
}

boolean led::getPort() {
  return _state;
}
//void led::inicialize(){
//  _state= false;
  
//}

void led::setPort(boolean value){
  _state=value;
  digitalWrite(_addr, _state);
}
void led::On(){
  _state= true;
  digitalWrite(_addr, true);
}

void led::Off(){
     _state= false;
     digitalWrite(_addr, false);
}

boolean led::getPortAddress(){
  return _addr;
}



// ***************************** Class display7segments


class display7Segments {

public:
  display7Segments(unsigned int);
  display7Segments(unsigned int, byte[], byte[4], byte ); 
  void setDisplayAddresses(byte dAddr[], byte mAddr[4] , byte addrDP); 
  void SetNumber(int value);
  void Show();
  byte size();
  void setDigit(int, int);
  
 
private:
  unsigned int _numDisplays;  
  led _ledDP;
  led  _multiplex[4];
  led *_display;
  int _value;
  int _digSelect;
  unsigned long _delayDisplayMultiplex;
  byte _digits[maxDigitsNumber];
  void identifyDigits(int);
  void setDigitAddress(int , boolean value);
  void showDigitNumber(int);   
  
 
};

display7Segments::display7Segments(unsigned int nDisplays) {
    _numDisplays=nDisplays;
    _value=0;
}

display7Segments::display7Segments(unsigned int nDisplays, byte dAddr[], byte mAddr[4] , byte addrDP) {    

  _numDisplays=nDisplays;
  _value=0;
  _digSelect = 0;
  _delayDisplayMultiplex = 0;
  _ledDP.setAddr(addrDP); 
  _ledDP.setPort(!false);   
    
  for (int i=0; i<4; i++) {
    _multiplex[i].setAddr(mAddr[i]);
  }
  _display = new led[nDisplays];
  for (int i=0; i<nDisplays; i++) {
    _display[i].setAddr(dAddr[i]);
  }
}

void display7Segments:: setDisplayAddresses(byte dAddr[], byte mAddr[4] , byte addrDP) {
    _ledDP.setAddr(addrDP);
    _ledDP.setPort(!false);  
    _digSelect = 0;
     _delayDisplayMultiplex = 0; 
  for (int i=0; i<4; i++) {
    _multiplex[i].setAddr(mAddr[i]);
  }
  _display = new led[_numDisplays];
  for (int i=0; i<_numDisplays; i++) {
    _display[i].setAddr(dAddr[i]);
  }
}


void display7Segments:: identifyDigits(int value){
// transforme number in digits    
      if (value >= 0) { 
        _digits[3] = ((value / 1000) % 10);
        _digits[2] = ((value / 100) % 10);
        _digits[1] = ((value / 10) % 10);
        _digits[0] = value % 10;
      }

}


void display7Segments:: setDigit(int id, int value){
    _digits[id]=value;
}



void display7Segments:: SetNumber(int value){
      _ledDP.setPort(true);
      _value=value;
      
      identifyDigits(_value);  
  
}

void display7Segments:: Show(){            
      if((millis()-_delayDisplayMultiplex) > freqDisplayMultiplex) {          
           
          setDigitAddress(_digSelect, LOW); 
                                   
          _digSelect++;
        
          if (_digSelect >= _numDisplays) 
            _digSelect=0;  
                        
          setDigitAddress(_digSelect, HIGH);
          showDigitNumber(_digits[_digSelect]);                           
          _delayDisplayMultiplex = millis();              
      }
}

void display7Segments:: setDigitAddress(int digitId, boolean value){
  _display[digitId].setPort(value);
  
}


void display7Segments:: showDigitNumber(int id) {  
  for (int n=0;n<4;n++) {
    _multiplex[n].setPort(bitRead(id, n));   
  }
}


byte display7Segments:: size() {
  return _numDisplays;
}













#endif
