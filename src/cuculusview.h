/*
 * cuculusview.h
 *
 * Copyright (C) 2007 Cornelius Schumacher <schumacher@kde.org>
 */
#ifndef CUCULUSVIEW_H
#define CUCULUSVIEW_H

#include <QtGui/QWidget>

#include "ui_cuculusview_base.h"

class QPainter;
class KUrl;

/**
 * This is the main view class for cuculus.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author Cornelius Schumacher <schumacher@kde.org>
 * @version 0.1
 */

class cuculusView : public QWidget, public Ui::cuculusview_base
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    cuculusView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~cuculusView();

private:
    Ui::cuculusview_base ui_cuculusview_base;

signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

private slots:
    void switchColors();
    void settingsChanged();
};

#endif // cuculusVIEW_H