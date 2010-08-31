/*
    KetaRoller - an advanced signal router for musical devices

    Copyright (C) 2010 Dario Freddi <drf@kde.org>
    Copyright (C) 2010 Luca Mucci <luca.mucci@4cmp.it>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef KETAROLLER_PLUGINLOADER_H
#define KETAROLLER_PLUGINLOADER_H

#include <QObject>
#include <QVariantMap>


namespace KetaRoller {

class OutputDevice;
class InputDevice;
class OutputPort;

/**
 * @brief A singleton loader for plugins
 *
 * This class, implemented as a singleton, serves as a way for creating instances of types such as
 * OutputPort, InputDevice and OutputDevice from specific plugins. Talking bluntly, is how you should
 * create devices and ports (except for InputPorts) in your application.
 *
 * @section create_plugin_instance_sec Creating a new instance of a plugin
 *
 * We will try to create a new MIDI input device here. What you need to do is simply:
 *
 * @code
 * QVariantMap args = myArgs();
 * InputDevice *device = PluginLoader::instance()->loadInputDevice(PluginLoader::MIDIType, args);
 * @endcode
 *
 * To have your InputDevice created and ready to go. All of the loading functions are guaranteed to return
 * an object which is already ready to be used.
 */
class Q_DECL_EXPORT PluginLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PluginLoader)
public:
    /**
     * The type of a plugin
     */
    enum Type {
        /**
         * Creates a MIDI plugin
         */
        MIDIType = 1,
        /**
         * Creates a TUIO plugin
         */
        TuioType = 2,
        UserType = 128
    };

    /**
     * @returns The instance of plugin loader. You @b MUST access PluginLoader only through this method without
     *          creating a new instance.
     */
    static PluginLoader *instance();

    /**
     * @brief Loads a new instance of an OutputPort of the specified type
     *
     * This function creates a new instance of an OutputPort of the specified @c type. The returned OutputPort
     * is guaranteed to be already ready to be used.
     *
     * @param type The type of this OutputPort
     *
     * @returns A ready to be used OutputPort, or 0 if loading the plugin was unsuccessful
     */
    OutputPort *loadOutputPort(Type type);
    /**
     * @brief Loads a new instance of an InputDevice of the specified type
     *
     * This function creates a new instance of an InputDevice of the specified @c type. The returned InputDevice
     * is guaranteed to be already ready to be used.
     *
     * @param type The type of this InputDevice
     * @param args A set of arbitrary arguments to be passed to the new InputDevice. Please see
     *             @ref plugins_init_arguments_sec "Plugin arguments" for learning more on this.
     *
     * @returns A ready to be used InputDevice, or 0 if loading the plugin was unsuccessful
     */
    InputDevice *loadInputDevice(Type type, const QVariantMap &args = QVariantMap());
    /**
     * @brief Loads a new instance of an OutputDevice of the specified type
     *
     * This function creates a new instance of an OutputDevice of the specified @c type. The returned OutputDevice
     * is guaranteed to be already ready to be used.
     *
     * @param type The type of this OutputDevice
     * @param args A set of arbitrary arguments to be passed to the new OutputDevice. Please see
     *             @ref plugins_init_arguments_sec "Plugin arguments" for learning more on this.
     *
     * @returns A ready to be used OutputDevice, or 0 if loading the plugin was unsuccessful
     */
    OutputDevice *loadOutputDevice(Type type, const QVariantMap &args = QVariantMap());

    /**
     * Base destructor
     */
    virtual ~PluginLoader();

private:
    /**
     * Constructor.
     *
     * You can't and shouldn't use it: use instance() instead.
     *
     * @sa instance
     */
    PluginLoader(QObject* parent = 0);

    class Private;
    Private * const d;
};

}

#endif // KETAROLLER_PLUGINLOADER_H
