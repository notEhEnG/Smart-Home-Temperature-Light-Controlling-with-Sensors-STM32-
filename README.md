## Smart-Home-Temperature-Light-Controlling-with-Sensors-STM32
Smart Home Temperature &amp; Light Controlling with Sensors with the utilization of STM32, DHT11 and LDR. 

## Method 1: Implementing with STM32Cube IDE

The STM32Cube IDE Software can be downloaded with the following link:
[STM32Cube](https://www.st.com/en/development-tools/stm32cubeide.html). <br>
Make sure that your STM32Cube.exe is added to the System Environment Path. <br>

The ST-Link Utility software can be downloaded with the following link: 
[ST-Link Utility](https://www.st.com/en/development-tools/stsw-link004.html).<br>

After downloading both of them, the setup of STM32Cube IDE can be guided as follows:
[STm32Cube Setup](https://youtu.be/OSVffISU7DQ?si=I9No71ysC6M9cvIb&t=386). <br>
Note that the driver selected is *STM32F411CCU6*, depends on your STM32 Model. <br>

After setting all of it, the main.c file can be found in /Core/Src/main.c file. <br>
The github repository includes the **core files**, which contains the Inc (Include Files) & Src (Source Files). <br>
Please ensure everything in the files are downloaded and been paste to the directory file. <br>
The main.c file is the main executable file to be used in the project. <br>

## Method 2: Implementing with Arduino IDE

The Arduino IDE Software can be downloaded as the following link: 
[Arduino IDE](https://www.arduino.cc/en/software). <br>

After downloading the Arduino IDE Software, click File > Preference, navigate to Additional Board Manager URLs and insert **http://dan.drown.org/stm32duino/package_STM32duino_indexa.json**. <br> 
Next, click Sketch > Include Library > Manage Libraries, and download every STM32 core files. <br> 

After downloading the STM32 Core Files, the DHT11 files can be downloaded in Manage Libraries as well. <br> 

The code files of the Arduino IDE can be found in the Github Repository. 

## Pin Assignment
DHTPIN: PA0 <br>
DHTTYPE: DHT11 // DHTxx, where as xx represents your model. <br>
TEMP_LED_PIN: PB0 <br>
LIGHT_LED_PIN: PB1 <br>
LDR_PIN: PA1 <br>


