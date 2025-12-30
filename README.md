Renerage Stick
==============

An arcade, retro style, wireless bluetooth joystick.

![Renegade Stick](/photos/IMG20251226114752.jpg)

This repository includes all the necessary code, bill of materials, instructions and link to 3D printable files so you can build yourself a Renegade Stick.
The 3D printable files can be found on [printables.com](https://www.printables.com/model/1532850-renegade-stick/edit)

Who is this project it for ?
----------------------------
Retro game enthusiasts, gamers, makers, tinkerers

Where can I use it ?
-------------------
Wherever there is bluetooth HID support. 
Retro emulators such as Retro Pi, Recalbox etc, Mobile Phones, PCs, steam box, modern Game Consoles like playstastion etc

Where can I get it ?
--------------------
This is not sold as a whole, you have to 3D print the parts, source a few electronic and fastener materials  and build it yourself.

What do I need to build it ?
----------------------------
1. Own or have access to a 3D printer
2. Source or purchase some of the required parts like an ESP32 board, a Li-Po battery, microswitches, hook-up wires, screws etc
3. Basic soldering (for hooking up wires)
4. A PC from where you can flash or compile the code for the board
5. Love building things, patience
Read on for instructions

The Story behind Renagade Stick
-------------------------------

The whole project began as an idea for a gift for a good friend of mine, Nikos.
Nikos and I grew up together in the 1980s, during the era when the first computer games truly flourished.
Back then, gaming platforms usually fell into three categories: home computers, game consoles, or arcade coin-op machines. Should I name a few? Think Atari, Amstrad, Commodore, Amiga, early PCs, and more.
We spent endless hours playing side by side—sometimes as opponents, sometimes cooperating—trying to reach the next level or beat the next boss. Games of that era were simple by design. The hero could usually move left and right, maybe up and down, and perform one action. That simplicity is exactly what gave birth to the joystick: a single handle that allowed the player to control the action without being tied to the bulky, uncomfortable keyboards of those early computer systems.
Although not widely known abroad, in Greece—where we both grew up—several companies started producing joysticks inspired by the build quality and ease of use of arcade coin-op machines. You can find examples of these here: [Greek Joysticks](https://binaryvalue.com/index.php/retro-stuff/our-blog/greek-sticks)
The feeling and amusement of playing on those joysticks was unforgetable. 
The feeling of playing with those joysticks—the weight, the click, the responsiveness—was unforgettable.

Unfortunately, Nikos and I now live on different continents. We see each other only once a year, but when we do, we always end up talking about computers and games. After all, we are still active gamers to this day. During our last meeting, we were discussing game emulators and eventually agreed on one thing: playing those games with modern gamepads just didn’t feel right.
The idea didn’t fully sink in until a few days later, when we had to part ways again. I remembered him showing me his collection of retro joysticks—each one with a different cable and connector for a different system.

When I started searching online, I was disappointed to discover that joysticks like those no longer really exist—at least not in the compact form we were used to. Modern arcade controllers are often bulky, overloaded with buttons, and frankly quite ugly. Definitely not my cup of tea.
Being a 3D-printing nerd, I immediately had the urge to create something that could revive—or perhaps emulate—that lost feeling. I bought a couple of bare-bones arcade-style sticks and experimented with different enclosure sizes until it finally felt right in my hands.
And that was it.
Behold the Renegade Stick.

The joystick takes its name from one of our favorite Amstrad games: Target Renegade.
[Target Renegade on Wikipedia](https://en.wikipedia.org/wiki/Target:_Renegade) 
[Target Renegade on Amstrad CPC Youtube longplay](https://www.youtube.com/watch?v=2ePhicu4iZM)

I created this joystick as a gift for Nikos, for all these reasons. I’m sure it will find its place among his Amstrad and retro computing memorabilia—even if it doesn’t strictly belong to that era.

And since I had already gone this far, I thought: why not make it available to anyone who might want to build one themselves?


Bill of Materials
-----------------
I'm not getting any commision nor am I related with any of the below link sources. 
For my build I have sourced most of my parts from a local electronics store [grobotronics.com](https://grobotronics.com/) with some exceptions. Most of my build was from (Link 1)
I tried to find these items and provide you links for other platforms like amazon,temu etc sothem (Link 2 and 3). However I have not tried them. Sorry I couldn't find everything in one place. 
The links are indicative, feel free to source these materials from your own prefered stores. Pay attention however to quantities and exact specifications. 
Again, Link 1 was my source.

| Item                                  | Quantity | Comment | Photo | Link 1 | Link 2 | Link 3 |
| ------------------------------------- | -------- | ------- | ----- | ------ | ------ | ------ |
| M3x3.0 or M3x4.0 Heat set inserts Short Version | 21 | You need the sort version which is either 3mm or 4mm long | ![M3x3.0 Heat Set Inserts](/icons/item1.png) | [CNC kitchen](https://cnckitchen.store/products/heat-set-insert-m3-x-3-short-version-100-pieces) | [grobotronics](https://grobotronics.com/ruthex-threaded-insert-m3-short-pack-of-70.html) | [Ruthex](https://www.ruthex.de/en/collections/gewindeeinsatze/products/ruthex-gewindeeinsatz-m3s-100stuck-rx-m3x4-0-short-messing-gewindebuchsen-fur-3d-druck) |
| Screw M3x8mm DIN965 (Countersunk)	| 10 | Prefer Black one if you print a Black bottom. Alternatively you could use equivallent countersunk scews with a torx or allen head | ![M3x8.0 countersunk screws](/icons/item2.png) |[grobotronics](https://grobotronics.com/ruthex-threaded-insert-m3-short-pack-of-70.html) | [amazon.de](https://www.amazon.de/-/en/AERZETIX-countersunk-stainless-standard-screwdriver/dp/B0BH4FK22Y/ref=sr_1_35?crid=3V01PV2M2VP78&dib=eyJ2IjoiMSJ9.CsZBng3_E2T11dcul8av-1z-pBEpZvajPqZNLiajdHIcTeiVLxAlhqlXyRDqV7XeaoKlOXAPr8HXPhnWQeDrpw2CWqgTDdg36shAzVNwMMZ8bLY7esZFmZ6_KuVPvdeK6C24c9boKW3FKbc3bmLjSr1_r_pfmmWz6LdhBBv0tZb5esUfHN_eWZ3hAtJbSILwYPIWF3B68KeeuJie3RDkBlaqtdapz1_BBdMxPxPEQxa0rijzjqTTC1uE3b2bCM3eb61UNxxPhoRw1jlUce_QmdbZ2_h2JYKh-DvfzCIqeZs.Be98D4p2OqLddvGO_XOS8bSF6iUg7NUAdO8F44GlGxo&dib_tag=se&keywords=DIN%2B965%2BM3x8%2Bcountersunk%2Bblack&qid=1765727788&sprefix=din%2B965%2Bm3x8%2Bcountersunk%2Bblack%2Caps%2C166&sr=8-35&th=1) | [TME](https://www.tme.eu/gr/en/katalog/bolts_100316/?params=1484:1493365;1489:1475694,1493340,1496790;139:1475833,1461181,1459809;822:1475693&queryPhrase=m3x8) |
| Screw M3x8mm DIN912 (Socket Head)	| 11 | You can use any M3 non countersunk as long as it is 8mm screw body long | ![M3x8.0 socket head](/icons/item3.png) | [grobotronics](https://grobotronics.com/bolt-m3-din-912.html?variation_id=11808) | [TME](https://www.tme.eu/gr/en/katalog/bolts_100316/?params=2394:1475854;139:1459809,1475833;1492:1475469&queryPhrase=m3x8) | [amazon.de](https://www.tme.eu/gr/en/katalog/bolts_100316/?params=2394:1475854;139:1459809,1475833;1492:1475469&queryPhrase=m3x8) |
| Microswitch Mini SPDT ON-(ON) - without Lever	| 8 | prefer the no lever version | ![Microswitch mini SPDT](/icons/item4.png) | [grobotronics](https://grobotronics.com/microswitch-mini-spdt-on-on-without-lever.html) | [TME](https://www.tme.eu/gr/en/katalog/?params=725:1453016_switches-features:without-lever&queryPhrase=Microswitch%20Mini%20SPDT) | [amazon.de](https://www.amazon.de/-/en/mxuteuk-KW11-3Z01-Micro-Switch-Button/dp/B07S8VWG9J/ref=sr_1_28?crid=2PYUXZZY9JA8L&dib=eyJ2IjoiMSJ9.Wo5obEsIy8Wm8OpsWaLVVvw7qNLwm43B3QI0Z-DiWPagiHiY6xL37mgll1dof3LGiKqKFcid589IeUYXg0uKgYsrwkkBsnS7Y5yNY5_dehRr2JSwcE5fsEPG7GRNvQuLJJx_uu_sV0aoQFhzPnIEptIsUkod78DMFL_pA_WMABBIEYPrQrCKg2da4_HBI_HtC8Nuh17MHUL9nsteGRpmTB7zZ9Ddtl_TIaJS7JilZvXfCNaxMaUmMIDoa9wDHWxe7-5Tt7ePFKNOabmT_LB61nXzwPutdnRiNmsTVE7oP_I.ob0yYQzTmjzyg9NcaTkVDdUWldLL9ycludrOaNSIUA4&dib_tag=se&keywords=Microswitch%2BMini%2BSPDT%2Bno%2Blever&qid=1765729863&sprefix=microswitch%2Bmini%2Bspdt%2Bno%2Blever%2Caps%2C113&sr=8-28&th=1) |
| Suction cup with M6 screw	| 4 | Optional if you want a firm anchoring on table | ![Suction Cups with M6 screw](/icons/item5.png) | [temu](https://share.temu.com/IOST35h5UgB) | [amazon.de](https://www.amazon.de/-/en/Diameter-Lightweight-Installation-Multipurpose-Resistant/dp/B0DM26HL43/ref=sr_1_4?crid=2QMFJOW9607D2&dib=eyJ2IjoiMSJ9.B51RalKxbBXrApQ-0jUfBjznELpu1fs-eZ8Sms4EcMQKK--gy88UR5FTBh_VA60ux_7xHx5P_wXhgEi7WXOb0vhgvRP1spjlF7GU-CxbIEOiVtce6yt07ir_riXX1qzIfzqaPKrMNh5UeAC1h2T5E0l6FTa2PcWtqlVv3AWsznKSpwp70LpWCqvpvIqkwBqXywHnMHTcxTYu2rbf86e-iTQO2pLsDdAeH0XxDkI959LRYquPtkSt4rv0XZsd8c1RL0edBTgq3FYhIEc_mCicrT9tdZLzBXGovPsncA37Qkg.UymWOad3FRg0tXh6oNPaclX1QHIs89h_OGBDtnRbelo&dib_tag=se&keywords=Suction+cup+with+M6+screw&qid=1765729975&sprefix=suction+cup+with+m6+screw%2Caps%2C116&sr=8-4) |
| Nut M6 DIN934	| 4 | Optional if you choose the suction cups above | ![Nut M6](/icons/item6.png) | | [amazon.de](https://www.amazon.de/-/en/DIN-934-Hexagonal-Nut-Galvanised/dp/B07FF3869P/ref=sr_1_1?crid=1AJB21N4DRO8K&dib=eyJ2IjoiMSJ9.82DYkS3YrdsUj8QR_bibcSKfFCT82N7SmnAxej0mKGFIqCMLuSsvC_cTJWJbPXQyYa0yEKut6hWMewGvPu61uhALdKyvC4BVoQZ1PAeWUaBG6yyPjhg8dsbf6vmSArjxsFlKtxw3Skhp5xJfOncCe6fwoC9WQ_1JVF7h8XD2NkX2AjwnlLXDXITFTHk6m1OoKmSRddWy9lwurqDJygEgoOTgcif0cTXhZYnZF7937iToWQ8E-1IgKhLyeqrNfjOoxFq6HNDrymf0CapnHzQsM7i1s2lt58nps0xuhIW1q2U.dOLhrQAbFQTSoZNQHQJv50R0EwFcGprAOf75gMu53Ks&dib_tag=se&keywords=DIN934%2BM6&qid=1765730707&sprefix=din934%2Bm6%2Caps%2C106&sr=8-1&th=1) | [TME](https://www.tme.eu/gr/en/katalog/?queryPhrase=DIN934%20M6) |
| Arcade Joystick Assembly | 1 | There is no brand for this There are many similar assemblies around in the market, pay attention to the photo to source the exact one. Mind you the mini switches at the bottom. | ![Arcade Joystick Assembly](/icons/item7.png) | [grobotronics](https://grobotronics.com/arcade-joystick-red-handle.html)  | [amazon.de](https://www.amazon.de/-/en/TOPINCN-Joystick-Classic-Competition-Accessories/dp/B0C3ZJZTLH/ref=sr_1_13?crid=30D8YVWAJBBXF&dib=eyJ2IjoiMSJ9.yAb7Y4OwJqBkzEGvO-Lx1CqPZSvzG50PNe-OqhJpXfpb-NGmc802vJZpZymap4rs8_AYd4h7jRfTKh8IU-IWSnxZekvz3FYwBYm7959F0TkZEp7YhhVUcVdV72pLWT_fkJr_C036k-8_a4sPrgihEAS64bp8XUTIKJZ0ZudQo-umebNyS3cjakv9bquy5X1QMHM-902a_rZCOVCBZjpOsQcP0g6QTF1pYPgpn28SSlU.-sB7wg21R40LZtnXChBxCTkSJxKJ4WSvY52lmNLa1Dw&dib_tag=se&keywords=Arcade+Joystick&qid=1765731021&sprefix=arcade+joystick%2Caps%2C131&sr=8-13) | [Alixpress](https://www.aliexpress.com/item/33008035407.html?spm=a2g0o.productlist.main.14.37bbO8wdO8wdhN&algo_pvid=b734923e-5358-4c62-be63-a92783f1661e&algo_exp_id=b734923e-5358-4c62-be63-a92783f1661e-31&pdp_ext_f=%7B%22order%22%3A%225%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%215.94%215.46%21%21%2148.00%2144.16%21%40210391a017657318030786194ea54a%2167115624089%21sea%21GR%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A5f7d80cc%3Bm03_new_user%3A-29895&curPageLogUid=ASvR5trkSFxh&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A33008035407%7C_p_origin_prod%3A) |
| Batt 3.7V 2500mAh	| 1 | You need one with JST PH2.0 connector. Try searching for LiPo 555060 | ![LiPo Batt 3.7V](/icons/item8.png) | [grobotronics](https://grobotronics.com/polymer-lithium-ion-battery-3.7v-2500mah-jst-ph.html) | [amazon.de](https://www.amazon.de/-/en/Battery-575166-Lithium-Polymer-Connection/dp/B0D7VVJ4JR/ref=sr_1_7?crid=37Z7TVYRU3NZB&dib=eyJ2IjoiMSJ9.Gw6IEzcWolSkJM35XT8ptzzhw4OklGI-RrOfaUbY9w_JH6wWrdjigGXDdF_ePbTZLDLtNWZQyYdFU8UY7ifyfnssnswnMfnRfJiutfw1_rG0uZMWU7cXSA6pphk3MW9t4Bz5jXTtQBLpZnmrbJd4OTHqJbdh9pA3GRWmiMgExdoxX_tvnkNngOBRRUN26K898M0dGoprYpAX2vckIUF0Mi1dUdUz20GXJ9srNGdbkX4.pN2J0n1TQPAmCzrKXmipfbUBiwH3I0gU7LUeOksXRvs&dib_tag=se&keywords=Batt%2B3.7V%2B2500mAh&qid=1765732774&sprefix=batt%2B3.7v%2B2500mah%2Caps%2C156&sr=8-7&th=1) | [Alixpress](https://www.aliexpress.com/item/1005002956503167.html?spm=a2g0o.productlist.main.2.10f3RfCdRfCdSJ&algo_pvid=405c36f7-3cf9-43d4-a664-210bcce8e152&algo_exp_id=405c36f7-3cf9-43d4-a664-210bcce8e152-1&pdp_ext_f=%7B%22order%22%3A%228%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%215.18%214.46%21%21%215.93%215.10%21%402103847817657331538142309e1fa1%2112000022952494914%21sea%21GR%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A5f7d80cc%3Bm03_new_user%3A-29895&curPageLogUid=FMS9uT9Gj2lx&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005002956503167%7C_p_origin_prod%3A) |
| Screw Terminal 6P 2.54mm | 4 | You can buy assortment for 2pin-3pin-4pin-5pin-6pin screw terminals but in most cases you’ll be ok with just buying 6pin and laying them down as needed. Make sure they are the 2.54mm pitch pin variant | ![Screw Terminals](/icons/item9.png) | [grobotronics](https://grobotronics.com/screw-terminal-6p-2.54mm.html) |
| Hook-Up Wire 22 to 24 AWG 0.32 to 0.20 mm2 Assortment colors (Stranded) |  | Prefer different colors so to make your life easier identifying which switch to which board pin. Prefer stranded type. Diameter size is a matter of preference here | ![Hook-up Wire](/icons/item10.png) | [grobotronics](https://grobotronics.com/hook-up-wire-22awg-0-32mm2-assortment-stranded-ods7.html) |
| FireBeetle2 ESP32-C6 (DFR1075) | 1 | Select only ONE of these 3 board. All have been tested to work. Prefer ESP32-C6 being cheaper, more modern and future rich. Make sure you buy one of the exact DFR codes. | ![FireBeetle2 ESP32-C6](/icons/item11.png) | [grobotronics](https://grobotronics.com/firebeetle-2-esp32-c6-wi-fi-6-bluetooth-5-solar-powered.html) | [DFrobot](https://www.dfrobot.com/product-2771.html) |
| FireBeetle2 ESP32-S3(N4) (DFR1145) | 1 | Select only ONE of these 3 board. All have been tested to work. Prefer ESP32-C6 being cheaper, more modern and future rich. Make sure you buy one of the exact DFR codes. | ![FireBeetle2 ESP32-S3](/icons/item12.png) |  [grobotronics](https://grobotronics.com/firebeetle-2-esp32-s3-n4.html) | [DFrobot](https://www.dfrobot.com/product-2836.html) |
| FireBeetle2 ESP32-E N16R2 (DFR1139) | 1 | Select only ONE of these 3 board. All have been tested to work. Prefer ESP32-C6 being cheaper, more modern and future rich. Make sure you buy one of the exact DFR codes. | ![FireBeetle2 ESP32-E](/icons/item13.png) | [grobotronics](https://grobotronics.com/firebeetle-2-esp32-c6-wi-fi-6-bluetooth-5-solar-powered.html) | [DFrobot](https://www.dfrobot.com/product-2837.html) |
| Quick Disconnect - Female Bare 2.8mm | 16 | OPTIONAL item Only needed if you don’t wish to solder the microswitch terminals. The 2.8mm version is for microswitches | ![Quick Disconnect - Female Bare 2.8mm](/icons/item14.png) | [grobotronics](https://grobotronics.com/quick-disconnect-female-bare-2.8mm-bag-of-100.html) |
| Quick Disconnect - Female Bare 4.8mm | 8 | OPTIONAL item Only needed if you don’t wish to solder the microswitch terminals. The 4.8mm version is for the joystick assembly | ![Quick Disconnect - Female Bare 4.8mm](/icons/item15.png) | [grobotronics](https://grobotronics.com/quick-disconnect-female-bare-4.8mm-bag-of-100.html) |

Regarding the DFRobot ESP boards, I have successfully tested all 3 different DFRobot boards and have modified the source code so its compatible with all three of them.
If you would like to compile on your own, there is a single sketch. If you wish to flash directly with the .bin file you'll need to pick the correct binary for your board. 
ESP32-C6 (DFR1075) is the only one that supports active battery level monitoring. The other two will only report a dummy 100% battery. However ESP32-C6 is the trickiest to flash although I hear this is fixed in late board or chip revisions. In any case I provide clear instructions how to flash each of them.

# Build Instructions
You can find build instructions with photos at the following file <a href="/docs/assembly/Renegade Stick Assembly Guide.pdf" target="_blank">User Manual (PDF)</a>


# Operating Instructions
Below some short instructions on how to operate your Renegade stick

Charging the Renegade Stick
-----------------------------
To charge the Renegade stick, connect a USB type C cable. A Red LED light next to the USB port will light up showing battery is charging. The Red light will go off when battery is fully charged, you may disconnect the USB type C cable.

Turn the device ON
------------------
A Green light next to the USB connector indicates the device is powered on/active. If the Green LED is OFF, this means the device is powered off/entered deep sleep.

To wake device from deep sleep wimply press and hold the two front buttons (eyes of the ghost) for at least 3 seconds. The Green light on the USB port should start flashing which means the device has powered on.

If device is paired but no buttons/movement is recorded for more than 5 minutes, the device will power off/enter deep sleep.
If device is not paired or does not get paired within 5 minutes, is will power off/enter deep sleep.

Pairing the Renegade Stick
--------------------------
The device will blink a Green LED at a slow rate (1sec) when it is ready to be paired or is currently not paired with a host.
On your host open the wireless bluetooth device settings and do a scan to discover the nearby devices. You should be able to find the Renegade Stick in the list. Simply click on it and it should instantly get paired with your host.
Mind you every host has a different pairing mechanism but you should not require more than selecting the device from the list and selecting to pair with it.
Once paired the Green LED of Renegade stick will start flashing quickly. Whenever the Green LED flashes quickly means an active paired connection to a host.
If the device is paired with a host it will not broadcast its presence anymore to other devices so if you would like to pair it with another host you will have to unpair it first from the active host to get it discoverable again. If the device was paired but the host is out of reach or turned off the Renegade stick will be in pairing mode waiting to get claimed.

Button Mapping
--------------
Once the device is paired it is a good idea to do some button mapping should your game, console or device allows you to.
By default the handle will be discovered as a HAT switch and the buttons are numbered from left to right 1 to 3 and then from the right side to the left 4 to 6 like below

                            /\                      
      BUTT 1                \/                BUTT 4
              BUTT 2        ||        BUTT 5        
              BUTT 3        ||        BUTT 6        

                      SELECT  START                                

The two front buttons from left to right are SELECT and START

On some consoles the default mapping is the following but it may differ on your console.
| Regegade Stick Buttons | PC | Android | PS Mode 1 | PS Mode 2 |
| ---------------------- | -- | ------- | --------- | --------- |
| BUTT 1 | 1 | A | square button | X button |
| BUTT 2 | 2 | B | X button | circle button | 
| BUTT 3 | 3 | C | circle button | X button |
| BUTT 4 | 4 | X | triagle button | square button |
| BUTT 5 | 5 | Y | L1 shoulder | triagle button |
| BUTT 6 | 6 | Z | R1 shoulder | R1 shoulder |


LED indicators
--------------

| USB LED Color | State | Meaning |
| ------------- | ----- | ------- |
| Green | Flashing slow | Not paired |
| Green | Flashing quick | Paired |
| Green | OFF | Gamepad is in sleep mode/battery discharged |
| Red | permanently ON | Battery charging |
| Red | OFF | Batterry charged/ Battery Full |
| Red | Flashing | No battery detected | 




# Liked it ?
If you found some of this information usuful and would like to buy me a coffee you can donate below

[![Donate with PayPal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.me/mach0gr)

or you can just say thank you at

[pmatsakos@gmail.com](mailto:pmatsakos@gmail.com)


