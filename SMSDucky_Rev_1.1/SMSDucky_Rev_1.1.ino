//
// SMSDucky Revision 1.1
// Date code: 141217
// Originally Created by MK-V
// Commented, cleaned and verified by Cheetah Pixie
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
#include <Keyboard.h> // Keyboard library
#include <GSM.h> // GSM library
#define PINNUMBER "" // Pin in case SIM is locked goes in quotes
GSM gsmAccess; // Initializes the gsmAccess subroutine of the GSM library
GSM_SMS sms; // Initializes the sms subroutine of the SMS subset of the GSM library (for simplicity)
int delayTime; // Defines delayTime; used for extra delay time (adds to defaultDelay)
int defaultDelay = 0; // Defines defaultDelay; used for default delay configuration
void setup() { // Every Arduino does this once, go figure
  Serial.begin(9600);
  boolean notConnected = true; // Defines the lack of a connection
  while (notConnected) { // While not connected, try accessing the network with pin number defined above
    if (gsmAccess.begin(PINNUMBER) == GSM_READY){ // If it has connected and reports itself as ready, do the following
      notConnected = false; // Defines the presence of a connection
    } else { // If connection fails, do the following
      delay(1000); // 1 second delay before retrying
    }
  }
}
void loop() { // Main Arduino loop
  String message; // Required definition; gives error otherwise during compile
  if (sms.available()) { // If it can do SMS, let's
    while(message = sms.read()){ // Parses messages
      int trailingSpace = message.indexOf(" "); // Space after text; renamed from firstSpace to trailingSpace for clarity
      delay(defaultDelay); // Default delay between commands
      if(trailingSpace = -1){ // sms.read will return this value if there is no more data
        sms.flush(); // Deletes the SMS after reading
      }
      else if(message.substring(0,trailingSpace) == "STRING"){ // Duckyscript string
        for( // Splits command from input data
          // "i" renamed to msgLength for clarity
          int msgLength=trailingSpace+1; // Defines the integer variable used for message length
          msgLength<message.length(); // Reads the length of the message and inserts it into msgLength
          msgLength++ // Adds the space between command and data, presumably to cut it away
        )
        Keyboard.write(message[msgLength]); // Cuts the command and writes the remainder of the SMS message
      }
      else if(message.substring(0,trailingSpace) == "DELAY"){ // Duckyscript delay
        delayTime = message.substring(0,trailingSpace +1).toInt(); // Reads and inserts the delay time from an SMS
        delay(delayTime); // Wait time defined by delayTime
      }
      else if(message.substring(0,trailingSpace) == "DEFAULTDELAY"){ // Duckyscript default delay; without underscore for shortness
        defaultDelay = message.substring(trailingSpace +1).toInt(); // Reads an inserts the default delay time from an SMS
      }
      else if(message.substring(0,trailingSpace) == "REM'"){} // Duckyscript remark
      else if(message.substring(0,trailingSpace) == "GUI"){ // Super key press
        Keyboard.write(KEY_LEFT_GUI); // Left Super, probably; needs testing
      }
    }
  }
  // Unimplemented commands here
}
