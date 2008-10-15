/*
 * cuculusview.cpp
 *
 * Copyright (C) 2008 Cornelius Schumacher <schumacher@kde.org>
 */

#include "cuculusview.h"

#include "settings.h"

#include <klocale.h>

#include <QtGui>

CuculusView::CuculusView(QWidget *)
{
  QBoxLayout *topLayout = new QVBoxLayout( this );
  
  QLabel *label = new QLabel( "Hallo" );
  topLayout->addWidget( label );

  settingsChanged();
  setAutoFillBackground(true);
}

CuculusView::~CuculusView()
{
}

void CuculusView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = Settings::col_background();
    Settings::setCol_background( Settings::col_foreground() );
    Settings::setCol_foreground( color );

    settingsChanged();
}

void CuculusView::settingsChanged()
{
}

#include "cuculusview.moc"
