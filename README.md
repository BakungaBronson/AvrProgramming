### Cattle Grazing Management System

## Layout
There are two foldes, namely "keyandpeele" and "new circuitry", the first contains the ATMEL studio project and the second contains the Proteus schematic.

The versions of ATMEL studio and Proteus used are 7.0 and 8.10 SP3. For compatibility purposes, it is recommended to use the same versions or those higher.

## Limitations
The only limitation comes with the Multiplexed 7 segment display which displays the total grazing time of the cattle. Here we found that using 1 out of the 4 digits works without an issue however when the grazing time exceeds 9 and needs two digits or more to show, it becomes hard to show all the digits at all times given that using more than one digit on the 7 segment requires the use of a loop which we cannot have. The only solution here is to use threads however that might be done later on.
