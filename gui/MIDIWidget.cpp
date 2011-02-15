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


#include "MIDIWidget.h"

#include "ui_midiWidget.h"

#include <QDebug>

MIDIWidget::MIDIWidget(const QHash< int, ModelDescription > &availableModels, BctOutputDevice *device, QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::MIDIWidget)
    , m_device(device)
    , m_availableModels(availableModels)
    , m_lastCC(-1)
{
    m_ui->setupUi(this);

    m_ui->modelBox->addItem("Nessuno", -1);
    for (QHash< int, ModelDescription >::const_iterator i = m_availableModels.constBegin();
         i != m_availableModels.constEnd(); ++i) {
        m_ui->modelBox->addItem(i.value().name, i.key());
    }
    m_ui->paramBox->setEnabled(false);

    connect(m_ui->ccNumber, SIGNAL(valueChanged(int)), this, SLOT(onCCNumberChanged(int)));
    connect(m_ui->modelBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onModelBoxChanged(int)));
    connect(m_ui->paramBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onParamBoxChanged(int)));
    connect(m_ui->removeButton, SIGNAL(clicked(bool)), this, SLOT(kill(bool)));
}

MIDIWidget::~MIDIWidget()
{

}

void MIDIWidget::kill(bool )
{
    unmap();
    deleteLater();
}

void MIDIWidget::map()
{
    m_device->mapMidiCC(m_lastCC,
                        m_ui->modelBox->itemData(m_ui->modelBox->currentIndex()).toInt(),
                        m_ui->paramBox->itemData(m_ui->paramBox->currentIndex()).toInt());
    qDebug() << "MIDI CC " << m_lastCC << " mapped";
}

void MIDIWidget::unmap()
{
    m_device->unmapMidiCC(m_lastCC);
    qDebug() << "MIDI CC " << m_lastCC << " unmapped";
}

void MIDIWidget::onCCNumberChanged(int cc)
{
    if (m_lastCC != -1) {
        unmap();
    }

    m_lastCC = cc;

    if (m_lastCC >= 0 && m_ui->modelBox->itemData(m_ui->modelBox->currentIndex()).toInt() >= 0 &&
        m_ui->paramBox->itemData(m_ui->paramBox->currentIndex()).toInt() >= 0) {
        map();
    }
}

void MIDIWidget::onParamBoxChanged(int index)
{
    int param = m_ui->paramBox->itemData(m_ui->paramBox->currentIndex()).toInt();
    if (param >= 0) {
        map();
    } else {
        unmap();
    }
}

void MIDIWidget::onModelBoxChanged(int index)
{
    unmap();
    m_ui->paramBox->clear();
    int model = m_ui->modelBox->itemData(m_ui->modelBox->currentIndex()).toInt();
    if (model >= 0) {
        m_ui->paramBox->setEnabled(true);
        m_ui->paramBox->addItem("Nessuno", -1);
        for (QHash< int, QString >::const_iterator j = m_availableModels[model].parameters.constBegin();
             j != m_availableModels[model].parameters.constEnd(); ++j) {
            if (j.key() > 3) {
                m_ui->paramBox->addItem(j.value(), j.key());
            }
        }
    } else {
        m_ui->paramBox->setEnabled(false);
    }
}

#include "MIDIWidget.moc"
