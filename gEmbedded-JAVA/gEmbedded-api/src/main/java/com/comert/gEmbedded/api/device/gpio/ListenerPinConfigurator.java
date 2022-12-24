package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.Pin;

public interface ListenerPinConfigurator {

    Pin getPin();

    Event getEventStatus();

    int getTimeoutInMilSec();

    ListenerCallBack getCallBack();

    static ListenerPinPropertyConfigurator getBuilder() {
        return new ListenerPinConfiguratorImpl.ListenerPinPropertyConfiguratorImpl();
    }

    interface ListenerPinPropertyConfigurator {

        ListenerPinPropertyConfigurator pin(Pin pin);

        ListenerPinPropertyConfigurator eventStatus(Event eventStatus);

        // for non-blocking timeout must be greater than 0 and maybe less than 1000 millisecond ?
        ListenerPinPropertyConfigurator timeoutInMilSec(int timeoutInMilSec);

        ListenerPinPropertyConfigurator callBack(ListenerCallBack listenerCallBack);

        ListenerPinConfigurator build();

    }

}
