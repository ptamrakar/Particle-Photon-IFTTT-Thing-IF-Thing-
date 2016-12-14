

// This #include statement was automatically added by the Particle IDE.
#include "RCSwitch/RCSwitch.h"

//-----------These values are used for Lights--------------------------------
int Light = A0; 
int analoglightvalue=0; 
int lightThreshold=1000;
//-----------These values are used for Lights--------------------------------

//-------------------These values are used for temperature-------------------
int temp =A1;
int analogtempvalue=0;
int tempthreshold=1000;
//-------------------These values are used for temperature-------------------

//-------------------These values are used for Motion-------------------
int motion =D0;
int analogmotionvalue=0;
int motionthreshold=1; //in Minute
int motiontimer=0;
int lastmotion=0;
//-------------------These values are used for Motion------------------

//-------------------Function used to switch on and off things around house-------------
int Switches(String command);
int switchpin=D3;
RCSwitch switchObj = RCSwitch();
//-------------------Function used to switch on and off things around house-------------


int wait=500; // This is the wait time until particle checks the system again and before sending the email

void setup() 
{
    pinMode(Light,INPUT);      
  
    pinMode(temp,INPUT);
  
    pinMode(motion,INPUT);
   
    pinMode(switchpin, OUTPUT);
    switchObj.enableTransmit(switchpin);
    switchObj.setPulseLength(180);
    
    
    //Expose the Switches function to IFTTT
    Particle.function("Switch", Switches);
}

void loop() {
    
    //-------------------Light Code Starts here--------------------------------------
    analoglightvalue = analogRead(Light);
    Particle.variable("LightVal", &analoglightvalue, INT);
    if (analoglightvalue > lightThreshold)
    {
        Particle.publish( "Light","DO");
    }
    
    //-------------------Light Code Ends here--------------------------------------
    
    
    //-------------------Temperature Code Starts here--------------------------------------
    analogtempvalue = analogRead(temp);
    analogtempvalue = ((((analogtempvalue * 3.2)/4095) - 0.5) * 100)*(9.0/5.0) + 32.0;
    Particle.variable("TempVal", &analogtempvalue, INT);
    if(analogtempvalue >tempthreshold)
    {
        Particle.publish( "Temperature","DO");
    }
    //-------------------Temperature Code Ends here--------------------------------------
    
    
    //--------------------Motion Code Starts Here----------------------------------------
    analogmotionvalue=digitalRead(motion);
    Particle.variable("MotionVal", &analogmotionvalue, INT);
    if (analogmotionvalue==1)
    {
        if (lastmotion==1 && motiontimer!=0){ motiontimer=2*60*motionthreshold;}
        
        if (motiontimer==0)
        {
             Particle.publish( "Motion","1");
             motiontimer=2*60*motionthreshold;
        }
        lastmotion=1;
    }
    else if (lastmotion!=analogmotionvalue)
    {
        if (motiontimer==0)
        {
            Particle.publish( "Motion","0");
            lastmotion=0;
        }
    }
    motiontimer--;
    if(motiontimer<0){motiontimer=0;}
    Particle.publish( "count",String(motiontimer)); //debug code
    //--------------------Motion Code Ends Here----------------------------------------

    delay(wait);
}





// this function automagically shows up in IFTTT
int Switches( String command)
{
  // look for the matching argument "coffee" <-- max of 64 characters long
  if(command == "11")
  { 
    switchObj.send(4265267, 24);
    return 1;
  }
  else if (command == "10")
  {
    switchObj.send(4265276, 24);
    return 1;
  }
  else if (command == "21")
  {
    switchObj.send(4265411, 24); 
    return 1;
  }
  else if (command == "20")
  {
    switchObj.send(4265420, 24);
    return 1;      
  }
  else if (command == "31")
  {
    switchObj.send(4265731, 24);
    return 1;      
  }
  else if (command == "30")
  {
    switchObj.send(4265740, 24);
    return 1;      
  }
  else if (command == "41")
  {
    switchObj.send(4267267, 24);
    return 1;      
  }
  else if (command == "40")
  {
    switchObj.send(4267276, 24);
    return 1;      
  }
  else if (command == "51")
  {
    switchObj.send(4273411, 24);
    return 1;      
  }
  else if (command == "50")
  {
    switchObj.send(4273420, 24);
    return 1;      
  }
  else return -1;
}
