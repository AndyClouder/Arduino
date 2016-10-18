#include <SoftwareSerial.h> 
 SoftwareSerial mySerial(3, 2); // RX, TX
  String Shanflag = "000";
  String Redopenflag = "010";
  String Redcloseflag = "001";  
  String Greencloseflag = "101";
  String Greenopenflag = "111";
  String serialString = "";//串口数据缓存字符串
  String receviedsub = "";
  boolean sendFlag = false;//指示是否允许通过串口发送数据
  boolean readCompleted = false;//指示是否完成读取串口数据
void setup() {
   pinMode(13,OUTPUT);
   pinMode(12,OUTPUT);
   digitalWrite(12,HIGH);
   Serial.begin(115200);
   while (!Serial) {;} 
   Serial.println("hardware"); 
   mySerial.begin(115200);
   mySerial.println("software");
   comandoESP("AT+RST");
   comandoESP("AT+CWMODE=1");
   comandoESP("AT+CWJAP=\"WIFICTC\",\"Welcome1\"");
   delay(3000); 
   comandoESP("AT+CIPMUX=1");
   comandoESP("AT+CIPSERVER=1,8888");
   digitalWrite(13,HIGH);
   digitalWrite(12,LOW);
   delay(3000);
   digitalWrite(13,LOW);
}

void loop() {
  serialEvent();
 if(readCompleted)//判断串口是否接收到数据并完成读取
  {
    Serial.print("read value:");
    Serial.println(serialString);//将读取到的信息发送给电脑
//    Serial.println(serialString.substring(10,13));
//    Serial.println(serialString.length());
    int start = serialString.indexOf(":");
    receviedsub =serialString.substring(start+1,start+4);
    const char* recevied = receviedsub.c_str();
    const char* RedOpenFlag = Redopenflag.c_str();
//    Serial.println("recived:");
//    Serial.println(recevied);
//    Serial.println(serialString.substring(10,13).length());
//    Serial.println("flag:");
//    Serial.println(RedOpenFlag);
//    Serial.println(Redopenflag.length());
    
    const char* GreenCloseflag = Greencloseflag.c_str();
    const char* RedCloseflag = Redcloseflag.c_str();
    const char* GreenOpenflag = Greenopenflag.c_str();
    const char* ShanFlag = Shanflag.c_str();
    if(strcmp(recevied,RedOpenFlag)==0) 
    { 
      digitalWrite(13,HIGH);
    }
     else if(strcmp(recevied,RedCloseflag)==0) //当读取到的信息是"serial stop"时，设置发送标志设置为false
    {
      digitalWrite(13,LOW);
    }
     else if(strcmp(recevied,GreenOpenflag)==0) //当读取到的信息是"serial stop"时，设置发送标志设置为false
    {
      digitalWrite(12,HIGH);
    }
    else if(strcmp(recevied,GreenCloseflag)==0) //当读取到的信息是"serial stop"时，设置发送标志设置为false
    {
      digitalWrite(12,LOW);
    }
     else if(strcmp(recevied,ShanFlag)==0) //当读取到的信息是"serial stop"时，设置发送标志设置为false
    {
      digitalWrite(13,HIGH);
      digitalWrite(12,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      delay(1000);
      digitalWrite(13,HIGH);
      digitalWrite(12,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      delay(1000);
      digitalWrite(13,HIGH);
      digitalWrite(12,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
    }
    serialString = "";
    readCompleted = false;
  }   
   if (Serial.available())
   {
      mySerial.write(Serial.read());        
    }  
}

void serialEvent()
{
  while(mySerial.available())
  {
    char inChar = (char)mySerial.read();
    if(inChar != '\n')//以换行符作为读取结束标志
    {
      serialString += inChar;
    }
    else
    {
      readCompleted = true;
    }
  }
}

void comandoESP(String cmd)
{
  mySerial.println(cmd);
  if(mySerial.available())
    Serial.println(mySerial.readStringUntil(14));

  delay(5000); 
}
