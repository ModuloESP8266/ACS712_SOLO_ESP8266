
const int Relay_2=5;
/*
Measuring AC Current Using ACS712
*/
const int sensorIn = A0;
int mVperAmp = 37;//185; // use 100 for 20A****66 for 30A **** 185 for 5A
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
////////////////////////////////

void setup() {
  Serial.begin(115200);
  pinMode(Relay_2,OUTPUT);
  digitalWrite(Relay_2,true);

}

void loop() {
delay(2000);
Consumo_ACS712() ;
//Serial.print("VPP: ");
// Serial.println(getVPP());
/*
Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS-0.04);
 Serial.println(" Amps RMS");
*/
}



void Consumo_ACS712() {
 
  float ajuste=0;//-.08;
  float AmpFinalRMS=0;
  float Voltaje;
 
 AmpsRMS=(TrueRMSMuestras() * 1000)/mVperAmp;
 
 AmpFinalRMS=AmpsRMS+ajuste;
// Serial.print(" AmpFinalRMS:");Serial.println(AmpFinalRMS);


}



float TrueRMSMuestras(){
  float result=0,conv=0,Acumulador=0,suma=0;
  int readValue;             //value read from the sensor
  int Count=0;
  uint32_t start_time = millis();
  
  while((millis()-start_time) < 40) 
   {   
       Count++;
       readValue = analogRead(A0);
       conv=(readValue*1.0)/1024.0;
        //Serial.print("conv:");
        Serial.println(conv);
       Acumulador=Acumulador+sq(conv);
    
   }
     suma=Acumulador/Count;
   /*  Serial.print("Acumulador:");Serial.println(Acumulador);
     Serial.print("Count:");Serial.println(Count);
     Serial.print("suma:");Serial.println(suma);*/
     result=sqrt(suma);
     return result;
     
    }

float getVPP(){
  
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 40) //sample for 1 Sec
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
