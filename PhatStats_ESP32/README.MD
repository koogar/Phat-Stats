WARNING!!!last successful compile espressif v2.0.5
if your compile fails (analogWriteResolution error) uninstall in the IDE boards manager down to the above version

The Baud rate of HardwareSerialMonitor(get the 9600 Version) and PhatStats must match recommended Baud is 9600



  when using BT you only have to connect the device to Windows, no BT pairing is needed.
  When disconnected, you will need to manualy reconnect in HardwareSerialMonitor by clicking
  on the correct COM port “Standard Serial over Bluetooth link”.

  Note: Once connected, two “Standard Serial over Bluetooth Classic link” will be visible
  one is Send, the other is Receive.
  When you know the correct port for Send you can disable the other in Device Manager
  so it does not to show up in HardwareSerialMonitor. 
  If you select the wrong BT Serial port (downlink) HardwareSerialMontor will be laggy










//-------------------------------- DISCLAIMER -------------------------------------------

  !!!THE WEMOS LOLIN32, NOT LIMITED TO, APPEARS TO HAVE NO "UNDERVOLTAGE PROTECTION"
  OR "OVER DISCHARGE PROTECTION" ON THE CHARGING CIRCUIT!!!

  OTHER BOARDS ARE THE SAME!!! USE A LiPo BATTERY WITH BUILT IN PROTECTION, EVEN THEN,
  BUILT IN PROTECTION IS CONSIDERED A LAST RESORT SAFETY NET OR "BELTS AND BRACERS" APPROACH.

  YOU MAY GET SOME BENEFITS, OVERVOLTAGE,OVERCURRENT AND SHORT CIRCUIT PROTECTION BUT, USUALLY
  THE OVER DISCHARGE PROTECTION CUT OFF VOLTAGE IS AROUND 2.4v WHICH IS WAY TOO LOW FOR THE
  CONTINUED MAINTAINED HEALTH OF THE BATTERY.

  RECOMMENDED OVER DISCHARGE PROTECTION VOLTAGES FOR LiPo's ARE AROUND 2.9 - 3 VOLTS.

  ALTERNATIVELY USE A BATTERY BANK THROUGH THE USB CONNECTOR

  !!!LITHIUM POLYMER PACKS / BATTERIES CAN BE VERY DANGEROUS, WITH A RISK OF FIRE!!!

  If you are going to use a battery or LiPo pack you must take some responsibility, do your research!!!.
  No advice will be given, or implied regarding which you should use etc.

  Use the battery/type in accordance with the manufacturer's recommendations.




