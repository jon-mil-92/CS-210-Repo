FILENAME = 'items.txt'

def readFile(filename):
   '''
   This function gets the list of lines read in from the file in raw form.
   @param filename - The filename to read in (must be in same directory as the Source.cpp!).
   @return - The list of lines.
   '''
   lines = [] # Declare empty list for items.txt contents.

   # Open the 'items.txt' file and read the contents into a list.
   with open(filename) as file:
      lines = file.readlines()

   return lines


def getInventory():
   '''
   This function gets the inventory read in from the file.
   @return - A Dictionary of inventory in the form {item : frequency}.
   '''
   inventory = {} # Dictionary of {item : frequency}.
   items = readFile(FILENAME) # Get a list of the 'items.txt' contents.

   # Loop through the list of items.
   for item in items:
      item = item.replace('\n', '') # Remove the newline character at end of line.

      # Update existing frequency; otherwise add item to dictionary.
      if item in inventory:
         inventory[item] += 1 # Accumulate to the dictionary item.
      else:
         inventory[item] = 1 # Add the item to the dictionary with a frequency of 1.
            
   return inventory


def determineInventory():
   '''
   This function prints each item and its corresponding frequency to the console.
   '''
   inventory = getInventory() # Get the inventory.

   # Print each item and its frequency from the inventory to the console.
   for key, value in inventory.items():
      print(key, value)


def determineFrequency(item):
   '''
   This function determines the frequency of a given item that occurs in the inventory.
   @return - The item's frequency if it occurs in the inventory; Otherwise, 0 is returned because it is not in the inventory.
   '''
   inventory = getInventory() # Get the inventory
   itemFrequency = 0;
   
   # If the item is in the inventory, get its frequency.
   if item in inventory:
      itemFrequency = inventory[item]

   return itemFrequency
   

def output():
   '''
   This function loops through the inventory dictionary and writes each item and its frequency to a line in the frequency.dat file.
   '''
   inventory = getInventory()
   numOfItems = len(inventory) # How many items are in the inventory dictionary.
   itemCounter = 1 # Item counter to keep track of how many items have been accessed from the inventory dictionary.
   
   # Open the frequency.dat file for writing and automatically close it when finished writing data.
   with open('frequency.dat', 'w') as frequencyOutputFile:

      # Write each item and its frequency from the dictionary on its own line in the frequency.dat file.
      for key, value in inventory.items():
         if (itemCounter < numOfItems): # If not on the last item left in the dictionary, print a newline.
            itemLine = key + ' ' + str(value) + '\n'
         else: # If on the last item left in the dictionary, do not print a newline.
            itemLine = key + ' ' + str(value)

         itemCounter += 1 # Increment the item counter.
         frequencyOutputFile.write(itemLine) # Write the item and frequency string to the frequency.dat file.

def getMaxItemNameLength():
   '''
   This function loops through the keys in the inventory dictionary and determines which item name string has the longest length.
   @return - The max item name string length.
   '''
   inventory = getInventory()
   maxItemNameLength = 0

   # Iterate through the items in the inventory and determine the max item name string length.
   for itemName in inventory.keys():
      # If an item name string has a length that is longer than the previous max item name string, assign its length to the max item name length.
      if (len(itemName) > maxItemNameLength):
         maxItemNameLength = len(itemName)

   return maxItemNameLength

def getMaxFrequency():
   '''
   This function loops through the values in the inventory dictionary and determines the max item purchase frequency.
   @return - The max item purchase frequency.
   '''
   inventory = getInventory()
   maxFrequency = 0

   # Iterate through the frequency values in the inventory and determine the max item purchase frequency.
   for frequency in inventory.values():
      # If a frequency value is larger than the previous max frequency value, update the max frequency.
      if (frequency > maxFrequency):
         maxFrequency = frequency;

   return maxFrequency

