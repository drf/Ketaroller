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


#include "FiducialWidget.h"

#include "ui_fiducialWidget.h"

#include <KetaRoller/InputDevice>
#include <KetaRoller/OutputDevice>
#include <KetaRoller/InputPort>
#include <KetaRoller/PluginLoader>

FiducialWidget::FiducialWidget(const QHash< int, ModelDescription > &availableModels,
                               KetaRoller::InputDevice *inDevice, BctOutputDevice *outDevice,
                               int fiducialId, QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::FiducialWidget)
    , m_fiducialId(fiducialId)
    , m_availableModels(availableModels)
    , m_input(inDevice)
    , m_output(outDevice)
    , m_outPort(KetaRoller::PluginLoader::instance()->loadOutputPort(KetaRoller::PluginLoader::TuioType))
    , m_lastModelIndex(-1)
    , m_fiducialIsMapped(false)
{
    m_ui->setupUi(this);
    m_ui->fiducialNumberLabel->setText(QString::number(fiducialId));

    QVariantMap args;
    args.insert("TuioFiducialID", fiducialId);
    m_inPort = new KetaRoller::InputPort(KetaRoller::Port::TUIOType, args);

    // Connections
    m_input->addOutgoingPort(m_inPort);
    m_inPort->addOutput(m_outPort);
    m_output->addIncomingPort(m_outPort);

    // Add stuff
    m_ui->modelBox->addItem("Nessuno", -1);
    for (QHash< int, ModelDescription >::const_iterator i = m_availableModels.constBegin();
         i != m_availableModels.constEnd(); ++i) {
        m_ui->modelBox->addItem(i.value().name, i.key());
    }
    m_ui->angleBox->setEnabled(false);
    m_ui->positionBox->setEnabled(false);

    // Sigs/slots
    connect(m_ui->angleBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onAngleBoxChanged(int)));
    connect(m_ui->positionBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onPositionBoxChanged(int)));
    connect(m_ui->modelBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onModelBoxChanged(int)));
    connect(m_ui->removeButton, SIGNAL(clicked(bool)),
            this, SLOT(kill()));
}

FiducialWidget::~FiducialWidget()
{

}

void FiducialWidget::kill()
{
    unmapFiducial();
    m_output->removeIncomingPort(m_outPort);
    m_input->removeOutgoingPort(m_inPort, KetaRoller::InputDevice::DeleteAllOrphanOutputsMode);
    delete m_inPort;
}

void FiducialWidget::mapFiducial()
{
    m_output->mapFiducial(m_fiducialId, m_lastModelIndex,
                          m_ui->angleBox->itemData(m_ui->angleBox->currentIndex()).toInt(),
                          m_ui->angleBox->itemData(m_ui->positionBox->currentIndex()).toInt());
    m_fiducialIsMapped = false;
    qDebug() << "Fiducial is now mapped";
}

void FiducialWidget::unmapFiducial()
{
    m_output->unmapFiducial(m_fiducialId);
    m_fiducialIsMapped = false;
    qDebug() << "Fiducial is now unmapped";
}

void FiducialWidget::onModelBoxChanged(int index)
{
    int modelIndex = m_ui->modelBox->itemData(index).toInt();

    if (m_lastModelIndex >= 0) {
        unmapFiducial();
    }

    m_lastModelIndex = modelIndex;
    m_fiducialIsMapped = false;

    m_ui->angleBox->setEnabled(false);
    m_ui->positionBox->setEnabled(false);
    m_ui->angleBox->clear();
    m_ui->positionBox->clear();

    if (modelIndex >= 0) {
        foreach (QComboBox *box, QList< QComboBox* >() << m_ui->angleBox << m_ui->positionBox) {
            box->setEnabled(true);
            box->addItem("Nessuno", -1);
            for (QHash< int, ModelDescription >::const_iterator i = m_availableModels.constBegin();
                 i != m_availableModels.constEnd(); ++i) {
                for (QHash< int, QString >::const_iterator j = i.value().parameters.constBegin();
                     j != i.value().parameters.constEnd(); ++j) {
                    if (j.key() > 2) {
                        box->addItem(j.value(), j.key());
                    }
                }
            }
        }
    }
}

void FiducialWidget::onAngleBoxChanged(int index)
{
    int paramIndex = m_ui->angleBox->itemData(index).toInt();

    if (paramIndex >= 0) {
        mapFiducial();
    } else if (m_ui->positionBox->currentIndex() == 0) {
        unmapFiducial();
    }
}

void FiducialWidget::onPositionBoxChanged(int index)
{
    int paramIndex = m_ui->positionBox->itemData(index).toInt();

    if (paramIndex >= 0) {
        mapFiducial();
    } else if (m_ui->angleBox->currentIndex() == 0) {
        unmapFiducial();
    }
}


#include "FiducialWidget.moc"
