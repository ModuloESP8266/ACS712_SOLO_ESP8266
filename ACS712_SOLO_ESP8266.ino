
const int Relay_2=5;
unsigned long times;

/////////// antirebote /////////////
volatile int contador = 0;   // Somos de lo mas obedientes
int n = contador ;
long T0 = 0 ;  // Variable global para tiempo
/*
Measuring AC Current Using ACS712
*/
const int sensorIn = A0;
double mVperAmp = 37.0;//185.0; // use 100 for 20A****66 for 30A **** 185 for 5A
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
////////////////////////////////
double medida;
const int Btn_Config=0;// boton configuracion
void setup() {
  Serial.begin(115200);
  pinMode(Relay_2,OUTPUT);
  pinMode(Btn_Config, INPUT);
  digitalWrite(Relay_2,false);
attachInterrupt( digitalPinToInterrupt(Btn_Config), Servicio_Btn_Config,FALLING);
}

void loop() {

if (n != contador){
         n = contador ;
         digitalWrite(Relay_2,!digitalRead(Relay_2));
         }
delay(1000);
/*
Voltage = getVPP();
VRMS = (Voltage/2.0) *0.707; 
AmpsRMS = (VRMS * 1000)/mVperAmp;
Serial.print("Amps VPP RMS: ");Serial.println(AmpsRMS);

*/
 times = millis();
Consumo_ACS712() ;

 Serial.println("Demora: "); Serial.println( millis()-times);
}


void Consumo_ACS712() {
 
  float ajuste=-.02;
  float AmpFinalRMS=0;
  float Voltaje;
 
 AmpsRMS=(TrueRMSMuestras()*1000)/mVperAmp;///0.037;
 
 AmpFinalRMS=AmpsRMS+ajuste;
 Serial.print("AmpFinalRMS:");Serial.println(AmpFinalRMS);


}

float TrueRMSMuestras(){
  float result=0,conv=0,Acumulador=0,suma=0;
 int readValue;             //value read from the sensor
 int Count=0;
 uint32_t start_time = millis();

// while((millis()-start_time )< 200){   
 while(Count < 200){  
     delayMicroseconds(960);
     Count++;
     readValue = analogRead(A0);
     conv=(((readValue-513)*1.0)/1024.0);
     Acumulador=Acumulador+sq(conv);  
     }
   suma=Acumulador/Count;
   result=sqrt(suma);
 
   Serial.print("N Muestras:");Serial.println(Count);

   return result;
  }

float getVPP(){
  
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  int contador=0;
  uint32_t tiempo=0;
   uint32_t start_time = millis();
   while((millis()-start_time) < 20) //sample for 1 Sec
   {  
      tiempo =millis();
      delay(1);
       contador++;
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

   
   return result;
 }
 
void Servicio_Btn_Config(){
       if ( millis() > T0  + 250)
          {   contador++ ;
              T0 = millis();
            
             }
    }
