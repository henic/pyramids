// --------------------------------------------------------------------
// configuration.h
// --------------------------------------------------------------------

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "configuration_typedef.h"

// --------------------------------------------------------------------
#define Default_Ini_File_Name "pyramids.ini"

// --------------------------------------------------------------------
void Configuration_Save (
            const CONFIGURATION_USERDEF& Configuration,
            const QString& filename);

void Configuration_Load (
            CONFIGURATION_USERDEF& Configuration,
            const QString& filename,
            const bool Print = false);

#endif // CONFIGURATION_H
