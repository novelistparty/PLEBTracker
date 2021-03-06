#include "instedtr.h"
#include <iostream>




void instedtr::chgSelWavSeg(int i)
{
    selwavseg += i;
    if(selwavseg > WAVSEG_TONE)
        if(i > 0)
            selwavseg = WAVSEG_TONE; 
        else
            selwavseg = WAVSEG_WAVE;
}

void instedtr::chgSelWavRow(int i)
{
    using namespace editor;
    selwavrow += i;
    if(selwavrow > song->numWaveEntries())  //not -1! why not?. o yeah new waves
        if(i > 0)
            selwavrow = song->numWaveEntries(); //not -1! 
        else
            selwavrow = 0;

    unsigned short height;
    if(editor::wingroup == editor::instwin)
    {
        height = editor::WIN_HEIGHT - 4-1; //-1 for the header
    }
    else if(editor::wingroup ==editor::ptrnwin)
    {
        height = editor::WIN_HEIGHT - 3-1;
    }

    //Change viewport
    if(selwavrow >= viewportwave + height)
    {
        viewportwave += 4;
        if(viewportwave > song->numWaveEntries())
            viewportwave = song->numWaveEntries()-1;
    }
    else if(selwavrow < viewportwave)
    {
        viewportwave -=4;
        if(viewportwave > song->numWaveEntries())
            viewportwave = 0;
    }

}

void instedtr::chgSelPulSeg(int i)
{
    selpulseg += i;
    if(selpulseg > 1)
        if(i > 0)
            selpulseg = 1; 
        else
            selpulseg = 0;
}

void instedtr::chgSelPulRow(int i)
{
    using namespace editor;
    selpulrow += i;
    if(selpulrow > song->numPulseEntries()) 
        if(i > 0)
            selpulrow = song->numPulseEntries(); //not -1! 
        else
            selpulrow = 0;

    unsigned short height;
    if(editor::wingroup == editor::instwin)
    {
        height = editor::WIN_HEIGHT - 4-1; //-1 for the header
    }
    else if(editor::wingroup ==editor::ptrnwin)
    {
        height = editor::WIN_HEIGHT - 3-1;
    }

    //Change viewport
    if(selpulrow >= viewportpulse + height)
    {
        viewportpulse += 4;
        if(viewportpulse > song->numPulseEntries())
            viewportpulse = song->numPulseEntries()-1;
    }
    else if(selpulrow < viewportpulse)
    {
        viewportpulse -=4;
        if(viewportpulse > song->numPulseEntries())
            viewportpulse = 0;
    }

}

void instedtr::chgSelFltSeg(int i)
{
    selfltseg += i;
    if(selfltseg > 1)
        if(i > 0)
            selfltseg = 1; 
        else
            selfltseg = 0;
}

void instedtr::chgSelFltRow(int i)
{
    using namespace editor;
    selfltrow += i;
    if(selfltrow > song->numFilterEntries()) 
        if(i > 0)
            selfltrow = song->numFilterEntries(); //not -1! 
        else
            selfltrow = 0;

    unsigned short height;
    if(editor::wingroup == editor::instwin)
    {
        height = editor::WIN_HEIGHT - 4-1; //-1 for the header
    }
    else if(editor::wingroup ==editor::ptrnwin)
    {
        height = editor::WIN_HEIGHT - 3-1;
    }

    //Change viewport
    if(selfltrow >= viewportfilter + height)
    {
        viewportfilter += 4;
        if(viewportfilter > song->numFilterEntries())
            viewportfilter = song->numFilterEntries()-1;
    }
    else if(selfltrow < viewportfilter)
    {
        viewportfilter -=4;
        if(viewportfilter > song->numFilterEntries())
            viewportfilter = 0;
    }

}


void instedtr::chgSelVolSeg(int i)
{
    selvolseg += i;
    if(selvolseg > VOLSEG_DUR)
        if(i > 0)
            selvolseg = VOLSEG_DUR; 
        else
            selvolseg = VOLSEG_VOL;
}

void instedtr::chgSelVolRow(int i)
{
    using namespace editor;
    selvolrow += i;
    if(selvolrow > selinst->numVolEntries())
        if(i > 0)
            selvolrow = selinst->numVolEntries();
        else
            selvolrow = 0;

    unsigned short height = editor::WIN_HEIGHT - 4-1; //-1 for the header

    //Change viewport
    if(selvolrow >= viewportvol + height)
    {
        viewportvol += 4;
        if(viewportvol > selinst->numVolEntries())
            viewportvol = selinst->numVolEntries()-1;
    }
    else if(selvolrow < viewportvol)
    {
        viewportvol -=4;
        if(viewportvol > selinst->numVolEntries())
            viewportvol = 0;
    }

}


void instedtr::chgSelInstRow(int i)
{
    selinstrow += i;
    if(selinstrow > 3)
        if(i > 0)
            selinstrow = 3;
        else selinstrow =0;
    chgSelInstObj(0);
    return;
}
void instedtr::chgSelInstObj(int i)
{
    selinstobj += i;
    if(selinstrow == 0)
    {
        if(selinstobj > 6)
            if(i > 0)
                selinstobj = 6; 
            else
                selinstobj = 0;
    }
    else if(selinstrow > 0)
    {
        selinstobj = 0;
    }
}


void printline(const char *c, unsigned char y0, unsigned char y1)
{
    using editor::charBuffer;
    int rem = editor::WIN_WIDTH % 8;
    int div = editor::WIN_WIDTH / 8;

    for(int i = 0; i < 8; i++)
        charBuffer[i]=c[0];
    charBuffer[9] = 0;

    for(int i = 0; i < div; i++)
    {
        mvprintw(y1,8*i, charBuffer, editor::instwin);
        mvprintw(y0,8*i, charBuffer, editor::instwin);
    }
    for(int i = 8*div; i < editor::WIN_WIDTH; i++)
    {
        mvprintw(y1,i, c, editor::instwin);
        mvprintw(y0,i, c, editor::instwin);
    }
}




void instedtr::display()
{
    displayInst();
    displayWav();
    displayPulse();
    displayFilter();
    displayVol();

    //Print metaobjedit information
    if(instobjedit)
    {
        attron(A_BOLD);
        mvprintw(editor::WIN_HEIGHT-1, 0, "Editing a field: Press TAB to cancel or ENTER to commit", stdscr);
        attroff(A_BOLD);
    }

    printline(" ", 0, editor::WIN_HEIGHT - 1);
}

void instedtr::displayWav()
{
    attroff(-1);
    unsigned int y;
    unsigned int x;
    unsigned int height;
    if(editor::wingroup == editor::instwin)
    {
        y = 2;
        x = (editor::WIN_WIDTH-13)-11*2;
        height = editor::WIN_HEIGHT - 4-1; //-1 for the header
    }
    else if(editor::wingroup ==editor::ptrnwin)
    {
        y = 3;
        x = editor::WIN_WIDTH-11*3;
        height = editor::WIN_HEIGHT - 3-1;
    }

    attron(A_UNDERLINE);
    mvprintw(y++, x, "|WAVE TABLE",editor::wavewin);
    unsigned short * wavTable = editor::song->getWaveTable();
    //Print the wave table entries
    bool emptyvisible = true;
    bool lastselected = false;

    int entries = editor::song->numWaveEntries();

    //If the last entry is visible but not selected, print it dashes
    //otherwise print it with the numbers stored in it


    if(selwavrow == entries && editor::inputwin == editor::wavewin)
        lastselected = true;

    entries -= viewportwave; //Put in reference of viewport
    if (entries > height)
    {
        entries = height;
        emptyvisible = false;
    }
    else
        if(lastselected)
            entries++;

    using editor::charBuffer;
    charBuffer[5] = '|';
    charBuffer[6] = 0;
    int i;
    for(i = 0; i < entries; i++)
    {
        charBuffer[0] ='|';

        //vvvvvv
        //|0000|00 00
        setWaveAttribs(viewportwave+i, WAVSEG_NUM);
        editor::shortString(charBuffer+1, viewportwave + i,4);
        mvprintw(y+i, x, charBuffer, editor::wavewin);

        //         vv
        //|0000|00 00
        charBuffer[4] = 0;
        editor::shortString(charBuffer, wavTable[viewportwave+i],4);
        setWaveAttribs(viewportwave+i, WAVSEG_TONE);
        mvprintw(y+i, x+9, charBuffer+2, editor::wavewin);

        //      vvv
        //|0000|00 00
        charBuffer[2] = ' ';
        charBuffer[3] = 0;
        setWaveAttribs(viewportwave+i, WAVSEG_WAVE);
        mvprintw(y+i, x+6, charBuffer, editor::wavewin);
    }

    if(emptyvisible)
    {
        if(!lastselected && i < height)
        {
            charBuffer[0] = '|';
            editor::shortString(charBuffer + 1, viewportwave + i, 4);
            charBuffer[5] = '|';
            charBuffer[6] = '-';
            charBuffer[7] = '-';
            charBuffer[8] = ' ';
            charBuffer[9] = '-';
            charBuffer[10] = '-';
            charBuffer[11] = 0;

            setWaveAttribs(viewportwave+i, 2);
            mvprintw(y+i++,x, charBuffer);
        }

        setWaveAttribs(entries+1,2);
        charBuffer[0] = '|';
        charBuffer[5]='|';
        for(int j=6; j < 11; j++)
            charBuffer[j] = ' ';
        charBuffer[11]=0;

        while(i < height)
        {
            editor::shortString(charBuffer + 1, viewportwave + i, 4);
            mvprintw(y+i, x, charBuffer, editor::wavewin);
            i++;
        }
        attroff(-1);
    }

}


void instedtr::displayPulse()
{
    attroff(-1);
    unsigned int y;
    unsigned int x;
    unsigned int height;
    if(editor::wingroup == editor::instwin)
    {
        y = 2;
        x = editor::WIN_WIDTH-13-11;
        height = editor::WIN_HEIGHT - 4-1; //-1 for the header
    }
    else if(editor::wingroup ==editor::ptrnwin)
    {
        y = 3;
        x = editor::WIN_WIDTH-11*2;
        height = editor::WIN_HEIGHT - 3-1;
    }
    attron(A_UNDERLINE);

    mvprintw(y++, x, "|PULSE TABL",editor::pulsewin);
    unsigned short * pulseTable = editor::song->getPulseTable();
    //Print the wave table entries
    bool emptyvisible = true;
    bool lastselected = false;

    int entries = editor::song->numPulseEntries();

    //If the last entry is visible but not selected, print it dashes
    //otherwise print it with the numbers stored in it


    if(selpulrow == entries && editor::inputwin == editor::pulsewin)
        lastselected = true;

    entries -= viewportpulse; //Put in reference of viewport
    if (entries > height)
    {
        entries = height;
        emptyvisible = false;
    }
    else
        if(lastselected)
            entries++;

    using editor::charBuffer;
    charBuffer[5] = '|';
    charBuffer[6] = 0;
    int i;
    for(i = 0; i < entries; i++)
    {
        charBuffer[0] ='|';

        //vvvvvv
        //|0000|00 00
        setPulseAttribs(viewportpulse+i, 2);
        editor::shortString(charBuffer+1, viewportpulse + i,4);
        mvprintw(y+i, x, charBuffer, editor::pulsewin);

        //         vv
        //|0000|00 00
        charBuffer[4] = 0;
        editor::shortString(charBuffer, pulseTable[viewportpulse+i],4);
        setPulseAttribs(viewportpulse+i, 1);
        mvprintw(y+i, x+9, charBuffer+2, editor::pulsewin);

        //      vvv
        //|0000|00 00
        charBuffer[2] = ' ';
        charBuffer[3] = 0;
        setPulseAttribs(viewportpulse+i, 0);
        mvprintw(y+i, x+6, charBuffer, editor::pulsewin);
    }

    if(emptyvisible)
    {
        if(!lastselected && i < height)
        {
            charBuffer[0] = '|';
            editor::shortString(charBuffer + 1, viewportpulse + i, 4);
            charBuffer[5] = '|';
            charBuffer[6] = '-';
            charBuffer[7] = '-';
            charBuffer[8] = ' ';
            charBuffer[9] = '-';
            charBuffer[10] = '-';
            charBuffer[11] = 0;

            setPulseAttribs(viewportpulse+i, 2);
            mvprintw(y+i++,x, charBuffer);
        }

        setPulseAttribs(entries+1,0);
        charBuffer[0] = '|';
        charBuffer[5]='|';
        for(int j=6; j < 11; j++)
            charBuffer[j] = ' ';
        charBuffer[11]=0;

        while(i < height)
        {
            editor::shortString(charBuffer + 1, viewportpulse + i, 4);
            mvprintw(y+i, x, charBuffer, editor::pulsewin);
            i++;
        }
        attroff(-1);
    }

}




void instedtr::displayFilter()
{
    attroff(-1);
    unsigned int y;
    unsigned int x;
    unsigned int height;
    if(editor::wingroup == editor::instwin)
    {
        y = 2;
        x = editor::WIN_WIDTH-13;
        height = editor::WIN_HEIGHT - 4-1; //-1 for the header
    }
    else if(editor::wingroup ==editor::ptrnwin)
    {
        y = 3;
        x = editor::WIN_WIDTH-11;
        height = editor::WIN_HEIGHT - 3-1;
    }
    attron(A_UNDERLINE);

    mvprintw(y++, x, "|FILTER TBL",editor::filterwin);
    unsigned short * filterTable = editor::song->getFilterTable();
    //Print the wave table entries
    bool emptyvisible = true;
    bool lastselected = false;

    int entries = editor::song->numFilterEntries();

    //If the last entry is visible but not selected, print it dashes
    //otherwise print it with the numbers stored in it


    if(selfltrow == entries && editor::filterwin == editor::filterwin)
        lastselected = true;

    entries -= viewportfilter; //Put in reference of viewport
    if (entries > height)
    {
        entries = height;
        emptyvisible = false;
    }
    else
        if(lastselected)
            entries++;

    using editor::charBuffer;
    charBuffer[5] = '|';
    charBuffer[6] = 0;
    int i;
    for(i = 0; i < entries; i++)
    {
        charBuffer[0] ='|';

        //vvvvvv
        //|0000|00 00
        setFilterAttribs(viewportfilter+i, 2);
        editor::shortString(charBuffer+1, viewportfilter + i,4);
        mvprintw(y+i, x, charBuffer, editor::filterwin);

        //         vv
        //|0000|00 00
        charBuffer[4] = 0;
        editor::shortString(charBuffer, filterTable[viewportfilter+i],4);
        setFilterAttribs(viewportfilter+i, 1);
        mvprintw(y+i, x+9, charBuffer+2, editor::filterwin);

        //      vvv
        //|0000|00 00
        charBuffer[2] = ' ';
        charBuffer[3] = 0;
        setFilterAttribs(viewportfilter+i, 0);
        mvprintw(y+i, x+6, charBuffer, editor::filterwin);
    }

    if(emptyvisible)
    {
        if(!lastselected && i < height)
        {
            charBuffer[0] = '|';
            editor::shortString(charBuffer + 1, viewportfilter + i, 4);
            charBuffer[5] = '|';
            charBuffer[6] = '-';
            charBuffer[7] = '-';
            charBuffer[8] = ' ';
            charBuffer[9] = '-';
            charBuffer[10] = '-';
            charBuffer[11] = 0;

            setFilterAttribs(viewportfilter+i, 2);
            mvprintw(y+i++,x, charBuffer);
        }

        setFilterAttribs(entries+1,0);
        charBuffer[0] = '|';
        charBuffer[5]='|';
        for(int j=6; j < 11; j++)
            charBuffer[j] = ' ';
        charBuffer[11]=0;

        while(i < height)
        {
            editor::shortString(charBuffer + 1, viewportfilter + i, 4);
            mvprintw(y+i, x, charBuffer, editor::filterwin);
            i++;
        }
        attroff(-1);
    }

}








void instedtr::displayInst()
{
    using editor::lastwin;
    using editor::instwin;
    const bool WINCHANGE = lastwin != instwin;
    if(WINCHANGE)
    {
        instedtr::viewportvol = 0;
        lastwin = instwin;
        attroff(-1);
        attron(COLOR_PAIR(patternedtr::COL_PTRN_SU_SYSFX));
        //Display border
        printline(" ", 0, editor::WIN_HEIGHT - 1);
        printline("=", 1, editor::WIN_HEIGHT - 2);
        int bot = editor::WIN_HEIGHT - 2;

        //Clearing the screen 11 characters at a time
        int div = editor::WIN_WIDTH / 11;
        for(int i = 0; i < div; i++)
            for(int j = 2; j < bot; j++)
                mvprintw(j,11*i, "           ", editor::instwin);//11 spaces

        int right = editor::WIN_WIDTH - 2;
        for(int i = 2; i < bot; i++)
        {
            mvprintw(i, 0, "= ", editor::instwin);
            mvprintw(i, right, " =", editor::instwin);
        }
        attron(A_BOLD);
        attron(COLOR_PAIR(patternedtr::COL_META_UU));
        mvprintw(1, editor::WIN_WIDTH/2 - 8, "INSTRUMENT EDIT", editor::instwin);
    }


    //Display instrument editor
    using editor::charBuffer;
    using editor::charInputBuffer;
    using editor::textCursorPos;
    using editor::numBuffer;
    using editor::byteString;
    using patternedtr::selinstrument;
    using editor::selinst;
    bool isselected;
    int x = 11;

    //Selected Instrument


    //ROW 0
    //DOWN


    attroff(-1);
    mvprintw(2, x+1, "[NCX]", editor::instwin);
    mvprintw(3, x+2, "  WAVE INDEX:", editor::instwin);
    mvprintw(4, x+2, " PULSE INDEX:", editor::instwin);
    mvprintw(5, x+2, "FILTER INDEX:", editor::instwin);
    setInstAttribs(0,0);
    mvprintw(2, x+2, "N", editor::instwin);
    setInstAttribs(0,1);
    mvprintw(2, x+3, "C", editor::instwin);
    setInstAttribs(0,2);
    mvprintw(2, x+4, "X", editor::instwin);

    setInstAttribs(0, 3);
    mvprintw(2, x+7, "v", editor::instwin);

    //UP
    setInstAttribs(0, 4);
    mvprintw(2, x+8, "^", editor::instwin);


    charBuffer[INST_NAME_SIZE] =0;
    //INST NAME
    isselected = setInstAttribs(0, 5);
    if(isselected && instobjedit)
    {
        editor::copy(charInputBuffer, charBuffer, INST_NAME_SIZE);
        editor::makeUnderlines(charBuffer, INST_NAME_SIZE-1);
        mvprintw(2, x+10, charBuffer, instwin);
        attron(COLOR_PAIR(patternedtr::COL_META_UU));
        char sel[2];
        sel[0] = charBuffer[textCursorPos];
        sel[1] = 0;
        mvprintw(2, x+10 + textCursorPos, sel, instwin);
    }
    else
    {
        editor::copy(selinst->getName(), charBuffer, INST_NAME_SIZE);
        editor::makeUnderlines(charBuffer, INST_NAME_SIZE-1);
        mvprintw(2, x+10, charBuffer, editor::instwin);
    }

    //SELECTED INSTRUMENT
    charBuffer[2] = 0;
    isselected = setInstAttribs(0, 6);
    if(isselected && instobjedit)
        byteString(charBuffer, numBuffer);
    else
        byteString(charBuffer, patternedtr::selinstrument);
    mvprintw(2, x+33, charBuffer, editor::instwin);

    //WAVE INDEX
    charBuffer[4] = 0;
    isselected = setInstAttribs(1,0);
    if(isselected && instobjedit)
        editor::shortString(charBuffer, numBuffer, 4);
    else
        editor::shortString(charBuffer, selinst->getWaveIndex(), 4);
    mvprintw(3, x+9+6, charBuffer, editor::instwin);


    //PULSE INDEX
    isselected = setInstAttribs(2,0);
    if(isselected && instobjedit)
    {
        if(numBuffer != 0xFFFF)
            editor::shortString(charBuffer, numBuffer, 4);
        else
        {
            charBuffer[0]='_';
            charBuffer[1]='_';
            charBuffer[2]='_';
            charBuffer[3]='_';
        }
    }
    else
    {
        if(selinst->getPulseIndex() != 0xFFFF)
            editor::shortString(charBuffer, selinst->getPulseIndex(), 4);
        else
        {
            charBuffer[0]='_';
            charBuffer[1]='_';
            charBuffer[2]='_';
            charBuffer[3]='_';
        }
    }
    mvprintw(4, x+9+6, charBuffer, editor::instwin);

    //FILTER INDEX
    isselected = setInstAttribs(3,0);
    if(isselected && instobjedit)
    {
        if(numBuffer != 0xFFFF)
            editor::shortString(charBuffer, numBuffer, 4);
        else
        {
            charBuffer[0]='_';
            charBuffer[1]='_';
            charBuffer[2]='_';
            charBuffer[3]='_';
        }
    }
    else
    {
        if(selinst->getFilterIndex() != 0xFFFF)
            editor::shortString(charBuffer, selinst->getFilterIndex(), 4);
        else
        {
            charBuffer[0]='_';
            charBuffer[1]='_';
            charBuffer[2]='_';
            charBuffer[3]='_';
        }
    }
    mvprintw(5, x+9+6, charBuffer, editor::instwin);


    displayEnvelope();
}


void instedtr::displayEnvelope()
{
    int x = 11;
    int y = 8;
    int height = editor::WIN_HEIGHT - 4  - y;
    int width = editor::WIN_WIDTH   - 12 - 13 - 11*2;

    int bot = editor::WIN_HEIGHT - 2;
    int div = editor::WIN_WIDTH / 11 - 1;

    attroff(-1);
    for(int i = 0; i < div; i++)
        for(int j = y+1; j < bot; j++)
            mvprintw(j,x+11*i, "           ", editor::instwin);//11 spaces

    attron(A_UNDERLINE);
    for(int i = 0; i < width; i++)
        mvprintw(y, x+i," ",editor::instwin);
    attroff(A_UNDERLINE);
    y++;
    attron(A_BOLD);
    attron(COLOR_PAIR(patternedtr::COL_META_UU));
    mvprintw(y, x+width/2 - 8, "VOLUME-ENVELOPE", editor::instwin);

    unsigned short *volTable = editor::selinst->getVolTable();

    //Calculate total, ignoring jumps (0xFF__)
    float total =0;
    int entries = editor::selinst->numVolEntries();
    for(int i = 0; i < entries; i++)
        if(volTable[i] < 0xFA00)
            total += (volTable[i] & 0xFF);


    attroff(COLOR_PAIR(patternedtr::COL_META_UU));

    if(total < 1)
        return;
    bot--;
    unsigned short px, py, lx=0, ly=0; //temp vars to draw lines
    int acc = 0;
    unsigned char vol;
    for(int i = 0; i < entries; i++)
    {
        vol = (volTable[i] &0xFF00) >> 8;

        if(vol < 0xFB)
        {
            acc += volTable[i]&0xFF;
            px = x + width*(acc/total);
            py = bot - height*(vol/254.0);

            if(i == selvolrow)
            {
                attron(COLOR_PAIR(patternedtr::COL_CMDBAR_S));

                mvprintw(py, px-1, "|#|", editor::instwin);

                if(py < bot)
                {
                    mvprintw(py+1, px-1, "^^^", editor::instwin);
                }
                if(py > y)
                {
                    mvprintw(py-1, px-1, "vvv", editor::instwin);
                }
                attroff(COLOR_PAIR(patternedtr::COL_CMDBAR_S));

            }
            else
            {
                attron(COLOR_PAIR(patternedtr::COL_META_SSS));
                mvprintw(py, px, "o", editor::instwin);
                attroff(COLOR_PAIR(patternedtr::COL_META_SSS));
            }

            px--;
            //draw lines
            if(lx != 0 && px > lx)//the envelope will never be at the left of the screen, okay to use as sentinel
            {
                attron(COLOR_PAIR(patternedtr::COL_META_SSS));
                float dif = px-lx;
                for(int g = 0; g <= dif; g++)
                {
                    mvprintw(ly + (py-ly)*(g/dif), lx+g, ".", editor::instwin);
                }
                attroff(COLOR_PAIR(patternedtr::COL_META_SSS));
            }
            lx = px+2;
            ly = py;

        }
    }

}

void instedtr::displayVol()
{
    attroff(-1);
    unsigned char y;
    unsigned char x;
    unsigned short height;

    y = 2;
    x = 2;
    height = editor::WIN_HEIGHT - 4-1; //-1 for the header

    attron(A_UNDERLINE);
    mvprintw(y++, x, "VOL TBLE|",editor::wavewin);
    unsigned short * volTable = editor::selinst->getVolTable();
    //Print the wave table entries
    bool emptyvisible = true;
    bool lastselected = false;

    int entries = editor::selinst->numVolEntries();

    //If the last entry is visible but not selected, print it dashes
    //otherwise print it with the numbers stored in it


    if(selwavrow == entries && editor::inputwin == editor::volwin)
        lastselected = true;

    entries -= viewportvol; //Put in reference of viewport
    if (entries > height)
    {
        entries = height;
        emptyvisible = false;
    }
    else
        if(lastselected)
            entries++;

    using editor::charBuffer;
    charBuffer[2] = '|';
    charBuffer[3] = 0;
    int i;
    for(i = 0; i < entries; i++)
    {
        setVolAttribs(viewportvol+i, VOLSEG_NUM);
        editor::byteString(charBuffer, viewportvol+i);
        mvprintw(3+i,x, charBuffer, editor::volwin);
    }


    charBuffer[4]='|';
    charBuffer[5]=0;
    for(i = 0; i < entries; i++)
    {
        setVolAttribs(viewportvol+i, VOLSEG_DUR);
        editor::shortString(charBuffer, volTable[viewportvol+i], 4);
        mvprintw(3+i,x+6, charBuffer+2, editor::volwin);

        charBuffer[2] = ' ';
        charBuffer[3] = 0;
        setVolAttribs(viewportvol+i, VOLSEG_VOL);
        mvprintw(3+i,x+3, charBuffer, editor::volwin);
    }


    if(emptyvisible)
    {
        if(!lastselected && i < height)
        {
            editor::byteString(charBuffer + 0, viewportvol + i);
            charBuffer[2] = '|';
            charBuffer[3] = '-';
            charBuffer[4] = '-';
            charBuffer[5] = ' ';
            charBuffer[6] = '-';
            charBuffer[7] = '-';
            charBuffer[8] = '|';
            charBuffer[9] = 0;

            setVolAttribs(viewportvol+i, 2);
            mvprintw(y+i,x, charBuffer);
            charBuffer[5] = 0;

            setVolAttribs(viewportvol+i, VOLSEG_VOL);
            mvprintw(y+i, x+3, charBuffer+3, editor::volwin);

            setVolAttribs(viewportvol+i, VOLSEG_DUR);
            mvprintw(y+i, x+6, charBuffer+3, editor::volwin);
            i++;
        }

        setVolAttribs(entries+1,2);
        charBuffer[2] = '|';
        charBuffer[8]='|';
        for(int j=3; j < 8; j++)
            charBuffer[j] = ' ';
        charBuffer[9]=0;

        while(i < height)
        {
            editor::byteString(charBuffer, viewportvol + i);
            mvprintw(y+i, x, charBuffer, editor::volwin);
            i++;
        }
        attroff(-1);
    }


}

void instedtr::processInput(wint_t in)
{
    if(editor::inputwin == editor::instwin)
        processInputInst(in);    
    else if(editor::inputwin == editor::wavewin)
        processInputWav(in);
    else if(editor::inputwin == editor::volwin)
        processInputVol(in);
    else if(editor::inputwin == editor::pulsewin)
        processInputPulse(in);
    else if(editor::inputwin == editor::filterwin)
        processInputFilter(in);

}


void instedtr::processInputInst(wint_t in)
{
    using editor::song;
    bool ishex = editor::validateHexChar(in);

    if(!instobjedit)
    {
        switch(in)
        {
            case '\n':
                startInstEditing();
                return;
            case KEY_LEFT:
                chgSelInstObj(-1);
                return;
            case KEY_RIGHT:
                chgSelInstObj(1);
                return;
            case KEY_UP:
                chgSelInstRow(-1);
                return;
            case KEY_DOWN:
                chgSelInstRow(1);
                return;
            case KEY_HOME:
                selinstobj = 0;
                chgSelInstObj(0);
                return;
            case KEY_END:
                chgSelInstObj(18); //18 is fine because chgSel does verification anyways
                return;
            case ' ':
                if(selinstrow == 1 && selinstobj == 0)
                {
                    if(editor::song->numWaveEntries() >= editor::selinst->getWaveIndex())
                    {
                        instedtr::selwavrow = editor::selinst->getWaveIndex();
                        chgSelWavRow(0);
                        editor::inputwin = editor::wavewin;
                    }
                }
                return;
        }

    }
    else
    {
        if(in == '\n')
            doneInstEditing();
        else
            instEdit(in);
    }

}

void instedtr::processInputVol(wint_t in)
{
    using editor::song;
    using editor::selinst;
    bool ishex = editor::validateHexChar(in);
    unsigned short entries = selinst->numVolEntries();

    switch(in)
    {
        case KEY_LEFT:
            chgSelVolSeg(-1);
            return;
        case KEY_RIGHT:
            chgSelVolSeg(1);
            return;
        case KEY_UP:
            chgSelVolRow(-1);
            return;
        case KEY_DOWN:
            chgSelVolRow(1);
            return;
        case KEY_PPAGE:
            chgSelVolRow(-8);
            return;
        case KEY_NPAGE:
            chgSelVolRow(8);
            return;
        case KEY_HOME:
            selvolrow = 0;
            chgSelVolRow(0); //updates GUI
            return;
        case KEY_END:
            selvolrow = entries; 
            chgSelVolRow(0); //update GUI
            return;
        case KEY_IC:
            if(entries == 0xFFFF)
                return;
            selinst->insertVolEntry(selvolrow, selinst->getVolEntry(selvolrow));
            return;
        case KEY_DC: 
            if(selvolrow >= entries)
                return;
            if(entries != 1)
                selinst->removeVolEntry(selvolrow);
            chgSelVolRow(0);
            return;
        case ALT_BACKSPACE: 
            if(selvolrow >= entries)
                return;
            if(entries != 1)
                selinst->removeVolEntry(selvolrow);
            chgSelVolRow(-1);
            return;
        case  '\n':
            volclipboard = selinst->getVolEntry(selvolrow);
            chgSelVolRow(1);
            return;
        case ' ':
            if(selvolrow == selinst->numVolEntries())
                selinst->insertVolEntry(selvolrow, volclipboard);
            else
                selinst->setVolEntry(selvolrow,volclipboard);
            chgSelVolRow(1);
            return;
        default:

            if(ishex)
            {
                unsigned char hexnum = editor::charHex(in);
                unsigned short entry = selinst->getVolEntry(selvolrow);
                if(selvolseg == VOLSEG_VOL)
                {
                    unsigned char val = (entry & 0xFF00) >> 8;
                    entry &= 0x00FF;
                    val *= 0x10;
                    //allow FF(jump) if and only if not first row
                    if(val == 0xF0 && hexnum == 0xF && selvolrow == 0)
                        val = 0xFE;
                    else
                        val += hexnum;
                    entry |= ((short(val)) << 8);
                }
                else if(selvolseg == VOLSEG_DUR && selvolrow > 0)
                {
                    unsigned char val = (entry & 0x00FF);
                    entry &= 0xFF00;
                    val *= 0x10;
                    val += hexnum;
                    entry |= val;
                }

                if(selvolrow == selinst->numVolEntries())
                    selinst->insertVolEntry(selvolrow, entry);
                else
                    selinst->setVolEntry(selvolrow,entry);
            }


    }





}
void instedtr::processInputWav(wint_t in)
{
    using editor::song;
    bool ishex = editor::validateHexChar(in);
    unsigned short entries = song->numWaveEntries();
    switch(in)
    {
        case KEY_LEFT:
            chgSelWavSeg(-1);
            return;
        case KEY_RIGHT:
            chgSelWavSeg(1);
            return;
        case KEY_UP:
            chgSelWavRow(-1);
            return;
        case KEY_DOWN:
            chgSelWavRow(1);
            return;
        case KEY_PPAGE:
            chgSelWavRow(-8);
            return;
        case KEY_NPAGE:
            chgSelWavRow(8);
            return;
        case KEY_HOME:
            selwavrow = 0;
            chgSelWavRow(0); //updates GUI
            return;
        case KEY_END:
            selwavrow = entries; 
            chgSelWavRow(0); //update GUI
            return;
        case KEY_IC:
            if(entries == 0xFFFF)
                return;

            if(isJumpFunc_Volatile(song->getWaveEntry(selwavrow)))
                song->insertWaveEntry(selwavrow, 0);
            else
                song->insertWaveEntry(selwavrow, song->getWaveEntry(selwavrow));
            return;
        case KEY_DC: 

            if(selwavrow >= entries)
                return;
            if(entries != 0)
                song->removeWaveEntry(selwavrow);
            chgSelWavRow(0);
            return;
        case ALT_BACKSPACE: 
            if(selwavrow >= entries)
                return;
            if(entries != 0)
                song->removeWaveEntry(selwavrow);
            chgSelWavRow(-1);
            return;

        case  '\n':
            waveclipboard = song->getWaveEntry(selwavrow);
            chgSelWavRow(1);
            return;
        case ' ':
            if(selwavrow == song->numWaveEntries())
                song->insertWaveEntry(selwavrow, waveclipboard);
            else
                song->setWaveEntry(selwavrow,waveclipboard);
            chgSelWavRow(1);
            return;
        case 'n':
        case 'N':
            {
                unsigned short entry = song->getWaveEntry(selwavrow);
                char right = (entry & 0xFF);
                right = -right;
                entry = (entry & 0xFF00) | (unsigned char)right;
                song->setWaveEntry(selwavrow, entry);
            }
            return;
        default:
            if(ishex)
            {
                char hexnum = editor::charHex(in);
                unsigned short entry = song->getWaveEntry(selwavrow);
                if(selwavseg == WAVSEG_WAVE)
                {
                    unsigned char val = (entry & 0xFF00) >> 8;
                    entry &= 0x00FF;
                    val *= 0x10;
                    val += hexnum;
                    entry |= ((short(val)) << 8);
                }
                else if(selwavseg == WAVSEG_TONE)
                {
                    unsigned char val = (entry & 0x00FF);
                    entry &= 0xFF00;
                    val *= 0x10;
                    val += hexnum;
                    entry |= val;
                }

                if(selwavrow == song->numWaveEntries())
                    song->insertWaveEntry(selwavrow, entry);
                else
                    song->setWaveEntry(selwavrow,entry);
            }
    }



}

void instedtr::processInputPulse(wint_t in)
{
    using editor::song;
    bool ishex = editor::validateHexChar(in);
    unsigned short entries = song->numPulseEntries();
    switch(in)
    {
        case KEY_LEFT:
            chgSelPulSeg(-1);
            return;
        case KEY_RIGHT:
            chgSelPulSeg(1);
            return;
        case KEY_UP:
            chgSelPulRow(-1);
            return;
        case KEY_DOWN:
            chgSelPulRow(1);
            return;
        case KEY_PPAGE:
            chgSelPulRow(-8);
            return;
        case KEY_NPAGE:
            chgSelPulRow(8);
            return;
        case KEY_HOME:
            selpulrow = 0;
            chgSelPulRow(0); //updates GUI
            return;
        case KEY_END:
            selpulrow = entries; 
            chgSelPulRow(0); //update GUI
            return;
        case KEY_IC:
            if(entries == 0xFFFF)
                return;

            if(isJumpFunc_Volatile(song->getPulseEntry(selpulrow)))
                song->insertPulseEntry(selpulrow, 0);
            else
                song->insertPulseEntry(selpulrow, song->getPulseEntry(selpulrow));
            return;
        case KEY_DC: 
            if(selpulrow >= entries)
                return;
            if(entries != 0)
                song->removePulseEntry(selpulrow);
            chgSelPulRow(0);
            return;
        case ALT_BACKSPACE:
            if(selpulrow >= entries)
                return;
            if(entries != 0)
                song->removePulseEntry(selpulrow);
            chgSelPulRow(-1);
            return;
        case  '\n':
            pulseclipboard = song->getPulseEntry(selpulrow);
            chgSelPulRow(1);
            return;
        case ' ':
            if(selpulrow == song->numPulseEntries())
                song->insertPulseEntry(selpulrow, pulseclipboard);
            else
                song->setPulseEntry(selpulrow,pulseclipboard);
            chgSelPulRow(1);
            return;
        case 'n':
        case 'N':
            {
                unsigned short entry = song->getPulseEntry(selpulrow);
                char left = (entry & 0xFF00);
                if(left < 0xE000)
                {
                    if(left >= 0x7000)
                    {
                        entry += 0x2000;
                        entry = -entry;
                    }
                    else
                    {
                        entry = -entry;
                        entry -= 0x2000;
                    }
                    song->setPulseEntry(selpulrow, entry);
                }

            }
            return;
        default:
            if(ishex)
            {
                char hexnum = editor::charHex(in);
                unsigned short entry = song->getPulseEntry(selpulrow);
                if(selpulseg == 0)
                {
                    unsigned char val = (entry & 0xFF00) >> 8;
                    entry &= 0x00FF;
                    val *= 0x10;
                    val += hexnum;
                    entry |= ((short(val)) << 8);
                }
                else if(selpulseg == 1)
                {
                    unsigned char val = (entry & 0x00FF);
                    entry &= 0xFF00;
                    val *= 0x10;
                    val += hexnum;
                    entry |= val;
                }

                if(selpulrow == song->numPulseEntries())
                    song->insertPulseEntry(selpulrow, entry);
                else
                    song->setPulseEntry(selpulrow,entry);
            }
    }



}



void instedtr::processInputFilter(wint_t in)
{
    using editor::song;
    bool ishex = editor::validateHexChar(in);
    unsigned short entries = song->numFilterEntries();
    switch(in)
    {
        case KEY_LEFT:
            chgSelFltSeg(-1);
            return;
        case KEY_RIGHT:
            chgSelFltSeg(1);
            return;
        case KEY_UP:
            chgSelFltRow(-1);
            return;
        case KEY_DOWN:
            chgSelFltRow(1);
            return;
        case KEY_PPAGE:
            chgSelFltRow(-8);
            return;
        case KEY_NPAGE:
            chgSelFltRow(8);
            return;
        case KEY_HOME:
            selpulrow = 0;
            chgSelFltRow(0); //updates GUI
            return;
        case KEY_END:
            selfltrow = entries; 
            chgSelFltRow(0); //update GUI
            return;
        case KEY_IC:
            if(entries == 0xFFFF)
                return;

            if(isJumpFunc_Volatile(song->getFilterEntry(selfltrow)))
                song->insertFilterEntry(selfltrow, 0);
            else
                song->insertFilterEntry(selfltrow, song->getFilterEntry(selfltrow));
            return;
        case KEY_DC: 
            if(selfltrow >= entries)
                return;
            if(entries != 0)
                song->removeFilterEntry(selfltrow);
            chgSelFltRow(0);
            return;
        case ALT_BACKSPACE:
            if(selfltrow >= entries)
                return;
            if(entries != 0)
                song->removeFilterEntry(selfltrow);
            chgSelFltRow(-1);
            return;
        case  '\n':
            filterclipboard = song->getFilterEntry(selfltrow);
            chgSelFltRow(1);
            return;
        case ' ':
            if(selfltrow == song->numFilterEntries())
                song->insertFilterEntry(selfltrow, filterclipboard);
            else
                song->setFilterEntry(selfltrow,filterclipboard);
            chgSelFltRow(1);
            return;
        case 'n':
        case 'N':
            {
                unsigned short entry = song->getFilterEntry(selfltrow);
                char left = (entry & 0xFF00);
                if(left < 0xE000)
                {
                    if(left >= 0x7000)
                    {
                        entry += 0x2000;
                        entry = -entry;
                    }
                    else
                    {
                        entry = -entry;
                        entry -= 0x2000;
                    }
                    song->setFilterEntry(selfltrow, entry);
                }

            }
            return;
        default:
            if(ishex)
            {
                char hexnum = editor::charHex(in);
                unsigned short entry = song->getFilterEntry(selfltrow);
                if(selfltseg == 0)
                {
                    unsigned char val = (entry & 0xFF00) >> 8;
                    entry &= 0x00FF;
                    val *= 0x10;
                    val += hexnum;
                    entry |= ((short(val)) << 8);
                }
                else if(selfltseg == 1)
                {
                    unsigned char val = (entry & 0x00FF);
                    entry &= 0xFF00;
                    val *= 0x10;
                    val += hexnum;
                    entry |= val;
                }

                if(selfltrow == song->numFilterEntries())
                    song->insertFilterEntry(selfltrow, entry);
                else
                    song->setFilterEntry(selfltrow,entry);
            }
    }



}
bool isFuncEntry(const unsigned short &entry)
{
    return (entry & 0xF000) == 0xF000;
}

bool isJumpEntry(const unsigned short &entry)
{
    unsigned short func = (entry & 0xFF00);
    switch(func)
    {
        case 0xFF00:
        case 0xFC00:
        case 0xFE00:
            return true;
    }
    return false;
}

bool instedtr::setInstAttribs(unsigned char instrow, unsigned char instobj)
{
    attroff(-1);
    if(editor::inputwin == editor::instwin)
    {
        attron(A_BOLD);
        if(instrow == selinstrow && instobj == selinstobj)
        {

            if(instobjedit)
                attron(COLOR_PAIR(patternedtr::COL_META_SSSE));
            else
                attron(COLOR_PAIR(patternedtr::COL_META_SSS));
            return true;
        }
        else
            attron(COLOR_PAIR(patternedtr::COL_META_SU));
    }
    else
        if(instrow == selinstrow && instobj == selinstobj)
            attron(COLOR_PAIR(patternedtr::COL_META_US));
        else
            attron(COLOR_PAIR(patternedtr::COL_META_UU));
    return false;
}

void instedtr::setVolAttribs(unsigned char volrow, unsigned char volseg)
{
    attroff(-1);
    unsigned short entry;
    bool isFunc= false;
    bool isJump = false;
    if(volrow < editor::selinst->numVolEntries())
    {
        entry = editor::selinst->getVolEntry(volrow);
        isFunc = isFuncEntry(entry);
        if(isFunc)
            isJump = isJumpEntry(entry);
    }

    if(editor::inputwin == editor::volwin)
    {
        if(volrow == selvolrow)
        {
            attron(A_BOLD);
            if(volseg == selvolseg)
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSS));
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSU));
        }
        else
        {
            if(volrow > editor::selinst->numVolEntries())
                attron(COLOR_PAIR(patternedtr::COL_TABLE_UU));
            else
                if(isFunc)
                {
                    if(isJump)
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_JUMP));
                    else
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_FUNC));
                }
                else
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_SU));

        }
    }
    else
    {
        if(volrow == selvolrow)
            attron(COLOR_PAIR(patternedtr::COL_TABLE_US));
        else
        {
            if(isJump)
                attron(COLOR_PAIR(patternedtr::COL_TABLE_UU_JUMP));
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_UU));
        }
    }
}


void instedtr::setWaveAttribs(unsigned short waverow, unsigned char waveseg)
{
    attroff(-1);
    unsigned short entry;
    bool isFunc = false;
    bool isJump = false;
    if(waverow < editor::song->numWaveEntries())
    {
        entry = editor::song->getWaveEntry(waverow);
        isFunc = isFuncEntry(entry);
        if(isFunc)
            isJump = isJumpEntry(entry);
    }

    if(editor::inputwin == editor::wavewin)
    {
        if(waverow == selwavrow)
        {
            attron(A_BOLD);
            if(waveseg == selwavseg)
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSS));
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSU));
        }
        else
            if(waverow > editor::song->numWaveEntries())
                attron(COLOR_PAIR(patternedtr::COL_TABLE_US));
            else
                if(isFunc)
                {
                    if(isJump)
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_JUMP));
                    else
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_FUNC));
                }
                else
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_SU));
    }
    else
        if(waverow == selwavrow)
            attron(COLOR_PAIR(patternedtr::COL_TABLE_US));
        else
            if(isFunc && (entry & 0xFF00) != 0xF400) //F4 (finetune) consumes a tick
            {
                if(isJump)
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_UU_JUMP));
                else
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_UU_FUNC));
            }
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_UU));
}


void instedtr::setPulseAttribs(unsigned short pulserow, unsigned char pulseseg)
{
    attroff(-1);

    unsigned short entry;
    bool isFunc = false;
    bool isJump = false;
    if(pulserow < editor::song->numPulseEntries())
    {
        entry = editor::song->getPulseEntry(pulserow);
        isFunc = isFuncEntry(entry);
        if(isFunc)
            isJump = isJumpEntry(entry);
    }

    if(editor::inputwin == editor::pulsewin)
    {
        if(pulserow == selpulrow)
        {
            attron(A_BOLD);
            if(pulseseg == selpulseg)
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSS));
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSU));
        }
        else
            if(pulserow > editor::song->numPulseEntries())
                attron(COLOR_PAIR(patternedtr::COL_TABLE_US));
            else
                if(isFunc)
                {
                    if(isJump)
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_JUMP));
                    else
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_FUNC));
                }
                else
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_SU));
    }
    else
    {
        if(pulserow == selpulrow)
            attron(COLOR_PAIR(patternedtr::COL_TABLE_US));
        else
            if(isFunc)
            {
                if(isJump)
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_UU_JUMP));
                else
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_UU_FUNC));
            }
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_UU));
    }
}


void instedtr::setFilterAttribs(unsigned short filterrow, unsigned char filterseg)
{
    attroff(-1);

    unsigned short entry;
    bool isFunc = false;
    bool isJump = false;
    if(filterrow < editor::song->numFilterEntries())
    {
        entry = editor::song->getFilterEntry(filterrow);
        isFunc = isFuncEntry(entry);
        if(isFunc)
            isJump = isJumpEntry(entry);
    }

    if(editor::inputwin == editor::filterwin)
    {
        if(filterrow == selfltrow)
        {
            attron(A_BOLD);
            if(filterseg == selfltseg)
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSS));
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_SSU));
        }
        else
            if(filterrow > editor::song->numFilterEntries())
                attron(COLOR_PAIR(patternedtr::COL_TABLE_US));
            else
                if(isFunc)
                {
                    if(isJump)
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_JUMP));
                    else
                        attron(COLOR_PAIR(patternedtr::COL_TABLE_SU_FUNC));
                }
                else
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_SU));
    }
    else
        if(filterrow == selfltrow)
            attron(COLOR_PAIR(patternedtr::COL_TABLE_US));
        else
            if(isFunc)
            {
                if(isJump)
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_UU_JUMP));
                else
                    attron(COLOR_PAIR(patternedtr::COL_TABLE_UU_FUNC));
            }
            else
                attron(COLOR_PAIR(patternedtr::COL_TABLE_UU));
}


void instedtr::startInstEditing()
{
    if(selinstrow == 0)
    {
        if(selinstobj == 6)
        {
            instobjedit = true;
            editor::numBuffer = patternedtr::selinstrument;
        }
        else if(selinstobj == 0)
        {
            //NEW INST
            patternedtr::newInstrument();
        } else if(selinstobj == 1)
        {
            //CLONE ISNT
            patternedtr::cloneInstrument(patternedtr::selinstrument);
        } else if(selinstobj == 2)
        {
            //REMOVE INST
            patternedtr::removeInstrument(patternedtr::selinstrument);
        } else if(selinstobj == 3)
        {
            //DOWN
            if(patternedtr::selinstrument!= 0)
                patternedtr::selinstrument--;
            editor::selinst = editor::song->getInstrument(patternedtr::selinstrument);
        } else if(selinstobj == 4)
        {
            //UP
            if(patternedtr::selinstrument < editor::song->numInstruments()-1)
                patternedtr::selinstrument++;
            editor::selinst = editor::song->getInstrument(patternedtr::selinstrument);

        }
        else if(selinstobj == 5)
        {
            editor::copy(editor::selinst->getName(), editor::charInputBuffer, INST_NAME_SIZE);
            editor::textCursorPos = strlen(editor::selinst->getName());
            if(editor::textCursorPos > INST_NAME_SIZE-2)
                editor::textCursorPos = INST_NAME_SIZE-2;
            instobjedit = true;
        }
    }
    else if(selinstrow == 1)
    {
        if(selinstobj == 0)
        {
            editor::numBuffer = editor::selinst->getWaveIndex();
            instobjedit = true;
        }
    }
    else if(selinstrow == 2)
    {
        if(selinstobj == 0)
        {
            editor::numBuffer = editor::selinst->getPulseIndex();
            instobjedit = true;
        }
    }
    else if(selinstrow == 3)
    {
        if(selinstobj == 0)
        {
            editor::numBuffer = editor::selinst->getFilterIndex();
            instobjedit = true;
        }
    }
}

void instedtr::instEdit(wint_t in)
{
    using namespace editor;
    bool ishex = editor::validateHexChar(in);
    bool isarrow = (in == KEY_LEFT||in==KEY_RIGHT||in==KEY_UP||in==KEY_DOWN);
    bool spinnervalid = ishex || isarrow;
    char hexnum = charHex(in);

    if(selinstrow == 0)
    {
        //Instrument Name
        if(selinstobj == 5)
        {
            if(isarrow)
            {
                if(in == KEY_LEFT)
                {
                    if(textCursorPos > 0)
                        textCursorPos--;
                }
                else if(in == KEY_RIGHT)
                {
                    int length = strlen(charInputBuffer);

                    if(textCursorPos < length)
                        if(textCursorPos < INST_NAME_SIZE-2)
                            textCursorPos++;
                }
            }

            else if(in == ALT_BACKSPACE)
            {
                if(textCursorPos > 0)
                {
                    int length = INST_NAME_SIZE;
                    for(int i = textCursorPos; i < length; i++)
                        charInputBuffer[i-1] = charInputBuffer[i];//this is okay because charInputBuffer is larger than INST_NAME_SIZE
                    textCursorPos--;
                }
            }
            else if(in == KEY_DC)
            {
                int length = strlen(charInputBuffer);
                for(int i = textCursorPos+1; i <= length; i++)
                    charInputBuffer[i-1] = charInputBuffer[i];//this is okay because charInputBuffer is larger than INST_NAME_SIZE
                if(textCursorPos >= length-1 && textCursorPos > 0)
                    textCursorPos--;
            }
            else if(in == KEY_HOME)
                textCursorPos = 0;
            else if(in == KEY_END)
            {
                int length = strlen(charInputBuffer);

                if(length < INST_NAME_SIZE-1)
                    textCursorPos = length;
                else textCursorPos = INST_NAME_SIZE - 2;
            }
            else
            {
                if(in <= 'z' && in >= ' ')
                {
                    int length = INST_NAME_SIZE;
                    for(int i = length-2; i > textCursorPos; i--)
                        charInputBuffer[i] = charInputBuffer[i-1];

                    charInputBuffer[textCursorPos] = in;
                    charInputBuffer[length-1] = 0;
                    if(textCursorPos < INST_NAME_SIZE-2)
                        textCursorPos++;

                }
            }
        }
        //Instrument spinner
        else if(selinstobj == 6)
        {
            switch(in)
            {
                case KEY_UP:
                    numBuffer++;
                    break;
                case KEY_LEFT:
                    numBuffer -= 8;
                    break;
                case KEY_DOWN:
                    numBuffer--;
                    break;
                case KEY_RIGHT:
                    numBuffer += 8;
                    break;
                case KEY_END:
                    numBuffer = 0;
                    break;
                case KEY_HOME:
                    numBuffer = song->numInstruments()-1;
                    break;
                case KEY_DC:
                    numBuffer /= 0x10;
                    break;
                default:
                    if(ishex)
                    {
                        numBuffer *= 0x10;
                        numBuffer += hexnum;
                        numBuffer &= 0xFF;
                    }

            }
            if(numBuffer >= song->numInstruments())
            {
                numBuffer = song->numInstruments()-1;
            }
            else if(numBuffer < 0)
                numBuffer = 0;
        }


    }
    else if(selinstrow == 1)
    {
        //Wave parameter
        if(selinstobj == 0)
        {
            switch(in)
            {
                case KEY_UP:
                    numBuffer++;
                    break;
                case KEY_LEFT:
                    numBuffer -= 8;
                    break;
                case KEY_DOWN:
                    numBuffer--;
                    break;
                case KEY_RIGHT:
                    numBuffer += 8;
                    break;
                case KEY_END:
                    numBuffer = 0;
                    break;
                case KEY_HOME:
                    numBuffer = song->numWaveEntries()-1;
                    break;
                case KEY_DC:
                    numBuffer /= 0x10;
                    break;
                default:
                    if(ishex)
                    {
                        numBuffer *= 0x10;
                        if(numBuffer > editor::song->numWaveEntries())
                        {
                            //chop off digits until it isnt greater
                            for(int i = 3; (numBuffer %= int(std::pow(0x10,i))) > editor::song->numWaveEntries(); i--);

                        }
                        numBuffer += hexnum;
                    }

            }

            if(numBuffer > editor::song->numWaveEntries())
                for(int i = 3; (numBuffer %= int(std::pow(0x10,i))) > editor::song->numWaveEntries(); i--);
            if(numBuffer < 0) //not possible btw
                numBuffer = 0;
        }
    }
    else if(selinstrow == 2)
    {
        //Pulse  parameter
        if(selinstobj == 0)
        {
            switch(in)
            {
                case KEY_UP:
                    numBuffer++;
                    break;
                case KEY_LEFT:
                    numBuffer -= 8;
                    break;
                case KEY_DOWN:
                    numBuffer--;
                    break;
                case KEY_RIGHT:
                    numBuffer += 8;
                    break;
                case KEY_END:
                    numBuffer = 0;
                    break;
                case KEY_HOME:
                    numBuffer = song->numPulseEntries()-1;
                    break;
                case KEY_DC:
                case ALT_BACKSPACE:
                case ' ':
                    numBuffer = 0xFFFF;
                    break;
                default:
                    if(ishex)
                    {
                        numBuffer *= 0x10;
                        if(numBuffer > editor::song->numPulseEntries())
                        {
                            //chop off digits until it isnt greater
                            for(int i = 3; (numBuffer %= int(std::pow(0x10,i))) > editor::song->numPulseEntries(); i--);

                        }
                        numBuffer += hexnum;
                    }

            }

            if(numBuffer > editor::song->numPulseEntries() && numBuffer != 0xFFFF)
                for(int i = 3; (numBuffer %= int(std::pow(0x10,i))) > editor::song->numPulseEntries(); i--);
            if(numBuffer < 0) //not possible btw
                numBuffer = 0;
        }
    }
    else if(selinstrow == 3)
    {
        //FILTER index
        if(selinstobj == 0)
        {
            switch(in)
            {
                case KEY_UP:
                    numBuffer++;
                    break;
                case KEY_LEFT:
                    numBuffer -= 8;
                    break;
                case KEY_DOWN:
                    numBuffer--;
                    break;
                case KEY_RIGHT:
                    numBuffer += 8;
                    break;
                case KEY_END:
                    numBuffer = 0;
                    break;
                case KEY_HOME:
                    numBuffer = song->numFilterEntries()-1;
                    break;
                case KEY_DC:
                case ALT_BACKSPACE:
                case ' ':
                    numBuffer = 0xFFFF;
                    break;
                default:
                    if(ishex)
                    {
                        numBuffer *= 0x10;
                        if(numBuffer > editor::song->numFilterEntries())
                        {
                            //chop off digits until it isnt greater
                            for(int i = 3; (numBuffer %= int(std::pow(0x10,i))) > editor::song->numFilterEntries(); i--);

                        }
                        numBuffer += hexnum;
                    }
            }

            if(numBuffer > editor::song->numFilterEntries() && numBuffer != 0xFFFF)
                for(int i = 3; (numBuffer %= int(std::pow(0x10,i))) > editor::song->numFilterEntries(); i--);
            if(numBuffer < 0) //not possible btw
                numBuffer = 0;
        }
    }



}

void instedtr::doneInstEditing()
{
    instobjedit = false;
    if(selinstrow == 0)
    {
        if(selinstobj == 5)
        {
            editor::copy(editor::charInputBuffer,editor::selinst->getName(), INST_NAME_SIZE);
        }
        else if(selinstobj == 6)//spinner
        {
            patternedtr::selinstrument = editor::numBuffer;
            editor::selinst = editor::song->getInstrument(patternedtr::selinstrument);

        }
    }
    else if(selinstrow == 1)
    {
        if(selinstobj == 0)
        {
            editor::selinst->setWaveIndex(editor::numBuffer);
            if(editor::song->numWaveEntries() >= editor::numBuffer)
            {
                instedtr::selwavrow = editor::numBuffer;
                chgSelWavRow(0);
            }
        }
    }
    else if(selinstrow == 2)
    {
        if(selinstobj == 0)
        {
            editor::selinst->setPulseIndex(editor::numBuffer);
            if(editor::song->numPulseEntries() >= editor::numBuffer)
            {
                instedtr::selpulrow = editor::numBuffer;
                chgSelPulRow(0);
            }
        }
    }
    else if(selinstrow == 3)
    {
        if(selinstobj == 0)
        {
            editor::selinst->setFilterIndex(editor::numBuffer);
            if(editor::song->numFilterEntries() >= editor::numBuffer)
            {
                instedtr::selfltrow = editor::numBuffer;
                chgSelFltRow(0);
            }
        }
    }


}







