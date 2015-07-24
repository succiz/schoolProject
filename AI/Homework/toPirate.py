#--coding: utf8 --

dict1 = {'hello':'avast',
        'excuse':'arrr',
        'sir':'matey',
        'boy':'matey',
        'man':'matey',
        'madam':'proud beauty',
        'officer':'foul blaggart',
        'the':"th'",
        'my':'me',
        'your':'yer',
        'is':'be',
        'are':'be',
        'restroom':'head',
        'restaurant':'galley',
        'hotel':'fleabat inn'}

fileDir = raw_input("Please Enter a File Name:")

def toPirate(fileDir, dic1):
    try:
        f = open(fileDir, "r");
        stringContents = f.readlines();
        wordsArray = stringContents.split();
        index =0;
        for w in wordsArray:
            if w in dict1:
                wordsArray[index] = dict1[w];
            index = index+1
        return wordsArray
    except:
        print "Cannot open this file!\nPlease enter the whole path of the file."

print toPirate(fileDir,dict1)
