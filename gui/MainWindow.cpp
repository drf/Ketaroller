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


#include "MainWindow.h"

#include "ui_window1.h"
#include <KetaRoller/PluginLoader>
#include <BctOutputDevice.h>
#include <qhostaddress.h>
#include "ConfigWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::MainWindowUi())
{
    m_ui->setupUi(this);

    // Setup devices and stuff.
    KetaRoller::OutputDevice *device =
    KetaRoller::PluginLoader::instance()->loadOutputDevice(KetaRoller::PluginLoader::instance()->listOutputDevices().first());
    m_outputDevice = qobject_cast< BctOutputDevice* >(device);

    connect(m_ui->loadModels, SIGNAL(clicked(bool)),
            this, SLOT(onLoadModelsClicked(bool)));
    connect(m_ui->startBct, SIGNAL(clicked(bool)),
            this, SLOT(onStartBct(bool)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onLoadModelsClicked(bool )
{
    m_outputDevice->startConnection(QHostAddress(m_ui->ipAddress->text()), m_ui->bctPort->value());
//     QEventLoop e;
//     connect(m_outputDevice, SIGNAL(connectionEstabilished()), &e, SLOT(quit()));
//     e.exec();

    QHash< int, ModelDescription > models = m_outputDevice->models();
    for (QHash< int, ModelDescription >::const_iterator i = models.constBegin(); i != models.constEnd(); ++i) {
        qDebug() << "Adding Item";
        QListWidgetItem *item = new QListWidgetItem(i.value().name);
        item->setData(Qt::UserRole, i.key());
        m_ui->listWidget->addItem(item);
    }
}

void MainWindow::onStartBct(bool )
{
    QHash< int, ModelDescription > loadedModels;
    foreach (QListWidgetItem *item, m_ui->listWidget->selectedItems()) {
        int id = item->data(Qt::UserRole).toInt();
        qDebug() << "Loading model " << id;
        if (m_outputDevice->loadModel(id)) {
            loadedModels.insert(id, m_outputDevice->models().value(id));
        }
    }

    qDebug() << "Start playing" <<
    m_outputDevice->startPlaying();

    // Create a new window
    ConfigWindow *window = new ConfigWindow(m_outputDevice, loadedModels, m_ui->midiCheckBox->isChecked(),
                                            m_ui->tuioCheckBox->isChecked() ? m_ui->tuioPortSpinBox->value() : -1);
    window->show();

    hide();
}

#include "MainWindow.moc"
