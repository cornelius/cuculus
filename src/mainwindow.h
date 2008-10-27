/*
 * cuculus.h
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <kxmlguiwindow.h>

#include "ui_prefs_base.h"

class CuculusView;
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
class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT
  public:
    /**
     * Default Constructor
     */
    MainWindow();

    /**
     * Default Destructor
     */
    virtual ~MainWindow();

  private slots:
    void optionsPreferences();

  private:
    void setupActions();

  private:
    CuculusView *m_view;
    Ui::prefs_base ui_prefs_base;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif
