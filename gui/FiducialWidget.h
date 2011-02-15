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


#ifndef FIDUCIALWIDGET_H
#define FIDUCIALWIDGET_H

#include <QtGui/QWidget>
#include <QHash>

#include <BctOutputDevice.h>

namespace Ui {
    class FiducialWidget;
}

namespace KetaRoller {
    class InputDevice;
    class OutputDevice;
    class InputPort;
    class OutputPort;
}


class FiducialWidget : public QWidget
{
    Q_OBJECT
public:
    FiducialWidget(const QHash< int, ModelDescription > &availableModels,
                   KetaRoller::InputDevice *inDevice, BctOutputDevice *outDevice,
                   int fiducialId, QWidget* parent);
    virtual ~FiducialWidget();

    void unmapFiducial();
    void mapFiducial();

private slots:
    void onAngleBoxChanged(int);
    void onPositionBoxChanged(int);
    void onModelBoxChanged(int);
    void kill();

private:
    Ui::FiducialWidget *m_ui;
    int m_fiducialId;
    QHash< int, ModelDescription > m_availableModels;
    KetaRoller::InputDevice *m_input;
    BctOutputDevice *m_output;
    KetaRoller::InputPort *m_inPort;
    KetaRoller::OutputPort *m_outPort;
    int m_lastModelIndex;
    bool m_fiducialIsMapped;
};

#endif // FIDUCIALWIDGET_H
