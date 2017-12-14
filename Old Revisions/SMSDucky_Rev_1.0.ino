//
// SMSDucky Revision 1.0
// Date code: 121217
// Originally Created by MK-V
// 
// Copyright (C) 2017 MK-V, Cheetah Pixie
// MK-V#0505 and CheetahPixie#4257 on Discord
//
// This program is free software: you can redistribut it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have recieved a copy of the GNU General Public License
// along with this prgram. If not, see <http://www.gnu.org/licenses/>.
//
#include <Keyboard.h>
#include <GSM.h>
#define PINNUMBER ""
GSM gsmAccess;
GSM_SMS sms;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
  ;
  }
  boolean notConnected = true;
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY){
      notConnected = false;
    } else {
      delay(1000);
    }
  }
}
void loop() {
  String message;
  if (sms.available()) {
    while(message = sms.read()){
      int firstSpace = message.indexOf(" ");
      if(firstSpace = -1){
        exit;  
      }  
      else if(message.substring(0,firstSpace) == "STRING"){
        for(int i=firstSpace+1;i<message.length();i++) Keyboard.write(message[i]);
      }
      else if(message.substring(0,firstSpace) == "DELAY"){
        int delaytime = message.substring(0,firstSpace +1).toInt();
        delay(delaytime);
      }
      else if(message.substring(0,firstSpace) == "DEFAULTDELAY") int defaultDelay = message.substring(firstSpace +1).toInt();
      else if(message.substring(0,firstSpace) == "DEFAULT_DELAY") int defaultDelay = message.substring(firstSpace +1).toInt();
      else if(message.substring(0,firstSpace) == "REM'"){} //does nothing
      else if(message.substring(0,firstSpace) == "GUI") Keyboard.write(KEY_LEFT_GUI);
    }
  }
}  
