#include "utility.h"

bool AlphabeticallyFirst(QString firstString,QString secondString)
{
    int j = 0;
    for (int i = 0; i < firstString.size(); i++)
    {
        //i is the iterator for the first string
        //j is the iterator for the second string
        if (i < secondString.size())
        {
            QChar firstStringCharacter = firstString.at(i).toLower();
            QChar secondStringCharacter = secondString.at(j).toLower();
            //Ensure that these are both letters
            if (firstStringCharacter.isLetter() && secondStringCharacter.isLetter())
            {
                if ((secondStringCharacter < firstStringCharacter))
                {
                    return false;
                }
                else if (firstStringCharacter < secondStringCharacter)
                {
                    return true;
                }
                j++;
            }
            else
            {
                //If the first character is not, we will already be moving on
                //Otherwise if the second is also not a letter, we will move on
                if (!(secondStringCharacter.isLetter()))
                {
                    j++;
                }
            }

        }
        else
        {
            //End of second string, so we must be done
            return true;
        }
    }
    return true;
}
