# README: CS 360 Project 2 #
* Author: Matthew Leeds
* Date: 2015-02-08

## Assumptions ##
* Items should be considered the same when their descriptions match.
* Items with UPC's not in the Manufacturers file should not be included in the output.

## Design Description ##

My project two classes, ManufacturerData and SalesData, which each handle reading in their respective
data files. ManufacturerData is where most of the work happens since SalesData simply makes calls
to add items in ManufacturerData's objects. It makes heavy use of arrays and pointers to ensure
efficiency and compliance with the project specification. Because of this, there are member variables
storing array sizes and functions for resizing them. 

ManufacturerData stores most of its data in the allUPCs variable, a pointer to UPCInfo pointers. Each i
UPCInfo object is a struct with the UPC code and a pointer to a ManufacturerInfo object. It's important
to separate that information because the duplicate entries will have different UPC values but the 
same memory address for mInfo. In the ManufacturerInfo struct, you can store a company's name and 
list of Items (as well as auxiliary variables). The listOfItems is a pointer to Item pointers, which 
is the last level of abstraction. The Item struct just has description, quantity, and code.

One of the most important functions in ManufacturerData is sortByUPCorName(bool), which uses merge sort
to efficiently sort allUPCs either by UPC code or (case-insensitive) names. Given that merge sort takes
Theta(nlgn) time, it seemed like a good choice for the large number of records we have. My implementation
of it is not in-place.

Another important function is findByUPC(int UPC, int start, int end), which does a binary search to find
a company in the sorted array in lgn time. This gets called for every item that's read in (and calls
itself), so it makes sense to just sort the whole thing once in main rather than in the method.

The findAliases() function is also pretty interesting. It uses the sort function to sort by name, then
does one iteration over the allUPCs array. If an entry has the same name as the last one, we just
free its memory and assign its mInfo to the previous one. This way when we're using the data structure 
we don't even have to worry about duplicates; you'll automatically be pointed to the right place.
Unfortunately, we do have to keep track of which indices in the array have had this done, so we don't
try to double free that memory or display it twice in the report. These are stored in an integer array. 

The addItem(int UPC, int fullCode, string description) function also needs to be efficient since it will
be called every time a record is read from the items file. Utilizing findByUPC, it doesn't waste any extra
time on UPCs that don't exist in our data. Then it does a linear time search for an existing item with the
same description. This actually ends up making the whole program run in ~1.5s rather than ~30s when you
sort the items array every time and use a binary search. This is probably because the number of items is
generally pretty small for most of the manufacturers. This function also resizes listOfItems to twice as big
if necessary, which reduces the overhead from copying the whole array when it's resized. This is also the case
everywhere else that does array resizing.

Finally, the printReport() function simply sorts by Name using the function, and does one iteration over
allUPCs, printing each as it goes (except for duplicates). This is quite easy because of the hierarchal 
data structure that already has everything we need, like quantities for items, non-ALLCAPS names for companies,
etc.

As I said before, the SalesData constructor simply adds items to the ManufacturerData object as it reads them
in. If this code were for a more general application, you would probably want to save that data in an array
independent of mData, but this strategy is efficient and targets our computation at generating the report.

Hopefully everything else is clarified by the comments. Thanks!
