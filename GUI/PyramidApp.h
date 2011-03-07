/***************************************************************
 * Name:      PyramidApp.h
 * Purpose:   Defines Application Class
 * Author:    Marc Burns (m4burns@uwaterloo.ca)
 * Created:   2011-03-07
 * Copyright: Marc Burns (convextech.ca)
 * License:
 **************************************************************/

#ifndef PYRAMIDAPP_H
#define PYRAMIDAPP_H

#include <wx/app.h>

class PyramidApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // PYRAMIDAPP_H
