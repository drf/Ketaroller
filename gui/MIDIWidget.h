/*
    Copyright (c) 2011 <copyright holder> <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef MIDIWIDGET_H
#define MIDIWIDGET_H

#include <QtGui/QWidget>
#include <BctOutputDevice.h>

namespace Ui {
    class MIDIWidget;
}


class MIDIWidget : public QWidget
{
    Q_OBJECT
public:
    MIDIWidget(const QHash< int, ModelDescription > &availableModels, BctOutputDevice *device, QWidget *parent = 0);
    virtual ~MIDIWidget();

    void map();
    void unmap();

private slots:
    void onModelBoxChanged(int);
    void onParamBoxChanged(int);
    void onCCNumberChanged(int);
    void kill(bool);

private:
    Ui::MIDIWidget *m_ui;
    BctOutputDevice *m_device;
    QHash< int, ModelDescription > m_availableModels;
    int m_lastCC;
};

#endif // MIDIWIDGET_H
