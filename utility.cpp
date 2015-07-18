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
                qDebug() << firstStringCharacter;
                qDebug() << secondStringCharacter;
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
                if (!(secondStringCharacter.isLetter()))
                {
                    j++;
                }
            }

        }
        else
        {
            return true;
        }
    }
    return true;
}
