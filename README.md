Renegade Stick
==============

A DIY arcade-style, retro, wireless Bluetooth joystick.

![Renegade Stick](/photos/renegade-stick.jpg)

This repository includes all the necessary code, bill of materials, instructions, and links to 3D printable files so you can build yourself a Renegade Stick.
The 3D printable files can be found on [printables.com](https://www.printables.com/model/1532850-renegade-stick)

<br>

Disclaimer
-------
All 3D-printed hardware part files are licensed under [Open Community License (OCL)](https://github.com/OpenCommunityLicence/OpenCommunityLicence) and are available on [printables.com](https://www.printables.com/model/1532850-renegade-stick)<br>
The software code is licensed under the [GPL-3.0 License](LICENSE)<br>
Part of the code is based on the [ESP32-BLE-Gamepad library by lemmingDev](https://github.com/lemmingDev) distributed under the [MIT license](https://github.com/lemmingDev/ESP32-BLE-Gamepad/blob/master/license.txt)<br>
The above project is based on the [ESP32](http://esp32.net) chip and specifically a Firebeetle Board from [DFRobot](https://www.dfrobot.com/topic-302.html)
This project is solely for instructional and entertainment purposes. <br>
The item as a complete unit or the 3D-printed parts it consists of are not sold and may not be sold without written permission from author. <br>
Please be careful, especially with Li-Po batteries—they can be dangerous if mishandled. Take your time and stay safe!

<br>

## Table of Contents

- [Who Is This Project For?](#who-is-this-project-for-)
- [Where Can I Use It?](#where-can-i-use-it-)
- [Where Can I Get It?](#where-can-i-get-it-)
- [What Do I Need to Build It?](#what-do-i-need-to-build-it-)
- [Specifications](#specifications)
- [The Story Behind Renegade Stick](#the-story-behind-renegade-stick)
- [Bill of Materials](#bill-of-materials)
- [Assembly Instructions](#assembly-instructions)
- [Operating Instructions](#operating-instructions)
  - [Charging the Renegade Stick](#charging-the-renegade-stick)
  - [Turn the Device On](#turn-the-device-on)
  - [Pairing the Renegade Stick](#pairing-the-renegade-stick)
  - [Button Mapping](#button-mapping)
  - [Mode of Operation / Combo Keys](#modes-of-operation--combo-keys)
  - [LED Indicators](#led-indicators)
- [Testing the Device](#testing-the-device)
- [Flashing the Renegade Stick](#flashing-the-renegade-stick)
- [Liked It?](#liked-it-)

<br>

Who is this project for ?
----------------------------
Retro game enthusiasts, gamers, makers, tinkerers

Where can I use it ?
-------------------
Wherever Bluetooth HID support is available.
Retro emulators such as RetroPie, Recalbox etc, Mobile Phones, PCs, Steam box, modern Game Consoles like PlayStation etc

Where can I get it ?
--------------------
This is not sold as a whole, you have to 3D print the parts, source a few electronic components and fasteners and build it yourself.

What do I need to build it ?
----------------------------
1. Own or have access to a 3D printer
2. Source or purchase some of the required parts like an ESP32 board, a Li-Po battery, microswitches, hook-up wires, screws etc
3. Basic soldering (for hooking up wires)
4. A PC from where you can flash or compile the code for the board
5. Love building things, patience
Read on for instructions

<br>

Specifications
--------------

Dual-axis joystick 
10 buttons  
Bluetooth HID gamepad device  
Rechargeable Battery  
Auto Power-off (5 minutes inactivity)  
Switchable mode (DPAD - Axis)
Switchable hand side (Right/Left hand side user - buttons can flip to other side)
Pairing/Mode indication (Green LED)  
Battery Charging (Red LED)  
Active battery state reporting (FireBeetle2 ESP32-C6 board only)
Serial Number reporting (so more than one device can get paired on one host)
Ambidextrous design - Use the side you prefer 

<br>

The Story Behind Renegade Stick
-------------------------------

The whole project began as an idea for a gift for a good friend of mine, Nikos.
Nikos and I grew up together in the 1980s, during the era when the first computer games truly flourished.
Back then, gaming platforms usually fell into three categories: home computers, game consoles, or arcade coin-op machines. Should I name a few? Think Atari, Amstrad, Commodore, Amiga, early PCs, and more.
We spent endless hours playing side by side—sometimes as opponents, sometimes cooperating—trying to reach the next level or beat the next boss. Games of that era were simple by design. The hero could usually move left and right, maybe up and down, and perform one action. That simplicity is exactly what gave birth to the joystick: a single handle that allowed the player to control the action without being tied to the bulky, uncomfortable keyboards of those early computer systems.
Although not widely known abroad, in Greece—where we both grew up—several companies started producing joysticks inspired by the build quality and ease of use of arcade coin-op machines. You can find examples of these here: [Greek Joysticks](https://binaryvalue.com/index.php/retro-stuff/our-blog/greek-sticks)
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

<br>

Bill of Materials
-----------------
I'm not getting any commission nor am I affiliated with any of the below link sources. 
For my build I have sourced most of my parts from a local electronics store [grobotronics.com](https://grobotronics.com/) with some exceptions. Most of my build was from (Link 1)
I tried to find these items and provide you links for other platforms like Amazon, Temu etc (Link 2 and 3) however, I have not tried these links out so double-check or do your own research.
The links are only indicative, feel free to source these materials from your own preferred stores. Pay attention to quantities and exact specifications. 


| Item                                  | Quantity | Comment | Photo | Link 1 | Link 2 | Link 3 |
| ------------------------------------- | -------- | ------- | ----- | ------ | ------ | ------ |
| M3x3.0 or M3x4.0 Heat set inserts Short Version | 21 | You need the short version which is either 3mm or 4mm long | ![M3x3.0 Heat Set Inserts](/icons/item1.png) | [CNC kitchen](https://cnckitchen.store/products/heat-set-insert-m3-x-3-short-version-100-pieces) | [grobotronics](https://grobotronics.com/ruthex-threaded-insert-m3-short-pack-of-70.html) | [Ruthex](https://www.ruthex.de/en/collections/gewindeeinsatze/products/ruthex-gewindeeinsatz-m3s-100stuck-rx-m3x4-0-short-messing-gewindebuchsen-fur-3d-druck) |
| Screw M3x8mm DIN965 (Countersunk)	| 10 | Prefer Black one if you print a Black bottom. Alternatively you could use equivalent countersunk screws with a torx or allen head | ![M3x8.0 countersunk screws](/icons/item2.png) |[grobotronics](https://grobotronics.com/bolts-m3-din965-black-100pcs.html?variation_id=19122) | [amazon.de](https://www.amazon.de/-/en/AERZETIX-countersunk-stainless-standard-screwdriver/dp/B0BH4FK22Y/ref=sr_1_35?crid=3V01PV2M2VP78&dib=eyJ2IjoiMSJ9.CsZBng3_E2T11dcul8av-1z-pBEpZvajPqZNLiajdHIcTeiVLxAlhqlXyRDqV7XeaoKlOXAPr8HXPhnWQeDrpw2CWqgTDdg36shAzVNwMMZ8bLY7esZFmZ6_KuVPvdeK6C24c9boKW3FKbc3bmLjSr1_r_pfmmWz6LdhBBv0tZb5esUfHN_eWZ3hAtJbSILwYPIWF3B68KeeuJie3RDkBlaqtdapz1_BBdMxPxPEQxa0rijzjqTTC1uE3b2bCM3eb61UNxxPhoRw1jlUce_QmdbZ2_h2JYKh-DvfzCIqeZs.Be98D4p2OqLddvGO_XOS8bSF6iUg7NUAdO8F44GlGxo&dib_tag=se&keywords=DIN%2B965%2BM3x8%2Bcountersunk%2Bblack&qid=1765727788&sprefix=din%2B965%2Bm3x8%2Bcountersunk%2Bblack%2Caps%2C166&sr=8-35&th=1) | [TME](https://www.tme.eu/gr/en/katalog/bolts_100316/?params=1484:1493365;1489:1475694,1493340,1496790;139:1475833,1461181,1459809;822:1475693&queryPhrase=m3x8) |
| Screw M3x8mm DIN912 (Socket Head)	| 11 | You can use any M3 non countersunk as long as it is 8mm screw body long | ![M3x8.0 socket head](/icons/item3.png) | [grobotronics](https://grobotronics.com/bolt-m3-din-912.html?variation_id=11808) | [TME](https://www.tme.eu/gr/en/katalog/bolts_100316/?params=2394:1475854;139:1459809,1475833;1492:1475469&queryPhrase=m3x8) | [amazon.de](https://www.amazon.de/-/en/meinschraubenversand-Cylindrical-Partial-Cylinder-Stainless/dp/B0BNJWLFQ4/ref=sr_1_17?crid=2F6W4FNVNG20O&dib=eyJ2IjoiMSJ9.SCUBKeg5X7e-T2e2X6v28dQLSEy1cDl0q9Qb3QL3m0kpYeqCU1Flj5GMcP0egy7zmBGHBbQMVR8zYLLK7ZQ9IFQOtgr5FZzgFSyZCKzYmuIwgFHjihEMl9wOZZPP3U16SefZso9gZFuRX7xTZXGPRTagWrX1b0LJOq-mp3WB5qXzKr-W3WedljjMb66qTpBfhMfjeuqwTSZ4AH1-Ovm9DR-jll7lUdZRGidPfp3n061xgYNZjy-gc-66vbUPfiXUVV4HsTEQI99J-9ROe9HB8iqLSl8MLq65xlIqPU8kWFw.aG6S51yLn34pOKE9HjvofylBTO3azhJJN4NnVjej2q4&dib_tag=se&keywords=din%2B912%2Bm3x8&qid=1767187425&sprefix=din912%2Bm3x8%2Caps%2C168&sr=8-17&th=1) |
| Microswitch Mini SPDT ON-(ON) - without Lever	| 10 | prefer the no lever version | ![Microswitch mini SPDT](/icons/item4.png) | [grobotronics](https://grobotronics.com/microswitch-mini-spdt-on-on-without-lever.html) | [TME](https://www.tme.eu/gr/en/katalog/?params=725:1453016_switches-features:without-lever&queryPhrase=Microswitch%20Mini%20SPDT) | [amazon.de](https://www.amazon.de/-/en/mxuteuk-KW11-3Z01-Micro-Switch-Button/dp/B07S8VWG9J/ref=sr_1_28?crid=2PYUXZZY9JA8L&dib=eyJ2IjoiMSJ9.Wo5obEsIy8Wm8OpsWaLVVvw7qNLwm43B3QI0Z-DiWPagiHiY6xL37mgll1dof3LGiKqKFcid589IeUYXg0uKgYsrwkkBsnS7Y5yNY5_dehRr2JSwcE5fsEPG7GRNvQuLJJx_uu_sV0aoQFhzPnIEptIsUkod78DMFL_pA_WMABBIEYPrQrCKg2da4_HBI_HtC8Nuh17MHUL9nsteGRpmTB7zZ9Ddtl_TIaJS7JilZvXfCNaxMaUmMIDoa9wDHWxe7-5Tt7ePFKNOabmT_LB61nXzwPutdnRiNmsTVE7oP_I.ob0yYQzTmjzyg9NcaTkVDdUWldLL9ycludrOaNSIUA4&dib_tag=se&keywords=Microswitch%2BMini%2BSPDT%2Bno%2Blever&qid=1765729863&sprefix=microswitch%2Bmini%2Bspdt%2Bno%2Blever%2Caps%2C113&sr=8-28&th=1) |
| Suction cup with M6 screw	| 4 | Optional if you want a firm anchoring on table | ![Suction Cups with M6 screw](/icons/item5.png) | [temu](https://share.temu.com/zLP1plqt4lB) | [amazon.de](https://www.amazon.de/-/en/Diameter-Lightweight-Installation-Multipurpose-Resistant/dp/B0DM26HL43/ref=sr_1_4?crid=2QMFJOW9607D2&dib=eyJ2IjoiMSJ9.B51RalKxbBXrApQ-0jUfBjznELpu1fs-eZ8Sms4EcMQKK--gy88UR5FTBh_VA60ux_7xHx5P_wXhgEi7WXOb0vhgvRP1spjlF7GU-CxbIEOiVtce6yt07ir_riXX1qzIfzqaPKrMNh5UeAC1h2T5E0l6FTa2PcWtqlVv3AWsznKSpwp70LpWCqvpvIqkwBqXywHnMHTcxTYu2rbf86e-iTQO2pLsDdAeH0XxDkI959LRYquPtkSt4rv0XZsd8c1RL0edBTgq3FYhIEc_mCicrT9tdZLzBXGovPsncA37Qkg.UymWOad3FRg0tXh6oNPaclX1QHIs89h_OGBDtnRbelo&dib_tag=se&keywords=Suction+cup+with+M6+screw&qid=1765729975&sprefix=suction+cup+with+m6+screw%2Caps%2C116&sr=8-4) |
| Nut M6 DIN934	| 4 | Optional if you choose the suction cups above | ![Nut M6](/icons/item6.png) | | [amazon.de](https://www.amazon.de/-/en/DIN-934-Hexagonal-Nut-Galvanised/dp/B07FF3869P/ref=sr_1_1?crid=1AJB21N4DRO8K&dib=eyJ2IjoiMSJ9.82DYkS3YrdsUj8QR_bibcSKfFCT82N7SmnAxej0mKGFIqCMLuSsvC_cTJWJbPXQyYa0yEKut6hWMewGvPu61uhALdKyvC4BVoQZ1PAeWUaBG6yyPjhg8dsbf6vmSArjxsFlKtxw3Skhp5xJfOncCe6fwoC9WQ_1JVF7h8XD2NkX2AjwnlLXDXITFTHk6m1OoKmSRddWy9lwurqDJygEgoOTgcif0cTXhZYnZF7937iToWQ8E-1IgKhLyeqrNfjOoxFq6HNDrymf0CapnHzQsM7i1s2lt58nps0xuhIW1q2U.dOLhrQAbFQTSoZNQHQJv50R0EwFcGprAOf75gMu53Ks&dib_tag=se&keywords=DIN934%2BM6&qid=1765730707&sprefix=din934%2Bm6%2Caps%2C106&sr=8-1&th=1) | [TME](https://www.tme.eu/gr/en/katalog/?queryPhrase=DIN934%20M6) |
| Arcade Joystick Assembly | 1 | There is no specific brand for this. There are many similar assemblies on the market, pay attention to the photo to source the exact one. Mind you the mini switches at the bottom. | ![Arcade Joystick Assembly](/icons/item7.png) | [grobotronics](https://grobotronics.com/arcade-joystick-red-handle.html)  | [amazon.de](https://www.amazon.de/-/en/TOPINCN-Joystick-Classic-Competition-Accessories/dp/B0C3ZJZTLH/ref=sr_1_13?crid=30D8YVWAJBBXF&dib=eyJ2IjoiMSJ9.yAb7Y4OwJqBkzEGvO-Lx1CqPZSvzG50PNe-OqhJpXfpb-NGmc802vJZpZymap4rs8_AYd4h7jRfTKh8IU-IWSnxZekvz3FYwBYm7959F0TkZEp7YhhVUcVdV72pLWT_fkJr_C036k-8_a4sPrgihEAS64bp8XUTIKJZ0ZudQo-umebNyS3cjakv9bquy5X1QMHM-902a_rZCOVCBZjpOsQcP0g6QTF1pYPgpn28SSlU.-sB7wg21R40LZtnXChBxCTkSJxKJ4WSvY52lmNLa1Dw&dib_tag=se&keywords=Arcade+Joystick&qid=1765731021&sprefix=arcade+joystick%2Caps%2C131&sr=8-13) | [AliExpress](https://www.aliexpress.com/item/33008035407.html?spm=a2g0o.productlist.main.14.37bbO8wdO8wdhN&algo_pvid=b734923e-5358-4c62-be63-a92783f1661e&algo_exp_id=b734923e-5358-4c62-be63-a92783f1661e-31&pdp_ext_f=%7B%22order%22%3A%225%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%215.94%215.46%21%21%2148.00%2144.16%21%40210391a017657318030786194ea54a%2167115624089%21sea%21GR%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A5f7d80cc%3Bm03_new_user%3A-29895&curPageLogUid=ASvR5trkSFxh&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A33008035407%7C_p_origin_prod%3A) |
| Batt 3.7V 2500mAh	| 1 | You need one with JST PH2.0 connector. Try searching for LiPo 555060 | ![LiPo Batt 3.7V](/icons/item8.png) | [grobotronics](https://grobotronics.com/polymer-lithium-ion-battery-3.7v-2500mah-jst-ph.html) | [amazon.de](https://www.amazon.de/-/en/Battery-575166-Lithium-Polymer-Connection/dp/B0D7VVJ4JR/ref=sr_1_7?crid=37Z7TVYRU3NZB&dib=eyJ2IjoiMSJ9.Gw6IEzcWolSkJM35XT8ptzzhw4OklGI-RrOfaUbY9w_JH6wWrdjigGXDdF_ePbTZLDLtNWZQyYdFU8UY7ifyfnssnswnMfnRfJiutfw1_rG0uZMWU7cXSA6pphk3MW9t4Bz5jXTtQBLpZnmrbJd4OTHqJbdh9pA3GRWmiMgExdoxX_tvnkNngOBRRUN26K898M0dGoprYpAX2vckIUF0Mi1dUdUz20GXJ9srNGdbkX4.pN2J0n1TQPAmCzrKXmipfbUBiwH3I0gU7LUeOksXRvs&dib_tag=se&keywords=Batt%2B3.7V%2B2500mAh&qid=1765732774&sprefix=batt%2B3.7v%2B2500mah%2Caps%2C156&sr=8-7&th=1) | [AliExpress](https://www.aliexpress.com/item/1005002956503167.html?spm=a2g0o.productlist.main.2.10f3RfCdRfCdSJ&algo_pvid=405c36f7-3cf9-43d4-a664-210bcce8e152&algo_exp_id=405c36f7-3cf9-43d4-a664-210bcce8e152-1&pdp_ext_f=%7B%22order%22%3A%228%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%215.18%214.46%21%21%215.93%215.10%21%402103847817657331538142309e1fa1%2112000022952494914%21sea%21GR%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A5f7d80cc%3Bm03_new_user%3A-29895&curPageLogUid=FMS9uT9Gj2lx&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005002956503167%7C_p_origin_prod%3A) |
| Screw Terminal 6P 2.54mm | 5 | You can buy assortment for 2pin-3pin-4pin-5pin-6pin screw terminals but in most cases you’ll be ok with just buying 6pin and laying them down as needed. Make sure they are the 2.54mm pitch pin variant | ![Screw Terminals](/icons/item9.png) | [grobotronics](https://grobotronics.com/screw-terminal-6p-2.54mm.html) |
| Hook-Up Wire 22 to 24 AWG 0.32 to 0.20 mm2 Assortment colors (Stranded) |  | Prefer different colors so to make your life easier identifying which switch to which board pin. Prefer stranded type. Diameter size is a matter of preference here | ![Hook-up Wire](/icons/item10.png) | [grobotronics](https://grobotronics.com/hook-up-wire-22awg-0-32mm2-assortment-stranded-ods7.html) |
| FireBeetle2 ESP32-C6 (DFR1075) | 1 | Select only ONE of these 3 board. All have been tested to work. Prefer ESP32-C6 being cheaper, more modern and feature-rich. Make sure you buy one of the exact DFR codes. | ![FireBeetle2 ESP32-C6](/icons/item11.png) | [grobotronics](https://grobotronics.com/firebeetle-2-esp32-c6-wi-fi-6-bluetooth-5-solar-powered.html) | [DFRobot](https://www.dfrobot.com/product-2771.html) |
| FireBeetle2 ESP32-S3(N4) (DFR1145) | 1 | Select only ONE of these 3 board. All have been tested to work. Prefer ESP32-C6 being cheaper, more modern and feature-rich. Make sure you buy one of the exact DFR codes. | ![FireBeetle2 ESP32-S3](/icons/item12.png) |  [grobotronics](https://grobotronics.com/firebeetle-2-esp32-s3-n4.html) | [DFRobot](https://www.dfrobot.com/product-2836.html) |
| FireBeetle2 ESP32-E N16R2 (DFR1139) | 1 | Select only ONE of these 3 board. All have been tested to work. Prefer ESP32-C6 being cheaper, more modern and feature-rich. Make sure you buy one of the exact DFR codes. | ![FireBeetle2 ESP32-E](/icons/item13.png) | [grobotronics](https://grobotronics.com/firebeetle-2-esp32-c6-wi-fi-6-bluetooth-5-solar-powered.html) | [DFRobot](https://www.dfrobot.com/product-2837.html) |
| Quick Disconnect - Female Bare 2.8mm | 20 | OPTIONAL item. Only needed if you don’t wish to solder the microswitch terminals. The 2.8mm version is for microswitches | ![Quick Disconnect - Female Bare 2.8mm](/icons/item14.png) | [grobotronics](https://grobotronics.com/quick-disconnect-female-bare-2.8mm-bag-of-100.html) |
| Quick Disconnect - Female Bare 4.8mm | 8 | OPTIONAL item. Only needed if you don’t wish to solder the microswitch terminals. The 4.8mm version is for the joystick assembly | ![Quick Disconnect - Female Bare 4.8mm](/icons/item15.png) | [grobotronics](https://grobotronics.com/quick-disconnect-female-bare-4.8mm-bag-of-100.html) |

Regarding the DFRobot ESP boards, I have successfully tested all 3 different DFRobot boards and have modified the source code so it’s compatible with all three of them.
If you would like to compile on your own, there is a single sketch. If you wish to flash directly using a .bin file, you’ll need to pick the correct binary for your board. 
ESP32-C6 (DFR1075) is the only one that supports active battery level monitoring. The other two will only report a dummy 100% battery. However ESP32-C6 is the trickiest to flash although I hear this is fixed in later board or chip revisions. In any case I provide clear instructions on how to flash each of them.

<br>

# Assembly Instructions
You can find Assembly instructions with photos here --> <a href="/docs/assembly/Renegade Stick Assembly Guide.pdf" target="_blank">User Manual (PDF)</a>

<br>

# Operating Instructions

Charging the Renegade Stick
-----------------------------
To charge the Renegade stick, connect a USB type-C cable. A Red LED next to the USB port will indicate that the battery is charging. The Red LED will go off when battery is fully charged, you may disconnect the USB type-C cable.

<br>

Turn the device ON
------------------
A **green LED** next to the USB connector indicates the current power state of the Renegade Stick:
* **Green LED ON**: the device is powered on and active
* **Green LED OFF**: the device is powered off or in deep-sleep mode
 
To wake the device from deep sleep, press and hold **both front buttons** (the eyes of the ghost) for **at least 3 seconds**.  
The green LED will begin to flash, indicating that the device has powered on.   
To preserve battery life, the Renegade Stick will automatically enter deep sleep in the following cases:  
* If the device is paired but no button presses or joystick movement are detected for more than **5 minutes**  
* If the device is not paired, or pairing does not occur within **5 minutes**  

<br>

Pairing the Renegade Stick
--------------------------
When the Renegade Stick is ready to be paired—or is not currently paired with a host—**the green LED will blink slowly** (about once per second).  
On your host device, open the **Bluetooth settings** and scan for nearby devices.
You should see **“Renegade Stick”** appear in the list. Select it to initiate pairing.  
Pairing behavior may vary slightly depending on your operating system or host device, but in most cases selecting the device from the list is all that is required.  
Once pairing is successful, the green LED will begin to **flash rapidly**, indicating an active connection to a host.
While paired, the Renegade Stick will stop advertising itself to other devices. If you wish to pair it with a different host, you must first unpair it from the currently connected device.
If the Renegade Stick was previously paired but the host is turned off or out of range, it will automatically return to pairing mode and wait to be claimed by a host.

<br>

Button Mapping
--------------
If your game or console allows, it would be a good idea to do some button mapping.
By default the handle will be discovered as a dual axis Joystick and the buttons are numbered from left to right 1 to 4 and then from the right side to the left 5 to 8 like below.
The buttons will flip over with a key combo, read below

                            /\                      
      BUTT 1                \/                BUTT 5
              BUTT 2        ||        BUTT 6        
      BUTT 3                ||                BUTT 7        
              BUTT 4                  BUTT 8
                      SELECT  START                                

The two front buttons from left to right are SELECT and START

<br>

On some consoles the default mapping is the following but it may differ on your console.
| Renegade Stick Buttons | PC | Android | PS Mode 1 | PS Mode 2 |
| ---------------------- | -- | ------- | --------- | --------- |
| BUTT 1 | 1 | A | square button | X button |
| BUTT 2 | 2 | B | X button | circle button | 
| BUTT 3 | 3 | C | circle button | X button |
| BUTT 4 | 4 | X | triangle button button | square button |
| BUTT 5 | 5 | Y | L1 shoulder | triangle button button |
| BUTT 6 | 6 | Z | R1 shoulder | R1 shoulder |
| BUTT 7 | 7 | L1 | L2 shoulder | L1 shoulder |
| BUTT 8 | 8 | R1 | R2 shoulder | R1 shoulder |

<br>

Modes of Operation / Combo Keys
------------------------------
The device has **two modes** of operation **DPAD mode** and dual **Axis mode**. Dual axis mode is meant to be used by analog controllers and some games depend on axis control. Other games are easier to be played on DPAD mode.  
You can instantly switch between modes by pressing a "key combo". The device needs to be paired. You will notice the **Green LED** blinking at a different rate.  

The device can flip the keys over depending if you prefer to move the stick with your Right or Left hand. To flip the keys use a "key combo".

Key Combos
| Mode of Operation | Key combo (press the keys at the same time ) |
| ----------------- | ------------------------------------------- |
| Switch Hand side | 1 + 2 + 5 + 6 |
| Switch mode (axis/DPAD) | 3 + 4 + 7 + 8 |
| Switch Off/enter Deep Sleep | SELECT + START + 7 |
| Reboot board Firmware | SELECT + START + 8 |


You can verify and test using gamepad testers. [Testing the Device](#testing-the-device).  
Every time the device switches off it will not retain any of these settings and will default to **axis mode** and **right hand operation**

<br>

LED indicators
--------------

| USB LED Color | State | Meaning |
| ------------- | ----- | ------- |
| Green | Flashing slow (1s)| Device Not paired |
| Green | Flashing very quick | Device Paired (axis mode) |
| Green | Flashing quick | Device Paired (DPAD mode) |
| Green | OFF | Gamepad is in sleep mode/battery discharged |
| Red | permanently ON | Battery charging |
| Red | OFF | Battery charged/ Battery Full |
| Red | Flashing | No battery detected | 

<br>

# Testing the Device

On a **PC/MAC** you can test your device online directly on [hardwaretester.com](https://hardwaretester.com/gamepad)  
On an **Android** Device you can download the following app [Gamepad Tester](https://play.google.com/store/apps/details?id=com.chimera.saturday.evogamepadtester)

<br>

# Flashing the Renegade Stick

## Prerequisites

* USB-C cable
* Windows, macOS, or Linux PC
* One of the following:

  * Arduino IDE
  * Python + `esptool`
  * Espressif Flash Download Tool (not supported on all of the boards)

Please follow the flush instructions here --> [flash instructions](/binaries/flash%20instructions.md)


<br>

# Liked it ?
If you found some of this information useful and would like to buy me a coffee you can donate below

[![Donate with PayPal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.me/mach0gr)

or you can just say thank you at

[pmatsakos@gmail.com](mailto:pmatsakos@gmail.com)


