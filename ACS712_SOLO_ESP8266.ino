

/*
Measuring AC Current Using ACS712

const int sensorIn = A0;
float  mVperAmp = 37.0;// 185; // use 100 for 20A Module and 66 for 30A Module
float Voltage = 0;
float VRMS = 0;
float AmpsRMS = 0;
float AmpFinalRMS=0;
float PowRMS=0;
////////////////////////////////
*/


const int Relay_2=5;
/*
Measuring AC Current Using ACS712
*/
const int sensorIn = A0;
double mVperAmp = 37.0;//185.0; // use 100 for 20A****66 for 30A **** 185 for 5A
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
////////////////////////////////
float medida;

void setup() {
  Serial.begin(115200);
  pinMode(Relay_2,OUTPUT);
  digitalWrite(Relay_2,true);

}

void loop() {
//delay(2000);

medir();
/*
Serial.print("VPP: ");
Serial.println(getVPP());

Voltage = getVPP();
VRMS = (Voltage/2.0) *0.707; 
AmpsRMS = (VRMS * 1000)/mVperAmp;*/
/*
Serial.print("Amps RMS: ");Serial.println(AmpsRMS);
Consumo_ACS712() ;
*/
//float hola=Prueba();
//Serial.print("Irms: ");Serial.println(hola/0.037);
}

void medir(){
  delay(0.1);
  medida=((analogRead(A0)- 512)*1.0)/1024.0;
  Serial.println(medida/0.037);
  
  
  }

void Consumo_ACS712() {
 
  float ajuste=0;//-.08;
  float AmpFinalRMS=0;
  float Voltaje;
 
 AmpsRMS=TrueRMSMuestras() * 27.027027027;
 
 AmpFinalRMS=AmpsRMS+ajuste;
 Serial.print(" AmpFinalRMS:");Serial.println(AmpFinalRMS);


}

float Prueba(){

 float result=0,conv=0,Acumulador=0,suma=0;
 int readValue;             //value read from the sensor
 int Count=0;
 uint32_t start_time = millis();
 Serial.print("Start: ");Serial.println(millis()-start_time);
  while( (millis()-start_time )< 20){   
    
     Count++;
     readValue = analogRead(A0)- 510;
 //    Serial.print("readValue:");Serial.println(readValue);
     conv=(readValue*1.0)/1024.0;
   //  Serial.print("conv:");Serial.println(conv);
     Acumulador=Acumulador+sq(conv);  
    /* Serial.print("Acumulador:");Serial.println(Acumulador);
      Serial.print("Count: ");Serial.println(Count);
    */
     }
    Serial.print("Finish: ");Serial.println(millis()-start_time);
   suma=Acumulador/Count;
   Serial.print("suma:");Serial.println(suma);
   result=sqrt(suma);
   Serial.print("result:");Serial.println(result);
   return result;
  
   }
 
float TrueRMSMuestras(){
  float result=0,conv=0,Acumulador=0,suma=0;
 int readValue;             //value read from the sensor
 int Count=0;
 uint32_t start_time = millis();
   
  while((millis()-start_time )< 41){   
     Count++;
     readValue = analogRead(A0);
     conv=readValue*0.000976 -.5;
     Acumulador=Acumulador+sq(conv);  
     }
   suma=Acumulador/Count;
   result=sqrt(suma);
   return result;
  }

float getVPP(){
  
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 500) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 1.0)/1024.0;

    Serial.print(" maxValue:");Serial.println(maxValue);
    Serial.print(" minValue:");Serial.println(minValue);
   return result;
 }



 /*
void Consumo_ACS712() {
 
  float ajuste=0.0;//-.08;
  float Voltaje;

  digitalWrite(Led_Verde,false);
  AmpsRMS=(TrueRMSMuestras()*1000)/mVperAmp;///0.037;
  AmpFinalRMS=AmpsRMS+ajuste;
  
  if(AmpFinalRMS<0.040){// 1 muestra 26.1 mA =>mVperAmp 37mv
    AmpFinalRMS=0;
   
    }
  
  PowRMS=220.0*AmpFinalRMS;
   
  PowRMS_str=String(PowRMS);
  AmpsRMS_str=String(AmpFinalRMS);
  Serial.print("AmpFinalRMS:");Serial.println(AmpFinalRMS);
  Serial.print("PowRMS:");Serial.println(PowRMS);
  digitalWrite(Led_Verde,true);
}

float TrueRMSMuestras(){
  
  float result=0,conv=0,Acumulador=0,suma=0;
  int readValue;             //value read from the sensor
  int Count=0;
  uint32_t start_time = millis();
  // while((millis()-start_time )< 200){ 
  while(Count < 400) 
   {   
       delayMicroseconds(960); 
       //delayMicroseconds(500); 
       Count++;
       readValue = analogRead(A0);
       conv=(((readValue-511)*1.0)/1024.0);
       Acumulador=Acumulador+sq(conv);
      
   }
     suma=Acumulador/Count;
     result=sqrt(suma);
     return result;
  }

*/


 
