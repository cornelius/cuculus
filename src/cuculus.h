/*
 * cuculus.h
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */
#ifndef CUCULUS_H
#define CUCULUS_H


#include <kxmlguiwindow.h>

#include "ui_prefs_base.h"

class cuculusView;
class QPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for cuculus.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Cornelius Schumacher <schumacher@kde.org>
 * @version 0.1
 */
class cuculus : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    cuculus();

    /**
     * Default Destructor
     */
    virtual ~cuculus();

private slots:
    void fileNew();
    void optionsPreferences();

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    cuculusView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _CUCULUS_H_
