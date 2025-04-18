﻿// SPDX-FileCopyrightText: Copyright (c) Kitware Inc.
// SPDX-FileCopyrightText: Copyright (c) Sandia Corporation
// SPDX-License-Identifier: BSD-3-Clause

// self includes
#include "igwColorChooserButton.h"

#include "cassert"

// Qt includes
#include <QColorDialog>
#include <QPainter>
#include <QResizeEvent>

//-----------------------------------------------------------------------------
igwColorChooserButton::igwColorChooserButton(QWidget* p)
  : QToolButton(p)
  , ShowAlphaChannel(false)
{
  this->Color[0] = 0.0;
  this->Color[1] = 0.0;
  this->Color[2] = 0.0;
  this->Color[3] = 1.0;
  this->IconRadiusHeightRatio = 0.75;
  this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  this->connect(this, SIGNAL(clicked()), SLOT(chooseColor()));
}

//-----------------------------------------------------------------------------
QColor igwColorChooserButton::chosenColor() const
{
  QColor color;
  color.setRgbF(this->Color[0], this->Color[1], this->Color[2], this->Color[3]);

  return color;
}

//-----------------------------------------------------------------------------
QVariantList igwColorChooserButton::chosenColorRgbF() const
{
  QVariantList val;
  val << this->Color[0] << this->Color[1] << this->Color[2];
  return val;
}

//-----------------------------------------------------------------------------
QVariantList igwColorChooserButton::chosenColorRgbaF() const
{
  QVariantList val;
  val << this->Color[0] << this->Color[1] << this->Color[2] << this->Color[3];
  return val;
}

//-----------------------------------------------------------------------------
void igwColorChooserButton::setChosenColor(const QColor& color)
{
  if (color.isValid())
  {
    QVariantList val;
    val << color.redF() << color.greenF() << color.blueF() << color.alphaF();
    this->setChosenColorRgbaF(val);
  }
}

//-----------------------------------------------------------------------------
void igwColorChooserButton::setChosenColorRgbF(const QVariantList& val)
{
  assert(val.size() == 3);
  QColor color;
  color.setRgbF(val[0].toDouble(), val[1].toDouble(), val[2].toDouble());

  if (color.isValid())
  {
    if (val[0].toDouble() != this->Color[0] || val[1].toDouble() != this->Color[1] ||
      val[2].toDouble() != this->Color[2])
    {
      this->Color[0] = val[0].toDouble();
      this->Color[1] = val[1].toDouble();
      this->Color[2] = val[2].toDouble();

      this->setIcon(this->renderColorSwatch(color));
      Q_EMIT this->chosenColorChanged(color);
    }

    Q_EMIT this->validColorChosen(color);
  }
}

//-----------------------------------------------------------------------------
void igwColorChooserButton::setChosenColorRgbaF(const QVariantList& val)
{
  assert(val.size() == 4);
  QColor color;
  color.setRgbF(val[0].toDouble(), val[1].toDouble(), val[2].toDouble(), val[3].toDouble());

  if (color.isValid())
  {
    if (val[0].toDouble() != this->Color[0] || val[1].toDouble() != this->Color[1] ||
      val[2].toDouble() != this->Color[2] || val[3].toDouble() != this->Color[3])
    {
      this->Color[0] = val[0].toDouble();
      this->Color[1] = val[1].toDouble();
      this->Color[2] = val[2].toDouble();
      this->Color[3] = val[3].toDouble();

      this->setIcon(this->renderColorSwatch(color));
      Q_EMIT this->chosenColorChanged(color);
    }
    Q_EMIT this->validColorChosen(color);
  }
}

//-----------------------------------------------------------------------------
QIcon igwColorChooserButton::renderColorSwatch(const QColor& color)
{
  int radius = qRound(this->height() * this->IconRadiusHeightRatio);
  if (radius <= 10)
  {
    radius = 10;
  }

  QPixmap pix(radius, radius);
  pix.fill(QColor(0, 0, 0, 0));

  QPainter painter(&pix);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setBrush(QBrush(color));
  painter.drawRect(1, 1, radius - 2, radius - 2);
  painter.end();
  QIcon ret(pix);

  QPixmap pix2x(radius * 2, radius * 2);
  // Add a high-dpi version, just like a @2x.png file
  pix2x.setDevicePixelRatio(2.0);
  pix2x.fill(QColor(0, 0, 0, 0));

  QPainter painter2x(&pix2x);
  painter2x.setRenderHint(QPainter::Antialiasing, true);
  painter2x.setBrush(QBrush(color));
  painter2x.drawEllipse(2, 2, radius - 4, radius - 4);
  painter2x.end();

  ret.addPixmap(pix2x);
  return ret;
}

//-----------------------------------------------------------------------------
void igwColorChooserButton::chooseColor()
{
  QColorDialog::ColorDialogOptions opts = QColorDialog::DontUseNativeDialog;
  if (this->ShowAlphaChannel)
  {
    opts |= QColorDialog::ShowAlphaChannel;
  }

  QColor color = QColorDialog::getColor(this->chosenColor(), this, tr("Set Color"), opts);
  this->setChosenColor(color);
}

//-----------------------------------------------------------------------------
void igwColorChooserButton::resizeEvent(QResizeEvent* rEvent)
{
  (void)rEvent;

  QColor color = this->chosenColor();
  this->setIcon(this->renderColorSwatch(color));
}
