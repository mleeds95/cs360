# README: CS 360 Project 3 #
* Author: Matthew Leeds
* Date: 2015-02-24

## Assumptions ##
* Items should be considered the same when their descriptions match.
* Items with UPC's not in the Manufacturers file should not be included in the output.

## Design Description ##

My project has two main classes, ManufacturerData and SalesData, which each handle reading in their respective
data files. ManufacturerData is where most of the work happens since SalesData simply makes calls
to add items in ManufacturerData's objects. 

ManufacturerData has three data structures that can each independently handle storing all the data:
an array of UPCInfo pointers, a "Perfect" Hash Table, and a Red-Black Tree. The latter two are implemented
by separate classes. Regardless of which data structure we will use, the data is read from the file into the 
array first so that we can efficiently identify aliases. Then it's all moved to either a Hash Table or a Red-Black Tree.
At that point those classes are the ones responsible for freeing the associated memory. This setup, in addition to 
meeting the project requirements, allows us to guarentee O(1) search operations in the worst case (for both data structures).
However, since the array can be sorted by name (rather than code), it is used to produce the final report.
(Actually it makes calls to the table/tree for the detailed data but it is used for ordering).

My Project 2 design description has a more detailed explanation of the structure, and most of it still applies.

Hopefully everything else is clarified by the comments. Thanks!
