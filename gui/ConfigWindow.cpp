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


#include "ConfigWindow.h"

#include "ui_configUi.h"
#include <KetaRoller/InputDevice>
#include <KetaRoller/PluginLoader>
#include <KetaRoller/InputPort>
#include <GestureOutputPort.h>
#include "FiducialWidget.h"
#include <QInputDialog>
#include "MIDIWidget.h"

ConfigWindow::ConfigWindow(BctOutputDevice* device, const QHash< int, ModelDescription >& loadedModels,
                           bool useMidi, int tuioPort, QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::ConfigGUI)
    , m_bctDevice(device)
    , m_loadedModels(loadedModels)
{
    m_ui->setupUi(this);

    // Populate checkboxes
    m_ui->midiTreeComboBox->addItem("Nessuno", -1);
    for (QHash< int, ModelDescription >::const_iterator i = loadedModels.constBegin();
         i != loadedModels.constEnd(); ++i) {
        m_ui->midiTreeComboBox->addItem(i.value().name, i.key());
    }

    if (useMidi) {
        // Create in/outs
        QVariantMap args;
        args["ClientName"] = "BCT Controller";
        KetaRoller::InputDevice *midiIn = KetaRoller::PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::MIDIType, args);
        KetaRoller::InputPort *midiInPort = new KetaRoller::InputPort(KetaRoller::Port::MIDIType);
        midiIn->addOutgoingPort(midiInPort);
        KetaRoller::OutputPort *midiOutPort = KetaRoller::PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::MIDIType);
        midiInPort->addOutput(midiOutPort);
        m_bctDevice->addIncomingPort(midiOutPort);
    } else {
        m_ui->midiConfig->setEnabled(false);
        m_ui->addMIDIButton->setEnabled(false);
    }

    if (tuioPort > 0) {
        // Create in/outs
        QVariantMap args;
        args.insert("TuioClientPort", tuioPort);
        // Enable gestures
        args.insert("EnableGestures", true);
        m_tuioInput = KetaRoller::PluginLoader::instance()->loadInputDevice(KetaRoller::PluginLoader::TuioType, args);

        // Setup gestures
        args.clear();
        args["GestureType"] = (uint)Qt::SwipeGesture;
        KetaRoller::InputPort *iport = new KetaRoller::InputPort(KetaRoller::Port::GestureType, args);
        KetaRoller::OutputPort *oport = new KetaRoller::GestureOutputPort(this);
        iport->addOutput(oport);
        m_tuioInput.data()->addOutgoingPort(iport);
        m_bctDevice->addIncomingPort(oport);

        args.clear();
        args["GestureType"] = (uint)Qt::TapGesture;
        iport = new KetaRoller::InputPort(KetaRoller::Port::GestureType, args);
        oport = new KetaRoller::GestureOutputPort(this);
        iport->addOutput(oport);
        m_tuioInput.data()->addOutgoingPort(iport);
        m_bctDevice->addIncomingPort(oport);
    } else {
        m_ui->tuioConfig->setEnabled(false);
        m_ui->addTuioButton->setEnabled(false);
    }

    // Connect handlers
    connect(m_ui->midiTreeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onMidiNoteOnOffAssociationChanged(int)));
    connect(m_ui->addTuioButton, SIGNAL(clicked(bool)), this, SLOT(onAddTuioClicked(bool)));
    connect(m_ui->addMIDIButton, SIGNAL(clicked(bool)), this, SLOT(onAddMIDIClicked(bool)));
}

ConfigWindow::~ConfigWindow()
{

}

void ConfigWindow::onAddTuioClicked(bool )
{
    // Ask for the id
    bool ok;
    int id = QInputDialog::getInt(this, "Numero Fiducial", "Per favore indica l'id del fiducial da pilotare",
                                  0, 0, 16, 1, &ok);

    if (ok) {
        FiducialWidget *widget = new FiducialWidget(m_loadedModels, m_tuioInput.data(), m_bctDevice, id, this);
        m_ui->tuioLayout->insertWidget(0, widget);
    }
}

void ConfigWindow::onAddMIDIClicked(bool )
{
    MIDIWidget *widget = new MIDIWidget(m_loadedModels, m_bctDevice, this);
    m_ui->midiLayout->insertWidget(1, widget);
}

void ConfigWindow::onMidiNoteOnOffAssociationChanged(int index)
{
    if (m_ui->midiTreeComboBox->itemData(m_ui->midiTreeComboBox->currentIndex()).toInt() > 0) {
        m_bctDevice->mapMidiNoteOnOff(m_ui->midiTreeComboBox->itemData(m_ui->midiTreeComboBox->currentIndex()).toInt());
    } else {
        m_bctDevice->mapMidiNoteOnOff(-1);
    }
}

#include "ConfigWindow.moc"
