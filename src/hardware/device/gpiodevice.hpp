/**
 * \file gpiodevice.hpp
 * \author Thibault Schueller <ryp.sqrt@gmail.com>
 * \brief GpioDevice class declaration
 */

#ifndef GPIODEVICE_HPP
#define GPIODEVICE_HPP

#include "config/ixmlserializable.hpp"
#include "gpio/igpioprovider.hpp"

class GPIO;

/**
* General GPIO Device object. It is configurable from a config file and wraps a GPIO object.
*/
class GpioDevice : public IXmlSerializable
{
public:
    explicit GpioDevice(IGPIOProvider& gpioProvider, const std::string& name = "gpio");
    ~GpioDevice() = default;

    GpioDevice(const GpioDevice& other) = delete;
    GpioDevice& operator=(const GpioDevice& other) = delete;

    GpioDevice(GpioDevice&& other) = default;

public:
    virtual void    serialize(ptree& node) override;
    virtual void    deserialize(const ptree& node) override;

public:
    GPIO*       getGpio();
    const GPIO* getGpio() const;

    /**
    * Setup the listener so that it receives events generated by this GpioDevice
    */
    void        startListening(IGPIOListener* listener);

    /**
    * Unregister the listener so that it stops receiving events generated by this GpioDevice
    */
    void        stopListening(IGPIOListener* listener);

protected:
    GPIO*   _gpio;

private:
    const std::string   _name;
    IGPIOProvider&      _gpioProvider;
    std::string         _startDirection;
    bool                _startValue;
    bool                _startActiveLow;
};

#endif // GPIODEVICE_HPP