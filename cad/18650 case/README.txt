                   .:                     :,                                          
,:::::::: ::`      :::                   :::                                          
,:::::::: ::`      :::                   :::                                          
.,,:::,,, ::`.:,   ... .. .:,     .:. ..`... ..`   ..   .:,    .. ::  .::,     .:,`   
   ,::    :::::::  ::, :::::::  `:::::::.,:: :::  ::: .::::::  ::::: ::::::  .::::::  
   ,::    :::::::: ::, :::::::: ::::::::.,:: :::  ::: :::,:::, ::::: ::::::, :::::::: 
   ,::    :::  ::: ::, :::  :::`::.  :::.,::  ::,`::`:::   ::: :::  `::,`   :::   ::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  :::::: ::::::::: ::`   :::::: ::::::::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  .::::: ::::::::: ::`    ::::::::::::::: 
   ,::    ::.  ::: ::, ::`  ::: ::: `:::.,::   ::::  :::`  ,,, ::`  .::  :::.::.  ,,, 
   ,::    ::.  ::: ::, ::`  ::: ::::::::.,::   ::::   :::::::` ::`   ::::::: :::::::. 
   ,::    ::.  ::: ::, ::`  :::  :::::::`,::    ::.    :::::`  ::`   ::::::   :::::.  
                                ::,  ,::                               ``             
                                ::::::::                                              
                                 ::::::                                               
                                  `,,`


https://www.thingiverse.com/thing:456900
Flexing battery holders with integrated spring by enif is licensed under the Creative Commons - Attribution - Share Alike license.
http://creativecommons.org/licenses/by-sa/3.0/

# Summary

For my electronic projects I often need battery holders of various size and for different number of cells: single, multiple cells in parallel or in series, or serial lithium-ion type cells with connectors for balanced charging between the cells.  
  
So the project here was to generate fully parametrized, printable battery holders for cylindrical cells of arbitrary size and number.  The additional challenge for me was to have the battery sit firmly in the holder without the use of the metallic spring that is usually found at the minus pole. In this design the metallic spring is replaced by a flexible printed curled structure, which presses the contacts firmly to the battery.  This plastic spring flexes about 1 - 2mm, which is just what's needed to comfortably insert and remove the cells.  
  
   
  
The contacts for the plus and minus pole can easily be made by a few windings of the uninsulated ends of the connecting wires.  Each battery compartment contains are several holes to the outside as well ad to the neighboring compartments, through which connecting wires can be passed for easy configuring of parallel, serial or balanced-serial battery packs.  Also, on the bottom of the case, there are longitudinal and traversal wire channels, which can be used for assing wires outside the case.  
  
   
Given that the printed plastic spring needs to be flexible, ABS is the material of choice here.  Also, I use a some "ABS slur" (mixture of ABS and acetone) to cover and insulate the otherwise exposed outer part of the pole connectors.  
In addition to the SCAD source file, I have added STL files for 1/2/3/4 cells of type AA, AAA, 18650(Li-Ion), as well as single cell versions for 18650P (protected Li-Ion), CR123A (aka 16340) and C (this one is untested yet,  as I don't have any C-cell around here).  
   
  
Of course, you can also just use these battery holders without any wiring to serve as battery cases, for carrying your spare batteries around.  But for this, you should also have a look at my [battery caps](http://www.thingiverse.com/thing:137582)...  
   
  
  
_Update 2014-09-17:  Upon request of user [wohenzhuce](http://www.thingiverse.com/wohenzhuce/about) I have also added STL files for 26650 type LiFePo Cells. These are still untested.  They were produced in OpenScad with the call:_  
`flexbatter(n=n,l=65.7,d=26.4,hf=0.72,shd=3,eps=0.28);`  

_Update 2015-04-10: Upon request of user [h4wk3y](http://www.thingiverse.com/h4wk3y/about) I have now uploaded extra long versions (70mm) needed for some protected 18650 cells, these are named_ `flexbatter18700xN.stl`._  

_Update 2015-07-25: I just published a [new version of this project](http://www.thingiverse.com/thing:941081) which supports multi-cell compartments housing 2 or 3 cells in a row._

# Instructions

I printed these battery holders on my DIY box-frame Prusa i3 using a 0.40mm nozzle with 0.25mm layer height and 0.56mm extrusion width.  
  
  
By default, the thickness of the spring part is twice the extrusion width _ew_.  If you have a significantly different extrusion width, for obtaining optimal spring strength, you might want to modify the _eh_ and _ew_ parameters in the SCAD file to fit your printer, and then rebuild all the STLs you need.