#include "cuculus.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KDE/KLocale>

static const char description[] =
    I18N_NOOP("A KDE 4 Application");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("cuculus", 0, ki18n("cuculus"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2007 Cornelius Schumacher"), KLocalizedString(), 0, "schumacher@kde.org");
    about.addAuthor( ki18n("Cornelius Schumacher"), KLocalizedString(), "schumacher@kde.org" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    cuculus *widget = new cuculus;

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(cuculus);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            //cuculus *widget = new cuculus;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                //cuculus *widget = new cuculus;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
