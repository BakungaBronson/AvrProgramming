### Cattle Grazing Management System

## Group Members
LWANGA CONRAD ARTHUR 18/U/21116/PS
BAKUNGA BRONSON 18/U/23411/EVE
DALI HILLARY 18/U/21102/PS
KATUSIIME CONRAD 18/U/855

## Layout
There are two foldes, namely "keyandpeele" and "new circuitry", the first contains the ATMEL studio project and the second contains the Proteus schematic.

The versions of ATMEL studio and Proteus used are 7.0 and 8.10 SP3. For compatibility purposes, it is recommended to use the same versions or those higher.

## Limitations
The only limitation comes with the Multiplexed 7 segment display which displays the total grazing time of the cattle. Here we found that using 1 out of the 4 digits works without an issue however when the grazing time exceeds 9 and needs two digits or more to show, it becomes hard to show all the digits at all times given that using more than one digit on the 7 segment requires the use of a loop which we cannot have. The only solution here is to use threads however that might be done later on.

## Things to note
The LCD screen and the 8 LED lights show the status of the main doors that lead to the 4 paddocks. We took modelled the system like this because we can know the cows are grazing when the grazing counter is increasing per minute and we can know they are drinking water when the counter stops increasing. 

The keypad numbers 1, 2, 3, 4 and 0 open the main doors, with the number corresponding to the paddock and 0 opening all the paddocks at once.

After a button is pressed, the cows go through the entire process and when the doors are closed again, which is shown on the LCD after about 11 minutes 20 seconds, another button may be pressed for another paddock to open and the cows there also go through 1 cycle as well.

Pressing a button after a cycle has started has no effect on the system.
